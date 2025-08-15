#pragma once

#include <core/core.hpp>
#include <entt/entt.hpp>

namespace Citrus {
    class CITRUS_API Scene {
    public:
        entt::registry registry;

        Scene();

        void Update();
    };
}