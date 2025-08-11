#include "graphicsManager.hpp"
#include "core/log.hpp"

#include <webgpu/webgpu.h>
#include <GLFW/glfw3.h>

#include "core/files.hpp"

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <windows.h>
#endif

namespace Citrus {
    void GraphicsManager::OnFramebufferResized(unsigned int width, unsigned int height) {
        WGPUSurfaceConfiguration surfaceConfiguration = {
            .nextInChain = nullptr,
            .device = device,
            .format = WGPUTextureFormat_BGRA8Unorm,
            .usage = WGPUTextureUsage_RenderAttachment,
            .width = width,
            .height = height,
            .viewFormatCount = 0,
            .viewFormats = nullptr,
            .alphaMode = WGPUCompositeAlphaMode_Auto,
            .presentMode = WGPUPresentMode_Fifo,
        };
        wgpuSurfaceConfigure(surface, &surfaceConfiguration);
    }

    void GraphicsManager::RequestAdapterCallback(WGPURequestAdapterStatus status, WGPUAdapter adapter, WGPUStringView message, void *userdata1, void* userdata2) {
        GraphicsManager* manager = static_cast<GraphicsManager*>(userdata1);
        manager->adapter = adapter;

        WGPULimits adapterLimits = {};
        wgpuAdapterGetLimits(adapter, &adapterLimits);

        WGPUAdapterInfo adapterInfo = {};
        wgpuAdapterGetInfo(adapter, &adapterInfo);

        CITRUS_CORE_INFO("Obtained adapter with limits and info: ");
        CITRUS_CORE_INFO("Limits: ");
        CITRUS_CORE_INFO(" - maxTextureDimension1D: {}", adapterLimits.maxTextureDimension1D);
        CITRUS_CORE_INFO(" - maxTextureDimension2D: {}", adapterLimits.maxTextureDimension2D);
        CITRUS_CORE_INFO(" - maxTextureDimension3D: {}", adapterLimits.maxTextureDimension3D);
        CITRUS_CORE_INFO(" - maxTextureArrayLayers: {}", adapterLimits.maxTextureArrayLayers);
        CITRUS_CORE_INFO("Info: ");
        CITRUS_CORE_INFO(" - vendor: {}", std::string(adapterInfo.vendor.data, adapterInfo.vendor.length));
        CITRUS_CORE_INFO(" - architecture: {}", std::string(adapterInfo.architecture.data, adapterInfo.architecture.length));
        CITRUS_CORE_INFO(" - device: {}", std::string(adapterInfo.device.data, adapterInfo.device.length));
        CITRUS_CORE_INFO(" - deviceID: {}", adapterInfo.deviceID);
        CITRUS_CORE_INFO(" - description: {}", std::string(adapterInfo.description.data, adapterInfo.description.length));
    }

    void GraphicsManager::RequestDeviceCallback(WGPURequestDeviceStatus status, WGPUDevice device, WGPUStringView message, void *userdata1, void* userdata2) {
        GraphicsManager* manager = static_cast<GraphicsManager*>(userdata1);
        manager->device = device;

        WGPULimits deviceLimits = {};
        wgpuDeviceGetLimits(device, &deviceLimits);

        CITRUS_CORE_INFO("Obtained device with limits and info: ");
        CITRUS_CORE_INFO("Limits: ");
        CITRUS_CORE_INFO(" - maxTextureDimension1D: {}", deviceLimits.maxTextureDimension1D);
        CITRUS_CORE_INFO(" - maxTextureDimension2D: {}", deviceLimits.maxTextureDimension2D);
        CITRUS_CORE_INFO(" - maxTextureDimension3D: {}", deviceLimits.maxTextureDimension3D);
        CITRUS_CORE_INFO(" - maxTextureArrayLayers: {}", deviceLimits.maxTextureArrayLayers);
        CITRUS_CORE_INFO(" - maxBindGroups: {}", deviceLimits.maxBindGroups);
        CITRUS_CORE_INFO(" - maxBufferSize: {}", deviceLimits.maxBufferSize);
        CITRUS_CORE_INFO(" - maxVertexAttributes: {}", deviceLimits.maxVertexAttributes);
    }

