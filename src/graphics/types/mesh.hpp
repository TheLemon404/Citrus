#pragma once

#include <vector>
#include <core/core.hpp>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

namespace Citrus {
    struct CITRUS_API Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 uv;
    };

    class CITRUS_API Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices = {
            0, 1, 2, // Triangle #0 connects points #0, #1 and #2
            0, 2, 3  // Triangle #1 connects points #0, #2 and #3
        };

        std::vector<float> ExtractPositionData();
        std::vector<float> ExtractNormalData();
        std::vector<float> ExtractColorData();
        std::vector<float> ExtractUVData();
    };
}
