cmake_minimum_required(VERSION 3.17)
project(pawn_toml C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")

set(SAMP_SDK_DIR ${CMAKE_SOURCE_DIR}/vendor/sdk)
set(TOML_LIB_DIR ${CMAKE_SOURCE_DIR}/vendor/tomlc99)

include(CheckIncludeFile)

check_include_file(alloca.h HAVE_ALLOCA_H)
if(HAVE_ALLOCA_H)
	add_definitions(-DHAVE_ALLOCA_H)
endif()

check_include_file(inttypes.h HAVE_INTTYPES_H)
if(HAVE_INTTYPES_H)
	add_definitions(-DHAVE_INTTYPES_H)
endif()

check_include_file(malloc.h HAVE_MALLOC_H)
if(HAVE_MALLOC_H)
	add_definitions(-DHAVE_MALLOC_H)
endif()

check_include_file(stdint.h HAVE_STDINT_H)
if(HAVE_STDINT_H)
	add_definitions(-DHAVE_STDINT_H)
endif()

if (WIN32 AND MSVC)
	set(USING_WIN32)
	message(STATUS "[${CMAKE_PROJECT_NAME}] On Win32 using MSVC.")
elseif(UNIX AND GCC)
	message(STATUS "[${CMAKE_PROJECT_NAME}] On Unix using GCC / Clang.")
	set(USING_UNIX)
elseif(UNIX AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	message(STATUS "[${CMAKE_PROJECT_NAME}] On Unix using GCC / Clang.")

	set(USING_UNIX)
	set(ON_CLANG)
else()
	message(FATAL_ERROR "Unsupported platform.")
endif()

if (USING_WIN32)
	add_compile_options(/std:c11)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS WIN32)

	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
elseif(USING_UNIX)
	if (ON_CLANG)
		add_compile_options(-Wno-ignored-attributes)
	else()
		add_compile_options(-Wno-attributes)
	endif()

	add_compile_options(-m32 -std=c11)
	add_compile_definitions(LINUX)

	set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)
endif()

add_library(pawn_toml SHARED
		${SAMP_SDK_DIR}/amxplugin.cpp ${SAMP_SDK_DIR}/amx/getch.h ${TOML_LIB_DIR}/toml.c
		source/plugin.def source/main.c source/main.h source/common.h source/natives.c source/natives.h source/pawn-natives.h)

target_include_directories(pawn_toml PUBLIC ${SAMP_SDK_DIR})
target_include_directories(pawn_toml PUBLIC ${SAMP_SDK_DIR}/amx)
target_include_directories(pawn_toml PUBLIC ${TOML_LIB_DIR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})