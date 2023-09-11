#include "EditorLayer.h"

#include "Grafix/Renderer/Image.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

void EditorLayer::Render(Grafix::Scene& scene)
{
    m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
    m_Renderer.Render(scene);
}

void EditorLayer::OnImGuiRender()
{
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_MenuBar;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", nullptr, window_flags);
    {
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("VulkanAppDockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ////ImGui::ShowDemoWindow();

        // Create menu bar
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                {
                    Grafix::Application::Get().Close();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Begin("Tools");
        {
        }
        ImGui::End(); // Tools

        ImGui::Begin("Viewport");
        {
            m_ViewportWidth = (uint32_t)ImGui::GetContentRegionAvail().x;
            m_ViewportHeight = (uint32_t)ImGui::GetContentRegionAvail().y;

            auto image = m_Renderer.GetImage();
            if (image)
            {
                ImGui::Image(image->GetDescriptorSet(),
                    { (float)image->GetWidth(), (float)image->GetHeight() },
                    ImVec2(0, 1), ImVec2(1, 0)
                );
            }

            Render(m_Scene);
        }
        ImGui::End(); // Viewport

        ImGui::Begin("Settings");
        {
            ImGui::Text("FPS: %d", (uint32_t)Grafix::Application::Get().GetFPS());
            ImGui::Separator();

            ImGui::Text("Background");
            ImGui::ColorEdit3("Color", glm::value_ptr(m_Scene.GetBackgroundColor()));
            ImGui::Separator();

            for (int i = 0; i < m_Scene.GetRectangles().size(); ++i)
            {
                auto& rect = m_Scene.GetRectangles()[i];

                ImGui::PushID(i);

                ImGui::Text("Rectangle");
                ImGui::DragFloat2("Position", glm::value_ptr(rect.Position), 2.0f, -2000.0f, 2000.0f);
                ImGui::DragFloat("Width", &rect.Width, 2.0f, 0.0f, 2000.f);
                ImGui::DragFloat("Height", &rect.Height, 2.0f, 0.0f, 2000.f);
                ImGui::ColorEdit3("Color", glm::value_ptr(rect.Color));

                ImGui::PopID();
                ImGui::Separator();
            }
        }
        ImGui::End(); // Settings

        ImGui::Begin("Entities");
        {
        }
        ImGui::End(); // Entities
    }

    ImGui::End(); // DockSpace
}