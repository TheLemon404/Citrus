#pragma once

#include "core/core.hpp"
#include <webgpu/wgpu.h>

namespace Citrus {
    class CITRUS_API GraphicsManager {
        WGPUInstance instance;

    public:
        GraphicsManager();

    private:
        void InitDevice();
        void LoadResources();
        void InitBindings();
        void InitPipelines();

        void SubmitCommands();

        void FetchResults();

    public:
        void Init();
    };
}