    void GraphicsManager::UncapturedErrorCallback(WGPUDevice const *device, WGPUErrorType type, WGPUStringView message, void *userdata1, void *userdata2) {
        CITRUS_CORE_ERROR("WebGPU Error Callback triggered: ");
        CITRUS_CORE_ERROR(" Error Type: {}", (int)type);
        CITRUS_CORE_ERROR(" Error: {}", std::string(message.data, message.length));
    }

    void GraphicsManager::QueueWorkDownCallback(WGPUQueueWorkDoneStatus status, void *userdata1, void *userdata2) {
        CITRUS_CORE_INFO("Queue work finished with status: {}", (int)status);
    }

    void GraphicsManager::DeviceLostCallback(WGPUDevice const *device, WGPUDeviceLostReason reason, WGPUStringView message, void *userdata1, void *userdata2) {
        CITRUS_CORE_FATAL("Device lost: ");
        CITRUS_CORE_FATAL(" reason: {}", (int)reason);
        CITRUS_CORE_FATAL(" message: {}", std::string(message.data, message.length));
    }

    void GraphicsManager::Init() {
        WGPUInstanceDescriptor instanceDescriptor = {
            .nextInChain = nullptr,
        };
        instance = wgpuCreateInstance(&instanceDescriptor);

        InitDevice();
        LoadResources();
        InitBindings();
        InitPipelines();

        CITRUS_CORE_INFO("initialized graphics manager");
    }

    void GraphicsManager::InitDevice() {
        //get glfw window surface
        HWND hwnd = glfwGetWin32Window(window.GetGLFWWindow());
        HINSTANCE hinstance = GetModuleHandle(nullptr);

        WGPUSurfaceSourceWindowsHWND win32SurfaceSrc = {
            .chain = {
                .next = nullptr,
                .sType = WGPUSType_SurfaceSourceWindowsHWND,
            },
            .hinstance = hinstance,
            .hwnd = hwnd,
        };

        WGPUSurfaceDescriptor surfaceDesc = {
            .nextInChain = &win32SurfaceSrc.chain,
            .label = "GLFW Surface"
        };
        surface = wgpuInstanceCreateSurface(instance, &surfaceDesc);

        //request and setup adapter
        WGPURequestAdapterOptions requestAdapterOptions = {
            .nextInChain = nullptr,
            .powerPreference = graphicalSettings.powerPreference,
            .backendType = graphicalSettings.backendType,
            .compatibleSurface = surface,
        };
        WGPURequestAdapterCallbackInfo requestAdapterCallbackInfo = {
            .nextInChain = nullptr,
            .mode = WGPUCallbackMode_WaitAnyOnly,
            .callback = RequestAdapterCallback,
            .userdata1 = this,
        };
        wgpuInstanceRequestAdapter(instance, &requestAdapterOptions, requestAdapterCallbackInfo);

        //request and setup device along with uncaptured error info
        WGPUDeviceLostCallbackInfo deviceLostCallbackInfo = {
            .nextInChain = nullptr,
            .callback = DeviceLostCallback,
        };
        WGPUUncapturedErrorCallbackInfo uncapturedErrorCallbackInfo = {
            .nextInChain = nullptr,
            .callback = UncapturedErrorCallback,
        };
        WGPUDeviceDescriptor deviceDescriptor = {
            .nextInChain = nullptr,
            .label = "Primary Graphics Device",
            .requiredFeatureCount = 0,
            .requiredLimits = nullptr,
            .defaultQueue = {
                .nextInChain = nullptr,
                .label = "Default Queue"
            },
            .deviceLostCallbackInfo = deviceLostCallbackInfo,
            .uncapturedErrorCallbackInfo = uncapturedErrorCallbackInfo,
        };
        WGPURequestDeviceCallbackInfo requestDeviceCallbackInfo = {
            .nextInChain = nullptr,
            .mode = WGPUCallbackMode_WaitAnyOnly,
            .callback = RequestDeviceCallback,
            .userdata1 = this,
        };
        wgpuAdapterRequestDevice(adapter, &deviceDescriptor, requestDeviceCallbackInfo);

        //Get primary queue
        queue = wgpuDeviceGetQueue(device);
        WGPUQueueWorkDoneCallbackInfo queueWorkDoneCallbackInfo = {
            .nextInChain = nullptr,
            .callback = QueueWorkDownCallback,
        };
        wgpuQueueOnSubmittedWorkDone(queue, queueWorkDoneCallbackInfo);

        //configure the surface
        WGPUSurfaceConfiguration surfaceConfiguration = {
            .nextInChain = nullptr,
            .device = device,
            .format = WGPUTextureFormat_BGRA8Unorm,
            .usage = WGPUTextureUsage_RenderAttachment,
            .width = window.GetWidth(),
            .height = window.GetHeight(),
            .viewFormatCount = 0,
            .viewFormats = nullptr,
            .alphaMode = WGPUCompositeAlphaMode_Auto,
            .presentMode = WGPUPresentMode_Fifo,
        };
        wgpuSurfaceConfigure(surface, &surfaceConfiguration);
    }

