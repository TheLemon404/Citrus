#include "graphicsManager.hpp"

#include "core/log.hpp"

namespace Citrus {
    GraphicsManager::GraphicsManager() {

    }

    void GraphicsManager::Init() {
        WGPUInstanceDescriptor desc = {};
        instance = wgpuCreateInstance(&desc);

        InitDevice();
        LoadResources();
        InitBindings();
        InitPipelines();

        CITRUS_CORE_INFO("initialized graphics manager");
    }

    void GraphicsManager::InitDevice() {

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
