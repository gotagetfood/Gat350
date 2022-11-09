#include "Material.h" 
#include "Engine.h" 

namespace neu
{
	bool Material::Create(std::string filename, ...)
	{
		// load program json document 
		rapidjson::Document document;
		bool success = neu::json::Load(filename, document);
		if (!success)
		{

			LOG("Could not load program file (%s).", filename.c_str());
			return false;
		}

		// read the program name 
		std::string program;
		READ_DATA(document, program);
		// get program resource 
		m_program = neu::g_resources.Get<neu::Program>(program);

		// read the texture name 
		std::vector<std::string> textures;
		READ_DATA(document, textures);
		for (auto textures : textures)
		{
			// get texture resource 

			m_textures.push_back(neu::g_resources.Get<neu::Texture>(textures));
		}

		// read colors 
		READ_DATA(document, color);
		READ_DATA(document, shininess);

		// read uvs
		READ_DATA(document, uv_tilling);
		READ_DATA(document, uv_offset);

		return true;
	}

	void Material::Bind()
	{
		m_program->Use();
		m_program->SetUniform("material.color", color);
		m_program->SetUniform("material.shininess", shininess);
		m_program->SetUniform("material.uv_tiling", uv_tilling);
		m_program->SetUniform("material.uv_offset", uv_offset);

		for (size_t i = 0; i < m_textures.size(); i++)
		{
			m_textures[i]->SetActive(GL_TEXTURE0 + (int)i);
			m_textures[i]->Bind();
		}
	}
}