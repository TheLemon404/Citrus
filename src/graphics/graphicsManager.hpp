#pragma once

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

        Window& window;

    public:
        GraphicsManager(Window& window) : window(window) {};

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

        void SubmitCommands();

        void FetchResults();

        std::pair<WGPUSurfaceTexture, WGPUTextureView> GetNextSurfaceViewData();

    public:
        void Init();
        void Draw();
        void CleanUp();
    };
}
