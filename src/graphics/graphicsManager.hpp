#pragma once

#include <vector>

#include "core/core.hpp"
#include <webgpu/webgpu.h>

#include "core/window.hpp"

namespace Citrus {
    struct CITRUS_API GraphicalSettings {
        WGPUPowerPreference powerPreference = WGPUPowerPreference_HighPerformance;
        WGPUBackendType backendType = WGPUBackendType_Vulkan;
    };

    class CITRUS_API GraphicsManager {
        WGPUInstance instance;
        WGPUSurface surface;
        WGPUAdapter adapter;
        WGPUDevice device;
        WGPUQueue queue;
        WGPUCommandEncoder commandEncoder;
        GraphicalSettings graphicalSettings;

        const WGPUTextureFormat surfaceFormat = WGPUTextureFormat_BGRA8Unorm;

        //pipelines
        WGPURenderPipeline pipeline;

        //shaders
        WGPUShaderModule shaderModule;

        Window& window;

        std::vector<float> vertexData = {
            // x0, y0
            -0.5, -0.5, 0.0,

            // x1, y1
            0.5, -0.5, 0.0,

            // x2, y2
            0.0, 0.5, 0.0
        };
        WGPUBuffer vertexBuffer;


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
        void InitBindings();
        void InitPipelines();

        std::pair<WGPUSurfaceTexture, WGPUTextureView> GetNextSurfaceViewData();

    public:
        void Init();
        void Draw();
        void CleanUp();
    };
}
