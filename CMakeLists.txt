cmake_minimum_required(VERSION 3.31)
project(Citrus)

set(CMAKE_CXX_STANDARD 20)
set(DAWN_DLL ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/webgpu/bin/wgpu-windows-x86_64-gnu-release/wgpu_native.dll)
set(DAWN_LIB ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/webgpu/bin/wgpu-windows-x86_64-gnu-release/libwgpu_native.a)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/entt)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
add_library(Citrus SHARED ${SRC})

target_link_libraries(Citrus PRIVATE
        glfw
        glm
        ${DAWN_LIB}
        EnTT::EnTT
        # Required Windows system libs
        opengl32
        d3dcompiler           # For D3DCompile
        ws2_32                # For WSAStartup, WSACleanup
        bcrypt                # Commonly required by Windows APIs
        runtimeobject         # For RoOriginateErrorW (WinRT)
        propsys              # For PropVariantToBSTR, etc.
        userenv
        ntdll
)
target_include_directories(Citrus PRIVATE
        dependencies/glfw/include
        dependencies/webgpu/include
        dependencies/spdlog/include
        dependencies/entt/single_include
        dependencies/glm
)

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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies/webgpu/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies/entt/single_include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm>
        $<INSTALL_INTERFACE:include>
)

function(citrus_target_link_dependency_libraries target)
    target_link_libraries(${target} PRIVATE ${DAWN_LIB})
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
file(COPY ${DAWN_DLL} DESTINATION ${CMAKE_BINARY_DIR}/bin)