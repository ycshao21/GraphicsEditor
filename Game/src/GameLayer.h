#pragma once

#include "Grafix.h"

#include "Level.h"

class GameLayer final : public Grafix::Layer
{
    enum class GameState : uint8_t
    {
        Ready,
        Playing,
        GameOver,
        Win
    };
public:
    GameLayer() = default;
    virtual ~GameLayer() = default;

    virtual void OnAttach() override;
    virtual void OnUpdate(float ts) override;
    virtual void OnUIRender() override;
    virtual void OnEvent(Grafix::Event& e) override;
    virtual void OnDetach() override;
private:
    bool OnKeyPressed(Grafix::KeyPressedEvent& e);

    void UI_Info();
private:
    float m_Time = 0.0f;
    GameState m_GameState = GameState::Ready;

    std::unique_ptr<Level> m_Level = nullptr;
    std::unique_ptr<Grafix::Camera> m_Camera = nullptr;

    // Canvas
    uint32_t m_CanvasWidth = 1280, m_CanvasHeight = 720;

    // Mouse
    glm::vec2 m_MousePosInCanvas{ 0.0f, 0.0f };
    glm::vec2 m_MousePosInWorld{ 0.0f, 0.0f };
    glm::vec2 m_MousePositionDelta = { 0.0f, 0.0f };
};
