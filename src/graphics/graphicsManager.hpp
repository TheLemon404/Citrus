#pragma once

#include <memory>
#include <vector>

#include "core/core.hpp"
#include <webgpu/webgpu.h>

#include <glm/mat4x4.hpp>
#include "core/window.hpp"
#include "scene/scene.hpp"
#include "types/mesh.hpp"

namespace Citrus {
    struct BackendMesh {
        WGPUBuffer positionBuffer;
        WGPUBuffer normalBuffer;
        WGPUBuffer colorBuffer;
        WGPUBuffer uvBuffer;
        WGPUBuffer indexBuffer;

        size_t indexCount;
    };

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

        //meshes
        std::unordered_map<std::shared_ptr<Mesh>, BackendMesh> meshCache;

        //standardized model data
        WGPUVertexAttribute positionAttribute;
        WGPUVertexAttribute colorAttribute;
        std::vector<WGPUVertexBufferLayout> vertexBufferLayout;

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

        void UploadMeshIfNeeded(std::shared_ptr<Mesh> mesh);

        std::pair<WGPUSurfaceTexture, WGPUTextureView> GetNextSurfaceViewData();

    public:
        void Init();
        void Draw(Scene& scene);
        void CleanUp();
    };
}
