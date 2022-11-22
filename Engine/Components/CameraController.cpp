#include "CameraController.h" 
#include "Engine.h" 

namespace neu
{
	void CameraController::Initialize(){
		glm::vec3 v = math::QuaternionToEuler(m_owner->m_transform.rotation);
		m_pitch = v.x;
		m_yaw = v.y;
	}

	void CameraController::Update()
	{
		// get camera rotation
		if (g_inputSystem.GetButtonState(2) == InputSystem::KeyState::Held)
		{
			glm::vec2 axis = g_inputSystem.GetMouseRelative() * 0.4f;

			m_yaw += axis.x;
			m_pitch -= axis.y;
			m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);
		}

		glm::vec3 forward;
		forward.x = cos(glm::radians(m_yaw - 90.0f)) * cos(glm::radians(m_pitch));
		forward.y = sin(glm::radians(m_pitch));
		forward.z = sin(glm::radians(m_yaw - 90.0f)) * cos(glm::radians(m_pitch));
		forward = glm::normalize(forward);

		glm::mat4 view = glm::lookAt(glm::vec3{ 0.0f }, -forward, glm::vec3{ 0, 1, 0 });
		m_owner->m_transform.rotation = glm::conjugate(glm::quat_cast(view));

		glm::vec3 direction{ 0 };

		if (g_inputSystem.GetKeyState(key_left) == InputSystem::KeyState::Held)		direction.x += 1;
		if (g_inputSystem.GetKeyState(key_right) == InputSystem::KeyState::Held)	direction.x -= 1;
		if (g_inputSystem.GetKeyState(key_up) == InputSystem::KeyState::Held)		direction.z += 1;
		if (g_inputSystem.GetKeyState(key_down) == InputSystem::KeyState::Held)		direction.z -= 1;
		if (g_inputSystem.GetKeyState(key_pgup) == InputSystem::KeyState::Held)	    direction.y += 1;
		if (g_inputSystem.GetKeyState(key_pgdn) == InputSystem::KeyState::Held)		direction.y -= 1;

		// convert world direction space to camera direction space
		direction = m_owner->m_transform.rotation * direction;
		m_owner->m_transform.position += direction * (speed * g_time.deltaTime);

	}

	void CameraComponent::SetProgram(std::shared_ptr<Program> program)
	{
		program->Use();
		program->SetUniform("view", m_view);
		program->SetUniform("projection", m_projection);
	}

	bool CameraController::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool CameraController::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);

		return true;
	}

}
