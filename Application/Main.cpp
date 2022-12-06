#include "Engine.h" 
#include <iostream> 

#define POST_PROCESS 
//#define PIXEL

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

	//create framebuffer texture
	auto texture = std::make_shared<neu::Texture>();
#ifdef PIXEL
	texture->CreateTexture(64, 64);
#else
	texture->CreateTexture(1024, 1024);
#endif // PIXEL
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);

	//create framebuffer
	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer","fb_texture");
	framebuffer->Unbind();

	glm::mat4 model(1);

	glm::vec3 cameraPosition = glm::vec3{ 0, 2, 2 };
	float speed = 3;

	auto scene = std::make_unique<neu::Scene>();
	scene->Create("Scenes/rtt.scn");

	auto actor = scene->GetActorFromName("Light");
	if (actor)
	{
		// move light using sin wave 
		actor->m_transform.position.x = std::sin(neu::g_time.time);
	}

	float x = 0;
	float ri = 1;
	float i = 1;
	glm::vec3 rot{ 0,0,0 };
	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		//auto actors = scene->GetActorsFromTag("RTT");
		//float offset = 0.0f;
		//for (auto actor : actors) {
		//	actor->m_transform.position.y = std::sin((neu::g_time.time * 1.4) + offset);
		//	offset += 0.2f;
		//}

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
		auto program = neu::g_resources.Get<neu::Program>("shaders/fx/trueref.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("i", i );
			program->SetUniform("ri", ri);
		}
		/*auto program2 = neu::g_resources.Get<neu::Program>("shaders/postprocess/postprocess.prog");
		if (program2)
		{
			program2->Use();
			program2->SetUniform("offset", neu::g_time.time);
		}*/

		ImGui::Begin("Transform"); {
			//ImGui::Button("Press Me!");
			//ImGui::SliderFloat("X", &x, -90.0f, 90.0f);
			ImGui::DragFloat3("X", &rot[0], 1.0f, -360.0f, 360.0f);
			ImGui::DragFloat("Refaction Index", &ri, 0.005f, 1.0f, 3.9f);
			ImGui::DragFloat("Interpolation", &i, 0.005f, 0.0f, 1.0f);
			//ImGui::SliderFloat3("X", &rot[0], -360.0f, 360.0f);
		} ImGui::End();

		scene->Update();


#ifdef POST_PROCESS 


		// don't draw post process actor when rendering to the framebuffer 
		{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		// render pass 1 (render scene to framebuffer) 
		neu::g_renderer.SetViewport(0, 0, framebuffer -> GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);

		// draw only the post process actor to the screen 
		{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(neu::g_renderer);
			}
		}

#else 
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
#endif // POST_PROCESS 
		

		neu::g_gui.Draw();

	    neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();
	}

	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();

	return 0;
}