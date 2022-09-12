cmake_minimum_required(VERSION 3.0.0)
project("TheEscape" VERSION 0.1.0)


file(GLOB SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
# set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
# set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "" FORCE)
# add_subdirectory(external/assimp)

target_include_directories(${PROJECT_NAME} PUBLIC header external external/stb external/glm external/glfw/include  .)

if (UNIX)
	# Linux specific libraries
	set(PLAT_SPEC_LIBS "GL")
elseif (WIN32)
	# Windows specific libraries
	set(PLAT_SPEC_LIBS "opengl32")
else ()
	message(FATAL_ERROR "Platform is not supported!")
endif ()

target_link_directories(${PROJECT_NAME} PUBLIC external/glfw/src)

target_link_libraries(${PROJECT_NAME} glfw ${PLAT_SPEC_LIBS})