    void GraphicsManager::LoadResources() {
    }

    void GraphicsManager::InitBindings() {

    }

    void GraphicsManager::InitPipelines() {
        //shaders
        std::string shaderCodeText = FileSystem::ReadFileString("resources/shaders/lit.wgsl");

        if (shaderCodeText.empty()) {
            CITRUS_CORE_ERROR("Shader code is empty! Cannot create shader module.");
            return;
        }

        CITRUS_CORE_INFO("Shader code loaded, length: {}", shaderCodeText.length());

        WGPUShaderSourceWGSL shaderCode = {
            .chain = {
                .next = nullptr,
                .sType = WGPUSType_ShaderSourceWGSL,
            },
            .code = {
                .data = shaderCodeText.c_str(),
                .length = strlen(shaderCodeText.c_str()),
                }
        };

        WGPUShaderModuleDescriptor shaderModuleDescriptor = {
            .nextInChain = &shaderCode.chain,
            .label = "Shader Module",
        };

        shaderModule = wgpuDeviceCreateShaderModule(device, &shaderModuleDescriptor);

        if (!shaderModule) {
            CITRUS_CORE_ERROR("Failed to create shader module!");
            return;
        }

        CITRUS_CORE_INFO("Shader module created successfully");

        // Pipelines
        WGPUBlendState blendState = {
            .color = {
                .operation = WGPUBlendOperation_Add,
                .srcFactor = WGPUBlendFactor_SrcAlpha,
                .dstFactor = WGPUBlendFactor_OneMinusSrcAlpha,
            },
            .alpha = {
                .operation = WGPUBlendOperation_Add,
                .srcFactor = WGPUBlendFactor_Zero,
                .dstFactor = WGPUBlendFactor_One,
            }
        };

        WGPUColorTargetState colorTarget = {
            .format = surfaceFormat,
            .blend = &blendState,
            .writeMask = WGPUColorWriteMask_All
        };

        WGPUFragmentState fragmentState = {
            .module = shaderModule,
            .entryPoint = {
                .data = "fs_main",
                .length = strlen("fs_main"),
                },
            .constantCount = 0,
            .constants = nullptr,
            .targetCount = 1,
            .targets = &colorTarget,
        };

        WGPURenderPipelineDescriptor pipelineDesc = {
            .nextInChain = nullptr,
            .label = "Render Pipeline",
            .layout = nullptr,
            .vertex = {
                .module = shaderModule,
                .entryPoint = {
                    .data = "vs_main",
                    .length = strlen("vs_main"),
                },
                .constantCount = 0,
                .constants = nullptr,
                .bufferCount = 0,
                .buffers = nullptr,
            },
            .primitive = {
                .topology = WGPUPrimitiveTopology_TriangleList,
                .stripIndexFormat = WGPUIndexFormat_Undefined,
                .frontFace = WGPUFrontFace_CCW,
                .cullMode = WGPUCullMode_None,
            },
            .depthStencil = nullptr,
            .multisample = {
                .count = 1,
                .mask = ~0u,
                .alphaToCoverageEnabled = false
            },
            .fragment = &fragmentState,
        };

        pipeline = wgpuDeviceCreateRenderPipeline(device, &pipelineDesc);

        if (!pipeline) {
            CITRUS_CORE_ERROR("Failed to create render pipeline!");
            return;
        }

        CITRUS_CORE_INFO("Render pipeline created successfully");
    }

