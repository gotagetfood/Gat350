#include "Engine.h" 
#include <iostream> 

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
	neu::g_gui.Initialize(neu::g_renderer);

	glm::mat4 model(1);

	glm::vec3 cameraPosition = glm::vec3{ 0, 2, 2 };
	float speed = 3;

	auto scene = std::make_unique<neu::Scene>();
	scene->Create("Scenes/cubemap.scn");

	auto actor = scene->GetActorFromName("Light");
	if (actor)
	{
		// move light using sin wave 
		actor->m_transform.position.x = std::sin(neu::g_time.time);
	}

	float x = 0;
	glm::vec3 rot{ 0,0,0 };
	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		scene->Update();

		actor = scene->GetActorFromName("mainboi");
		if (actor)
		{
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}
		actor = scene->GetActorFromName("Light");
		if (actor)
		{
			actor->m_transform.position += std::sin(neu::g_time.time);
		}

		ImGui::Begin("Hello!"); {
			//ImGui::Button("Press Me!");
			//ImGui::SliderFloat("X", &x, -90.0f, 90.0f);
			ImGui::SliderFloat3("X", &rot[0], -360.0f, 360.0f);
		} ImGui::End();

		neu::g_renderer.BeginFrame(); {

			scene->PreRender(neu::g_renderer);
			scene->Render(neu::g_renderer);

			neu::g_gui.Draw();

	    } neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();
	}

	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();

	return 0;
}