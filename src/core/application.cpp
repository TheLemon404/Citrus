#include "application.hpp"

#include "log.hpp"
#include "scene/components/generic/transformComponent.hpp"
#include "scene/components/graphics/meshComponent.hpp"

namespace Citrus {
    Application::Application() :
    window(1024, 768, "Citrus"),
    graphicsManager(window),
    sceneManager() {
    }

    void Application::Run() {
        Log::Init();
        window.Open();
        glfwSetWindowUserPointer(window.GetGLFWWindow(), this);
        graphicsManager.Init();

        //debug
        entt::entity e = sceneManager.GetCurrentScene().registry.create();
        sceneManager.GetCurrentScene().registry.emplace<MeshComponent>(e);
        sceneManager.GetCurrentScene().registry.emplace<TransformComponent>(e);
        MeshComponent& m = sceneManager.GetCurrentScene().registry.get<MeshComponent>(e);
        m.mesh = std::make_shared<Mesh>();

        while (!window.ShouldClose()) {
            sceneManager.GetCurrentScene().Update();
            graphicsManager.Draw(sceneManager.GetCurrentScene());
            window.SwapBuffersAndPoll();
        }

        graphicsManager.CleanUp();
        window.Close();
    }
}
