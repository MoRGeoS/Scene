#pragma once

#if defined(SCENE_BUILDING_DLL)
#	define SCENE_API __declspec(dllexport)
#elif defined(SCENE_USING_DLL)
#	define SCENE_API __declspec(dllimport)
#elif defined(SCENE_STATIC)
#	define SCENE_API
#else
#	define SCENE_API
#endif