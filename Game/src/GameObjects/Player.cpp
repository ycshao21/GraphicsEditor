#include "Player.h"

#include "../Level.h"

void Player::Init()
{
	m_Transform.Translation = glm::vec2(0.0f, 50.0f);
	m_Transform.Rotation = 0.0f;
	m_Transform.Scale = { 60.0f, 70.0f };

	m_Velocity = glm::vec2(150.0f, 0.0f);

	m_BulletCount = 3;

	m_Plane.Vertices = {
		{0.95f, 0.0f},
		{0.9f, 0.1f},
		{0.85f, 0.2f},
		{0.7f, 0.3f},
		{0.4f,0.3f},
		{0.4f,0.5f},
		{0.0f,0.5f},
		{0.0f,0.3f},
		{-0.4f,0.3f},
		{-0.75f,0.2f},
		{-0.8f,0.2f},
		{-0.8f,0.25f},
		{-0.9f,0.25f},
		{-0.9f,-0.3f},
		{-0.8f,-0.3f},
		{-0.8f,-0.25f},
		{-0.75f,-0.25f},
		{-0.5f,-0.3f},
		{0.7f,-0.3f},
		{0.85f,-0.2f},
		{0.9f,-0.1f}
	};
	m_Plane.Color = glm::vec3(0.6f, 0.4f, 0.2f);

	m_Windows[0].Center = glm::vec2{ 0.6f,0.0f };
	m_Windows[0].Radius = 0.1f;
	m_Windows[0].LineWidth = 2.0f;
	m_Windows[0].Color = glm::vec3(0.7f);

	m_Windows[1].Center = glm::vec2{ 0.3f,0.0f };
	m_Windows[1].Radius = 0.1f;
	m_Windows[1].LineWidth = 2.0f;
	m_Windows[1].Color = glm::vec3(0.7f);

	m_Windows[2].Center = glm::vec2{ 0.0f,0.0f };
	m_Windows[2].Radius = 0.1f;
	m_Windows[2].LineWidth = 2.0f;
	m_Windows[2].Color = glm::vec3(0.7f);

	// Particle System
	{
		m_SmokeProps.Position = glm::vec2(0.0f);

		m_SmokeProps.Velocity = glm::vec2(-50.0f, 0.0f);
		m_SmokeProps.VelocityVariation = glm::vec2(26.0f, 40.0f);

		m_SmokeProps.BeginSize = 6.0f;
		m_SmokeProps.EndSize = 0.0f;
		m_SmokeProps.SizeVariation = 5.0f;

		m_SmokeProps.LifeTime = 1.8f;
		m_SmokeProps.LifeRemaining = 1.8f;

		m_SmokeProps.Color = glm::vec3(0.7f);
		m_SmokeProps.ColorVariation = 0.15f;
	}
}

void Player::OnUpdate(float ts)
{
	m_SmokeGenerator.OnUpdate(ts);

	if (Grafix::Input::IsKeyPressed(Grafix::Key::Up))
	{
		if (m_Velocity.y < 0.0f)
			m_Velocity.y += m_Power * 2.0f;
		else
			m_Velocity.y += m_Power;

		glm::mat3 rotationMatrix = Grafix::Math::CalcRotationMatrix(glm::radians(m_Transform.Rotation));
		m_SmokeProps.Position = m_Transform.Translation + Grafix::Math::Transform(rotationMatrix, glm::vec2(-50.0f, 0.0f));
		m_SmokeProps.Velocity.x = -0.7f * m_Velocity.x;
		m_SmokeGenerator.Emit(m_SmokeProps);
	}

	// Update velocity: v_t = v_0 - g * t
	m_Velocity.y -= Level::GetGravity();
	m_Velocity.y = glm::clamp(m_Velocity.y, -260.0f, 300.0f);

	// Update position and rotation
	m_Transform.Translation += m_Velocity * ts;
	m_Transform.Rotation = m_Velocity.y / 6.0f;
}

void Player::OnRender()
{
	Grafix::Renderer::DrawPolygon(m_Transform, m_Plane);
	for (int i = 0; i < 3; i++)
		Grafix::Renderer::DrawCircle(m_Transform, m_Windows[i]);
	m_SmokeGenerator.OnRender();
}

std::vector<glm::vec2> Player::GetCollisionPoints() const
{
	return Grafix::Math::Transform(m_Transform.GetTransformMatrix(), m_CollisionPoints);
}
