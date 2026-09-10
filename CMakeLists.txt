cmake_minimum_required(VERSION 4.3)

project(
		AureaEngine
		LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# -----------------------------------------------------------------------------
# Paths
# -----------------------------------------------------------------------------

set(PROJECT_CORE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Core")
set(PROJECT_ENGINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine")
set(PROJECT_EDITOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Editor")

set(PROJECT_MIRA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Mira")
set(PROJECT_GL_DIR "${PROJECT_MIRA_DIR}/GL")
set(PROJECT_VK_DIR "${PROJECT_MIRA_DIR}/VK")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# -----------------------------------------------------------------------------
# Automatic source discovery
# -----------------------------------------------------------------------------

file(
		GLOB_RECURSE PROJECT_CORE_SOURCES
		CONFIGURE_DEPENDS
		"${PROJECT_CORE_DIR}/*.c"
		"${PROJECT_CORE_DIR}/*.cpp"
		"${PROJECT_CORE_DIR}/*.h"
		"${PROJECT_CORE_DIR}/*.hpp"
)

file(
		GLOB_RECURSE PROJECT_ENGINE_SOURCES
		CONFIGURE_DEPENDS
		"${PROJECT_ENGINE_DIR}/*.c"
		"${PROJECT_ENGINE_DIR}/*.cpp"
		"${PROJECT_ENGINE_DIR}/*.h"
		"${PROJECT_ENGINE_DIR}/*.hpp"
)

file(
		GLOB_RECURSE PROJECT_EDITOR_SOURCES
		CONFIGURE_DEPENDS
		"${PROJECT_EDITOR_DIR}/*.c"
		"${PROJECT_EDITOR_DIR}/*.cpp"
		"${PROJECT_EDITOR_DIR}/*.h"
		"${PROJECT_EDITOR_DIR}/*.hpp"
)

file(
		GLOB_RECURSE PROJECT_MIRA_GL_SOURCES
		CONFIGURE_DEPENDS
		"${PROJECT_GL_DIR}/*.c"
		"${PROJECT_GL_DIR}/*.cpp"
		"${PROJECT_GL_DIR}/*.h"
		"${PROJECT_GL_DIR}/*.hpp"
)

file(
		GLOB_RECURSE PROJECT_MIRA_VK_SOURCES
		CONFIGURE_DEPENDS
		"${PROJECT_VK_DIR}/*.c"
		"${PROJECT_VK_DIR}/*.cpp"
		"${PROJECT_VK_DIR}/*.h"
		"${PROJECT_VK_DIR}/*.hpp"
)

# -----------------------------------------------------------------------------
# SDL3
# -----------------------------------------------------------------------------

set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)

set(SDL_AUDIO OFF CACHE BOOL "" FORCE)

set(SDL_GPU OFF CACHE BOOL "" FORCE)
set(SDL_RENDER OFF CACHE BOOL "" FORCE)

set(SDL_CAMERA OFF CACHE BOOL "" FORCE)
set(SDL_SENSOR OFF CACHE BOOL "" FORCE)
set(SDL_POWER OFF CACHE BOOL "" FORCE)
set(SDL_TRAY OFF CACHE BOOL "" FORCE)

set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL_UNINSTALL OFF CACHE BOOL "" FORCE)

# Required SDL subsystems
set(SDL_VIDEO ON CACHE BOOL "" FORCE)
set(SDL_JOYSTICK ON CACHE BOOL "" FORCE)
set(SDL_HIDAPI ON CACHE BOOL "" FORCE)
set(SDL_HAPTIC ON CACHE BOOL "" FORCE)
set(SDL_DIALOG ON CACHE BOOL "" FORCE)

FetchContent_Declare(
		SDL3
		GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
		GIT_TAG release-3.4.16
		GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SDL3)

# -----------------------------------------------------------------------------
# OpenGL
# -----------------------------------------------------------------------------

find_package(OpenGL REQUIRED)

# -----------------------------------------------------------------------------
# GLAD
# -----------------------------------------------------------------------------

FetchContent_Declare(
		glad
		GIT_REPOSITORY https://github.com/Dav1dde/glad.git
		GIT_TAG glad2
		GIT_SHALLOW TRUE
		SOURCE_SUBDIR cmake
)

FetchContent_MakeAvailable(glad)

# OpenGL 4.6 Core
glad_add_library(
		glad_gl_core_46
		STATIC
		REPRODUCIBLE
		API gl:core=4.6
		EXTENSIONS NONE		# May need to be changed in the future
)

# Vulkan 1.4
glad_add_library(
		glad_vulkan_14
		STATIC
		LOADER
		API vulkan=1.4
		EXTENSIONS NONE		# May need to be changed in the future
)

# -----------------------------------------------------------------------------
# Dear ImGui
# -----------------------------------------------------------------------------

FetchContent_Declare(
		imgui
		GIT_REPOSITORY https://github.com/ocornut/imgui.git
		GIT_TAG docking
		GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(imgui)

add_library(
		ImGui
		STATIC

		"${imgui_SOURCE_DIR}/imgui.cpp"
		"${imgui_SOURCE_DIR}/imgui_draw.cpp"
		"${imgui_SOURCE_DIR}/imgui_tables.cpp"
		"${imgui_SOURCE_DIR}/imgui_widgets.cpp"

		"${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp"
		"${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
)

target_include_directories(
		ImGui
		PUBLIC
		"${imgui_SOURCE_DIR}"
		"${imgui_SOURCE_DIR}/backends"
)

target_compile_definitions(
		ImGui
		PRIVATE
		IMGUI_IMPL_OPENGL_LOADER_GLAD
)

target_link_libraries(
		ImGui
		PUBLIC
		SDL3::SDL3

		PRIVATE
		OpenGL::GL
		glad_gl_core_46
)

# -----------------------------------------------------------------------------
# Core
# -----------------------------------------------------------------------------

add_library(
		Core
		SHARED
		${PROJECT_CORE_SOURCES}
)

target_include_directories(
		Core
		PUBLIC
		"${PROJECT_CORE_DIR}"
)

# -----------------------------------------------------------------------------
# Engine
# -----------------------------------------------------------------------------

add_library(
		Engine
		SHARED
		${PROJECT_ENGINE_SOURCES}
)

target_include_directories(
		Engine
		PUBLIC
		"${PROJECT_ENGINE_DIR}"
)

target_link_libraries(
		Engine
		PUBLIC
		Core
		SDL3::SDL3
)

# -----------------------------------------------------------------------------
# Mira OpenGL
# -----------------------------------------------------------------------------

add_library(
		MiraGL
		SHARED
		${PROJECT_MIRA_GL_SOURCES}
)

target_include_directories(
		MiraGL
		PUBLIC
		"${PROJECT_GL_DIR}"
)

target_link_libraries(
		MiraGL
		PUBLIC
		Core
		Engine

		PRIVATE
		OpenGL::GL
		glad_gl_core_46
)

# -----------------------------------------------------------------------------
# Mira Vulkan
# -----------------------------------------------------------------------------

add_library(
		MiraVK
		SHARED
		${PROJECT_MIRA_VK_SOURCES}
)

target_include_directories(
		MiraVK
		PUBLIC
		"${PROJECT_VK_DIR}"
)

target_link_libraries(
		MiraVK
		PUBLIC
		Core
		Engine

		PRIVATE
		glad_vulkan_14
)

# -----------------------------------------------------------------------------
# Editor
# -----------------------------------------------------------------------------

add_executable(
		Editor
		${PROJECT_EDITOR_SOURCES}
)

target_include_directories(
		Editor
		PRIVATE
		"${PROJECT_EDITOR_DIR}"
)

target_link_libraries(
		Editor
		PRIVATE
		Core
		Engine
		MiraGL
		MiraVK
		ImGui
)

# -----------------------------------------------------------------------------
# Windows DLL exports
# -----------------------------------------------------------------------------

if(WIN32)
	set_target_properties(
			Core
			Engine
			MiraGL
			MiraVK
			PROPERTIES
			WINDOWS_EXPORT_ALL_SYMBOLS ON
	)
endif()

# -----------------------------------------------------------------------------
# Runtime dependencies
# -----------------------------------------------------------------------------

if(WIN32)
	add_custom_command(
			TARGET Editor
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:SDL3::SDL3>
			$<TARGET_FILE_DIR:Editor>
	)
endif()