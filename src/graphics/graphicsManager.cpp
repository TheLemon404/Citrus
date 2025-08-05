#include "graphicsManager.hpp"

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