cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)

project(Ray-Tracing)


# DEPENDENCIES
######################################################################################################
# Path to directory with GLFW Source
set(GLFW_SOURCE "./dependencies/GLFW" CACHE PATH "Path to directory with GLFW source")
set(GLFW_BUILT "${GLFW_SOURCE}/build" CACHE PATH "Path to directory with GLFW built files")

# Path to directory with GLAD Source
set(GLAD_SOURCE "./dependencies/GLAD" CACHE PATH "Path to directory with GLAD source")
set(GLAD_BUILT "${GLAD_SOURCE}/build" CACHE PATH "Path to directory with GLAD built files")

# Path to directory with GLM library headers
set(GLM_INCLUDES "./dependencies/GLM" CACHE PATH "Path to directory with GLM headers")

# Path to directory with STB Image Write library headers
set(STBI_WRITE_INCLUDE "./dependencies/STB_Image_Write" CACHE PATH "Path to directory with STB Image Write header")
######################################################################################################


# SETTINGS
######################################################################################################
# Set directory where executables are created
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "./example")

# Generate compile_commands.json for vscode
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Turn off building unnecessary files
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Include GLFW Source to be built
add_subdirectory(${GLFW_SOURCE} ${GLFW_BUILT})

# Include GLAD Source to be built
add_subdirectory(${GLAD_SOURCE} ${GLAD_BUILT})
######################################################################################################


# INCLUDES
######################################################################################################
include_directories("./include")
include_directories("${GLFW_SOURCE}/include")
include_directories("${GLAD_SOURCE}/include")
include_directories("${GLM_INCLUDES}")
include_directories("${STBI_WRITE_INCLUDE}")
######################################################################################################


# UTILS LIBRARY
######################################################################################################
add_library(RayTracingUtils STATIC
	"./src/Exception.cpp"
	"./src/Shader.cpp"
	"./src/WindowManager.cpp"
	"./src/Camera.cpp"
	"./src/ScreenQuad.cpp"
	"./src/Shapes/Sphere.cpp"
)

target_include_directories(RayTracingUtils PUBLIC "./include")

target_link_libraries(RayTracingUtils glad glfw)
######################################################################################################


# EXECUTABLES
######################################################################################################
add_executable(01-ImageCreation example/01-ImageCreation.cpp)
add_executable(02-ImageCreationGPU example/02-ImageCreationGPU.cpp)
add_executable(03-SimpleSphere example/03-SimpleSphere.cpp)
add_executable(04-NormalsColoredSphere example/04-NormalsColoredSphere.cpp)
######################################################################################################


# LINKING
######################################################################################################
target_link_libraries(02-ImageCreationGPU RayTracingUtils)
target_link_libraries(03-SimpleSphere RayTracingUtils)
target_link_libraries(04-NormalsColoredSphere RayTracingUtils)
######################################################################################################