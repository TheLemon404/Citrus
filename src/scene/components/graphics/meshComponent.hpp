#pragma once

#include <core/core.hpp>
#include <entt/entt.hpp>

#include "graphics/types/mesh.hpp"

namespace Citrus {
    struct CITRUS_API MeshComponent {
        std::shared_ptr<Mesh> mesh;
    };
}
