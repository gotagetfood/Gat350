#include "ModelComponent.h"
#include "Renderer/Material.h" 
#include "Renderer/Model.h" 
#include "Framework/Actor.h" 
#include "Engine.h" 

namespace neu
{
	void ModelComponent::Draw(Renderer& renderer)
	{
		material->Bind();
		// set the model matrix (transform to world space) 
		material->GetProgram()->SetUniform("model", (glm::mat4)m_owner->m_transform);

		glDepthMask(depth_test);
		model->m_vertexBuffer.Draw();
	}

	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		// read model name 
		std::string model_name;
		READ_DATA(value, model_name);
		// get model from model name 
		model = g_resources.Get<neu::Model>(model_name);

		// read material name 
		std::string material_name;
		READ_DATA(value, material_name);
		// get material from material name 
		material = g_resources.Get<neu::Material>(material_name);

		READ_DATA(value, depth_test);

		return true;
	}
}
