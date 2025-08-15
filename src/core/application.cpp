#include "application.hpp"

#include "log.hpp"
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

        //debug
        entt::entity e = sceneManager.GetCurrentScene().registry.create();
        sceneManager.GetCurrentScene().registry.emplace<MeshComponent>(e);
        MeshComponent& m = sceneManager.GetCurrentScene().registry.get<MeshComponent>(e);
        m.mesh = std::make_shared<Mesh>();

        graphicsManager.Init();

        while (!window.ShouldClose()) {
            graphicsManager.Draw(sceneManager.GetCurrentScene());
            window.SwapBuffersAndPoll();
        }

        graphicsManager.CleanUp();
        window.Close();
    }
}
