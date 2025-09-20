cmake_minimum_required(VERSION 3.16)

# Имя проекта
project(Scene LANGUAGES CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Пути
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR      ${PROJECT_ROOT}/src)
set(INC_DIR      ${PROJECT_ROOT}/include)
set(VENDORS_DIR  ${PROJECT_ROOT}/Vendors)

# Рекурсивно собираем исходники/заголовки
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    ${SRC_DIR}/*.cpp
    ${SRC_DIR}/*.c
)
file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS
    ${INC_DIR}/*.hpp
    ${INC_DIR}/*.h
)

# Исполняемый файл (если нужен стат/динамическая библиотека — замените на add_library)
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

# Инклуды проекта
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${INC_DIR}
        ${SRC_DIR} # на случай, если есть приватные заголовки в src
)

# Вендорные инклуды и библиотеки
if(EXISTS ${VENDORS_DIR})
    # Папки include/inc/Includes в каждом подкаталоге Vendors/*
    file(GLOB VENDOR_INCLUDE_DIRS
        "${VENDORS_DIR}/*/include"
        "${VENDORS_DIR}/*/inc"
        "${VENDORS_DIR}/*/Includes"
    )
    if(VENDOR_INCLUDE_DIRS)
        target_include_directories(${PROJECT_NAME} PRIVATE ${VENDOR_INCLUDE_DIRS})
    endif()

    # Предсобранные библиотеки из Vendors/*/lib
    if(MSVC)
        file(GLOB_RECURSE VENDOR_LIBS
            "${VENDORS_DIR}/*/lib/*.lib"
        )
    else()
        file(GLOB_RECURSE VENDOR_LIBS
            "${VENDORS_DIR}/*/lib/*.a"
            "${VENDORS_DIR}/*/lib/*.so"
            "${VENDORS_DIR}/*/lib/*.dylib"
        )
    endif()

    if(VENDOR_LIBS)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${VENDOR_LIBS})
    endif()

    # Копирование рантайм-библиотек (.dll/.so/.dylib) рядом с бинарником
    set(RUNTIME_COPY_PATTERNS "*.dll" "*.so" "*.dylib")
    foreach(PAT IN LISTS RUNTIME_COPY_PATTERNS)
        file(GLOB_RECURSE VENDOR_RUNTIME_FILES
            "${VENDORS_DIR}/*/bin/${PAT}"
            "${VENDORS_DIR}/*/lib/${PAT}"
        )
        if(VENDOR_RUNTIME_FILES)
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${VENDOR_RUNTIME_FILES}
                    $<TARGET_FILE_DIR:${PROJECT_NAME}>
                VERBATIM
            )
        endif()
    endforeach()
endif()

# Директории вывода
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_ROOT}/bin/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_ROOT}/lib/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_ROOT}/lib/$<CONFIG>"
)

# Группировка в IDE
source_group(TREE ${PROJECT_ROOT} FILES ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# Предупреждения компилятора
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_compile_definitions(${PROJECT_NAME}
   PRIVATE
       $<$<CONFIG:Debug>:DEBUG>
       $<$<CONFIG:Release>:NDEBUG>
       
       GLFW_INCLUDE_NONE
)