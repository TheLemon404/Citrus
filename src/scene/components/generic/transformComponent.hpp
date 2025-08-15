#pragma once

#include <core/core.hpp>
#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "glm/ext/matrix_transform.hpp"

namespace Citrus {
    struct CITRUS_API TransformComponent {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
        glm::mat4 transform = glm::identity<glm::mat4>();
    };
}