    std::pair<WGPUSurfaceTexture, WGPUTextureView> GraphicsManager::GetNextSurfaceViewData() {
        WGPUSurfaceTexture surfaceTexture;
        wgpuSurfaceGetCurrentTexture(surface, &surfaceTexture);

        if (!surfaceTexture.texture) {
            CITRUS_CORE_ERROR("Failed to get current surface texture!");
            return {surfaceTexture, nullptr};
        }

        WGPUTextureViewDescriptor viewDescriptor = {
            .nextInChain = nullptr,
            .label = "Surface View Texture",
            .format = wgpuTextureGetFormat(surfaceTexture.texture),
            .dimension = WGPUTextureViewDimension_2D,
            .baseMipLevel = 0,
            .mipLevelCount = 1,
            .baseArrayLayer = 0,
            .arrayLayerCount = 1,
            .aspect = WGPUTextureAspect_All,
        };
        WGPUTextureView targetView = wgpuTextureCreateView(surfaceTexture.texture, &viewDescriptor);
        return std::make_pair(surfaceTexture, targetView);
    }

    void GraphicsManager::Draw() {
        //Check if pipeline is valid before drawing
        if (!pipeline) {
            CITRUS_CORE_ERROR("Pipeline is invalid, skipping draw");
            return;
        }

        //Setup command encoder
        WGPUCommandEncoderDescriptor commandEncoderDescriptor = {
            .nextInChain = nullptr,
            .label = "Command Encoder",
        };
        commandEncoder = wgpuDeviceCreateCommandEncoder(device, &commandEncoderDescriptor);

        //get surface textures
        auto [surfaceTexture, targetView] = GetNextSurfaceViewData();
        if (!targetView) return;

        //describe render pass
        WGPURenderPassColorAttachment renderPassColorAttachment = {
            .nextInChain = nullptr,
            .view = targetView,
            .resolveTarget = nullptr,
            .loadOp = WGPULoadOp_Clear,
            .storeOp = WGPUStoreOp_Store,
            .clearValue = WGPUColor{ 0.9, 0.1, 0.2, 1.0 },
#ifndef WEBGPU_BACKEND_WGPU
            .depthSlice = WGPU_DEPTH_SLICE_UNDEFINED,
#endif // NOT WEBGPU_BACKEND_WGPU
        };
        WGPURenderPassDescriptor renderPassDescriptor = {
            .nextInChain = nullptr,
            .colorAttachmentCount = 1,
            .colorAttachments = &renderPassColorAttachment,
            .depthStencilAttachment = nullptr,
            .timestampWrites = nullptr,
        };

        //begin render pass
        WGPURenderPassEncoder renderPass = wgpuCommandEncoderBeginRenderPass(commandEncoder, &renderPassDescriptor);
        wgpuRenderPassEncoderSetPipeline(renderPass, pipeline);
        wgpuRenderPassEncoderDraw(renderPass, 3, 1, 0, 0);
        wgpuRenderPassEncoderEnd(renderPass);

        //encode commands
        WGPUCommandBufferDescriptor commandBufferDescriptor = {
            .nextInChain = nullptr,
            .label = "Command Buffer",
        };
        WGPUCommandBuffer command = wgpuCommandEncoderFinish(commandEncoder, &commandBufferDescriptor);

        //submit command buffer
        wgpuQueueSubmit(queue, 1, &command);

        //present rendered image
        wgpuSurfacePresent(surface);

        //reset
        wgpuTextureViewRelease(targetView);
        wgpuTextureRelease(surfaceTexture.texture);
        wgpuCommandBufferRelease(command);
        wgpuRenderPassEncoderRelease(renderPass);
        wgpuCommandEncoderRelease(commandEncoder);
    }

    void GraphicsManager::CleanUp() {
        wgpuSurfaceUnconfigure(surface);

        wgpuShaderModuleRelease(shaderModule);
        wgpuRenderPipelineRelease(pipeline);
        wgpuAdapterRelease(adapter);
        wgpuDeviceRelease(device);
        wgpuQueueRelease(queue);
        wgpuSurfaceRelease(surface);
    }
}
