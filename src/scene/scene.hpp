#pragma once

#include <core/core.hpp>
#include <entt/entt.hpp>

namespace Citrus {
    class CITRUS_API Scene {
        entt::registry registry;

    public:
        Scene();
    };
}