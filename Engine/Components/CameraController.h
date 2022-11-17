#pragma once 
#include "Framework/Component.h" 

namespace neu
{
	class CameraController : public Component
	{
	public:
		CLASS_DECLARATION(CameraController)

			void Initialize() override;
			void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		float speed = 0;
	private:

		float m_yaw = 0; //left / right
		float m_pitch = 0; // up / down
	};
}