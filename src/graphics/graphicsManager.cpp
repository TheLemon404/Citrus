#include "graphicsManager.hpp"
#include "core/log.hpp"

namespace Citrus {
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
    }

    void GraphicsManager::UncapturedErrorCallback(WGPUDevice const *device, WGPUErrorType type, WGPUStringView message, void *userdata1, void *userdata2) {
        CITRUS_CORE_ERROR("WebGPU Error Callback triggered: ");
        CITRUS_CORE_ERROR(" Error Type: {}", (int)type);
        CITRUS_CORE_ERROR(" Error: {}", std::string(message.data, message.length));
    }

    void GraphicsManager::DeviceLostCallback(WGPUDevice const *device, WGPUDeviceLostReason reason, WGPUStringView message, void *userdata1, void *userdata2) {
        CITRUS_CORE_FATAL("Device lost: ");
        CITRUS_CORE_FATAL(" reason: {}", (int)reason);
        CITRUS_CORE_FATAL(" message: {}", std::string(message.data, message.length));
    }

    void GraphicsManager::Init() {
        instance = wgpuCreateInstance({});

        InitDevice();
        LoadResources();
        InitBindings();
        InitPipelines();

        CITRUS_CORE_INFO("initialized graphics manager");
    }

    void GraphicsManager::InitDevice() {
        //request and setup adapter
        WGPURequestAdapterOptions requestAdapterOptions = {
            .nextInChain = nullptr,
            .powerPreference = graphicalSettings.powerPreference,
            .backendType = graphicalSettings.backendType,
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

    }

    void GraphicsManager::LoadResources() {

    }

    void GraphicsManager::InitBindings() {

    }

    void GraphicsManager::InitPipelines() {

    }

    void GraphicsManager::SubmitCommands() {

    }

    void GraphicsManager::FetchResults() {

    }
}
