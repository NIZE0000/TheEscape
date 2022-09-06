cmake_minimum_required(VERSION 3.0.0)
project("The Escape" VERSION 0.1.0)


# add_library()

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(TheEscape ${SRC_FILES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
# set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
# set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "" FORCE)
# add_subdirectory(external/assimp)

target_include_directories(TheEscape PUBLIC header external external/stb external/glm external/glfw/include  .)

target_link_libraries(TheEscape glfw GL dl ${PLAT_SPEC_LIBS})