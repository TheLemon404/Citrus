#pragma once

#include <vector>

#include "core/core.hpp"
#include <webgpu/webgpu.h>

#include "../../dependencies/glm/glm/mat4x4.hpp"
#include "core/window.hpp"

namespace Citrus {
    struct CITRUS_API GraphicalSettings {
        WGPUPowerPreference powerPreference = WGPUPowerPreference_HighPerformance;
        WGPUBackendType backendType = WGPUBackendType_Vulkan;
    };

    struct CITRUS_API ModelUniforms {
        glm::mat4x4 transform;
    };

    struct CITRUS_API WorldUniforms {
        glm::mat4x4 view;
        glm::mat4x4 projection;
    };

    class CITRUS_API GraphicsManager {
        Window& window;

        WGPUInstance instance;
        WGPUSurface surface;
        WGPUAdapter adapter;
        WGPUDevice device;
        WGPUQueue queue;
        WGPUCommandEncoder commandEncoder;
        GraphicalSettings graphicalSettings;

        const WGPUTextureFormat surfaceFormat = WGPUTextureFormat_BGRA8Unorm;

        //pipelines
        WGPUPipelineLayout pipelineLayout;
        WGPURenderPipeline pipeline;

        //shaders
        WGPUShaderModule shaderModule;

        // x0, y0, x1, y1, ...
        std::vector<float> positionData = {
            -0.5, -0.5, 0.0,
            +0.5, -0.5, 0.0,
            +0.5, +0.5, 0.0,
            -0.5, +0.5, 0.0,
        };

        // r0,  g0,  b0, r1,  g1,  b1, ...
        std::vector<float> colorData = {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 0.0,
        };

        std::vector<uint16_t> indexData = {
            0, 1, 2, // Triangle #0 connects points #0, #1 and #2
            0, 2, 3  // Triangle #1 connects points #0, #2 and #3
        };

        //model data
        WGPUVertexAttribute positionAttribute;
        WGPUVertexAttribute colorAttribute;
        std::vector<WGPUVertexBufferLayout> vertexBufferLayout;
        WGPUBuffer positionBuffer;
        WGPUBuffer colorBuffer;
        WGPUBuffer indexBuffer;

        //uniforms
        WGPUBuffer modelUniformsBuffer;
        WGPUBuffer worldUniformsBuffer;

        //bind groups
        WGPUBindGroupLayout bindGroupLayout;
        WGPUBindGroup bindGroup;


    public:
        GraphicsManager(Window& window) : window(window) {};

        //public callbacks
        void OnFramebufferResized(unsigned int width, unsigned int height);

    private:
        //WebGPU async callbacks
        static void RequestAdapterCallback(WGPURequestAdapterStatus status, WGPUAdapter adapter, WGPUStringView message, void* userdata1, void* userdata2);
        static void RequestDeviceCallback(WGPURequestDeviceStatus status, WGPUDevice device, WGPUStringView message, void* userdata1, void* userdata2);
        static void DeviceLostCallback(WGPUDevice const * device, WGPUDeviceLostReason reason, WGPUStringView message, void* userdata1, void* userdata2);
        static void UncapturedErrorCallback(WGPUDevice const * device, WGPUErrorType type, WGPUStringView message, void* userdata1, void* userdata2);
        static void QueueWorkDownCallback(WGPUQueueWorkDoneStatus status, void* userdata1, void* userdata2);

        void InitDevice();

        void LoadResources();
        void InitBuffers();
        void InitBindings();
        void InitPipelines();

        std::pair<WGPUSurfaceTexture, WGPUTextureView> GetNextSurfaceViewData();

    public:
        void Init();
        void Draw();
        void CleanUp();
    };
}
