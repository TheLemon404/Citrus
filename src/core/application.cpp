#include "application.hpp"
#include "log.hpp"
#include "scene/components/generic/transformComponent.hpp"
#include "scene/components/graphics/meshComponent.hpp"

namespace Citrus {
    Application::Application(Window* window)
        : graphicsManager(), sceneManager(), window(window) {
    }

    void Application::Init() {
        Log::Init();

        if (window) {
            graphicsManager.Init(window);
        }

        // Example entity creation (could be moved to host/editor)
        entt::entity e = sceneManager.GetCurrentScene().registry.create();
        sceneManager.GetCurrentScene().registry.emplace<MeshComponent>(e);
        sceneManager.GetCurrentScene().registry.emplace<TransformComponent>(e);
        sceneManager.GetCurrentScene().registry.get<MeshComponent>(e).mesh = std::make_shared<Mesh>();
    }

    void Application::Update() {
        sceneManager.GetCurrentScene().Update();
    }

    ApplicationRenderResult Application::Render() {
        if (!window) {
            CITRUS_CORE_FATAL("Cannot render scene if the engine is in headless mode (pass a window pointer into the application constructor)");
            throw std::runtime_error("Cannot render scene");
        }

        graphicsManager.Draw(sceneManager.GetCurrentScene());
        window->SwapBuffersAndPoll();
        return {};
    }

    void Application::Shutdown() {
        if (window) {
            graphicsManager.CleanUp();
            window->Close();
        }
    }

    bool Application::ShouldClose() {
        if (window) {
            return window->ShouldClose();
        }

        return false;
    }
}
