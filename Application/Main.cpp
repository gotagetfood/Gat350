#include "Engine.h" 
#include <iostream> 

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f
};

int main(int argc, char** argv)
{
	LOG("Application Started...");
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();
	LOG("Engine Initialized...");

	neu::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Initialized...");

	// create vertex buffer
	std::shared_ptr<neu::VertexBuffer> vb = neu::g_resources.Get<neu::VertexBuffer>("box");
	vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);
	vb-> SetAttribute(0, 3, 8 * sizeof(float), 0);
	vb-> SetAttribute(1, 3, 8 * sizeof(float), 3*sizeof(float));
	vb-> SetAttribute(2, 2, 8 * sizeof(float), 6*sizeof(float));

	// create shader
	//std::shared_ptr<neu::Shader> vs = neu::g_resources.Get<neu::Shader>("Shaders/basic.vert",GL_VERTEX_SHADER);
	//std::shared_ptr<neu::Shader> fs = neu::g_resources.Get<neu::Shader>("Shaders/basic.frag",GL_FRAGMENT_SHADER);

	// create program
	std::shared_ptr<neu::Program> program = neu::g_resources.Get<neu::Program>("Shaders/basic.prog");
	program->Link();
	program->Use();

	// create texture 
	//std::shared_ptr<neu::Texture> texture1 = neu::g_resources.Get<neu::Texture>("textrues/llama.jpg"); 
	//std::shared_ptr<neu::Texture> texture2 = neu::g_resources.Get<neu::Texture>("textures/wood.png"); 
	//texture1->Bind();

	// create material 
	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("materials/box.mtrl");
	material->Bind();
	
	//fun stuff
	glm::mat4 mx{ 1 };
	glm::mat4 model(1);
	glm::mat4 projection = glm::perspective(45.0f, neu::g_renderer.GetWidth() / (float)neu::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition = glm::vec3{ 0, 2, 2 };
	float speed = 3;

	std::vector<neu::Transform> t;
	for (size_t i = 0; i < 50; i++) {
		t.push_back({ {neu::random(i * -1,i + 1),neu::random(i * - 1,i + 1),neu::random(i * - 1,i + 1)},{neu::randomf(360.0f),90,0} });
	}

	/*
	neu::Transform transforms[] = {
		{ {0,0,0},{0,180,0} },
		{ {0,0,2},{0,0,45} },
		{ {0,1,0},{0,90,180} },
		{ {5,0,1},{45,0,0} },
		{ {0,3,0},{0,90,90} },
		{ {2,0,1},{270,90,90} },
		{ {0,2,5},{180,90,0} },
	};*/

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		//fun stuff movements
		if (neu::g_inputSystem.GetKeyState(neu::key_left)  == neu::InputSystem::KeyState::Held) cameraPosition.x += speed * neu::g_time.deltaTime;
		if (neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::KeyState::Held) cameraPosition.x -= speed * neu::g_time.deltaTime;
		if (neu::g_inputSystem.GetKeyState(neu::key_up)    == neu::InputSystem::KeyState::Held) cameraPosition.z += speed * neu::g_time.deltaTime;
		if (neu::g_inputSystem.GetKeyState(neu::key_down)  == neu::InputSystem::KeyState::Held) cameraPosition.z -= speed * neu::g_time.deltaTime;
		if (neu::g_inputSystem.GetKeyState(neu::key_pgup)  == neu::InputSystem::KeyState::Held) cameraPosition.y += speed * neu::g_time.deltaTime;
		if (neu::g_inputSystem.GetKeyState(neu::key_pgdn)  == neu::InputSystem::KeyState::Held) cameraPosition.y -= speed * neu::g_time.deltaTime;

		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{0,0,5}, glm::vec3{0,1,0});
		//cameraPosition = { std::cos(neu::g_time.time), std::sin(neu::g_time.time), std::tan(neu::g_time.time) };
		material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
		material->GetProgram()->SetUniform("scale", 0.5f);
		model = glm::eulerAngleXYZ(0.0f, neu::g_time.time,0.0f);
		//program->SetUniform("scale", std::sin(neu::g_time.time * 3));


		neu::g_renderer.BeginFrame();
			
			for (size_t i = 0; i < t.size(); i++)
			{
				//int randomLmao = neu::random(0, t.size());
				t[i].rotation += glm::vec3{ 45 * std::sin(i) * neu::g_time.deltaTime, 90*std::cos(i) * neu::g_time.deltaTime,90 * std::tan(i) * neu::g_time.deltaTime * 4 };
				glm::mat4 mvp = projection * view * (glm::mat4)t[i];
				material->GetProgram()->SetUniform("mvp", mvp);

				vb->Draw();
				
			}
		
		neu::g_renderer.EndFrame();
	}

	neu::Engine::Instance().Shutdown();

	return 0;
}