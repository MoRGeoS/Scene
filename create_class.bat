@echo off
rem NewClass-no-namespace.bat - generate .h in include\ and .cpp in src\ without any namespace

setlocal

:: Запрос подкаталога (можно оставить пустым)
set /p subpath=Enter subdirectory (or leave blank): 

:: Запрос имени класса
set /p name=Enter class name: 

:: Нормализация (убираем лишние кавычки)
for %%I in ("%subpath%") do set "subpath=%%~I"
for %%I in ("%name%") do set "name=%%~I"

:: Простейшая проверка
if "%name%"=="" (
  echo Class name is required.
  exit /b 1
)

:: Пути к файлам
if "%subpath%"=="" (
  set "hfile=include\%name%.h"
  set "cppfile=src\%name%.cpp"
) else (
  set "hfile=include\%subpath%\%name%.h"
  set "cppfile=src\%subpath%\%name%.cpp"
)

:: Создаём директории
for %%D in ("include\%subpath%" "src\%subpath%") do (
  if not exist "%%~D" mkdir "%%~D"
)

:: --- header (.h) ---
> "%hfile%" echo // %name%.h
>> "%hfile%" echo #pragma once
>> "%hfile%" echo.
>> "%hfile%" echo class %name%
>> "%hfile%" echo {
>> "%hfile%" echo public:
>> "%hfile%" echo     %name%();
>> "%hfile%" echo     virtual ~%name%();
>> "%hfile%" echo };
 
:: --- source (.cpp) ---
> "%cppfile%" echo // %name%.cpp
if "%subpath%"=="" (
  >> "%cppfile%" echo ^#include ^<%name%.h^>
) else (
  >> "%cppfile%" echo ^#include ^<%subpath%/%name%.h^>
)
>> "%cppfile%" echo.
>> "%cppfile%" echo %name%::%name%()
>> "%cppfile%" echo {
>> "%cppfile%" echo     // constructor
>> "%cppfile%" echo }
>> "%cppfile%" echo.
>> "%cppfile%" echo %name%::~%name%()
>> "%cppfile%" echo {
>> "%cppfile%" echo     // destructor
>> "%cppfile%" echo }

echo Created:
echo  %hfile%
echo  %cppfile%

:: Если нужно убрать автосборку — закомментируйте следующую строку
call build.bat

endlocal
exit /b 0