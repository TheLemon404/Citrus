#include "scene.hpp"

#include "components/generic/transformComponent.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace Citrus {
    Scene::Scene() {

    }

    void Scene::Update() {
        const auto& view = registry.view<TransformComponent>();
        for (entt::entity entity : view) {
            TransformComponent& transformComponent = view.get<TransformComponent>(entity);
            transformComponent.transform = glm::translate(transformComponent.transform, transformComponent.position);
            transformComponent.transform = glm::rotate(transformComponent.transform, transformComponent.rotation.x, glm::vec3(1, 0, 0));
            transformComponent.transform = glm::rotate(transformComponent.transform, transformComponent.rotation.y, glm::vec3(0, 1, 0));
            transformComponent.transform = glm::rotate(transformComponent.transform, transformComponent.rotation.z, glm::vec3(0, 0, 1));
            transformComponent.transform = glm::scale(transformComponent.transform, transformComponent.scale);
        }
    }
}
