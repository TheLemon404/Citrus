cmake_minimum_required(VERSION 3.31)
project(Citrus)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/webgpu)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
add_library(Citrus SHARED ${SRC})

target_link_libraries(Citrus PRIVATE glfw webgpu)
target_include_directories(Citrus PRIVATE dependencies/glfw/include dependencies/webgpu/wgpu-native/include dependencies/spdlog/include)
target_copy_webgpu_binaries(Citrus)

# In your CMakeLists.txt
if(MSVC)
    add_compile_options(/MP)  # Multi-processor compilation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")  # Handle large object files
endif()

# Set parallel jobs
set(CMAKE_BUILD_PARALLEL_LEVEL 8)  # Adjust based on your CPU cores

set(DAWN_BUILD_SAMPLES OFF)
set(DAWN_BUILD_TESTS OFF)
set(DAWN_BUILD_DOCS OFF)
set(TINT_BUILD_TESTS OFF)
set(TINT_BUILD_DOCS OFF)
set(DAWN_USE_X11 OFF)  # If not using X11
set(DAWN_USE_WAYLAND OFF)  # If not using Wayland

# Set up include directories for consumers of this library
target_include_directories(Citrus PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies/spdlog/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies/webgpu/dawn/include>
        $<INSTALL_INTERFACE:include>
)

function(citrus_target_link_dependency_libraries target)
    target_link_libraries(${target} PRIVATE webgpu)
endfunction()

# Set DLL export/import macros (if using Windows)
if(WIN32)
    target_compile_definitions(Citrus PRIVATE CITRUS_EXPORTS)
endif()

# Set output directory for the DLL
set_target_properties(Citrus PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR}/bin)