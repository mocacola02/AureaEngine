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

# -----------------------------------------------------------------------------
# Paths
# -----------------------------------------------------------------------------
set(PROJECT_CORE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Core")
set(PROJECT_ENGINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine")
set(PROJECT_EDITOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Editor")

set(PROJECT_MIRA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Mira")
set(PROJECT_GL_DIR "${PROJECT_MIRA_DIR}/GL")
set(PROJECT_VK_DIR "${PROJECT_MIRA_DIR}/VK")

set(PROJECT_GLAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glad")
set(PROJECT_IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ImGui")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Define SDL3 target from ThirdParty/SDL
set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/SDL3")

add_subdirectory(
		"${SDL3_DIR}"
		"${CMAKE_BINARY_DIR}/SDL3"
		EXCLUDE_FROM_ALL
)

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
# OpenGL
# -----------------------------------------------------------------------------
find_package(OpenGL REQUIRED)

# -----------------------------------------------------------------------------
# GLAD
# -----------------------------------------------------------------------------
file(
		GLOB_RECURSE PROJECT_GLAD_SOURCES
		CONFIGURE_DEPENDS
		"${PROJECT_GLAD_DIR}/src/*.c"
)

add_library(
		GLAD
		STATIC
		${PROJECT_GLAD_SOURCES}
)
target_include_directories(
		GLAD
		PUBLIC
		"${PROJECT_GLAD_DIR}/include"
)

# -----------------------------------------------------------------------------
# Dear ImGui
# -----------------------------------------------------------------------------
add_library(
		ImGui
		STATIC

		"${PROJECT_IMGUI_DIR}/imgui.cpp"
		"${PROJECT_IMGUI_DIR}/imgui_draw.cpp"
		"${PROJECT_IMGUI_DIR}/imgui_tables.cpp"
		"${PROJECT_IMGUI_DIR}/imgui_widgets.cpp"

		"${PROJECT_IMGUI_DIR}/backends/imgui_impl_sdl3.cpp"
		"${PROJECT_IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)
target_include_directories(
		ImGui
		PUBLIC
		"${PROJECT_IMGUI_DIR}"
		"${PROJECT_IMGUI_DIR}/backends"
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
		GLAD
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
		GLAD
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
		GLAD
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