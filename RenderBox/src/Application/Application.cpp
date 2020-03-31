#include "Application.h"
#include "Events/EventDispatcher.h"
#include "Events/InputEvents.h"

#include "Opengl/Shader.h"
#include "Opengl/Texture.h"
#include "Opengl/Mesh.h"

#include "stb_image.h"

#include "Math/Vec3.h"
#include "Math/Mat4.h"

#include "Graphics/Camera/VirtualCamera.h"
#include "Utility/Log.h"
#include "Opengl/Renderer.h"

#include "Game/LevelGeneration.h"
#include "Game/World.h"


namespace Rb {


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		Log::Init();
		time->Init();


		window = std::make_unique<Window>("Hello world", 1200.0f, 800.0f);
		window->Create();
		window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		input = std::make_shared<Input>();
		

		//Run();
	}

	Application::~Application() {}

	void Application::Run()
	{

		Vertex vertices[] = {


			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 0.0f)),
			Vertex(Vec3( 0.5f, -0.5f, -0.5f), Vec2( 1.0f, 0.0f)),
			Vertex(Vec3( 0.5f,  0.5f, -0.5f), Vec2( 1.0f, 1.0f)),
			Vertex(Vec3( 0.5f,  0.5f, -0.5f), Vec2( 1.0f, 1.0f)),
			Vertex(Vec3(-0.5f,  0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 0.0f)),
										
			Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2( 0.0f, 0.0f)),
			Vertex(Vec3( 0.5f, -0.5f,  0.5f), Vec2( 1.0f, 0.0f)),
			Vertex(Vec3( 0.5f,  0.5f,  0.5f), Vec2( 1.0f, 1.0f)),
			Vertex(Vec3( 0.5f,  0.5f,  0.5f), Vec2( 1.0f, 1.0f)),
			Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2( 0.0f, 1.0f)),
			Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2( 0.0f, 0.0f)),
											
			Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2( 1.0f, 0.0f)),
			Vertex(Vec3(-0.5f,  0.5f, -0.5f), Vec2( 1.0f, 1.0f)),
			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
			Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2( 0.0f, 0.0f)),
			Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2( 1.0f, 0.0f)),
											
			Vertex(Vec3( 0.5f,  0.5f,  0.5f), Vec2( 1.0f, 0.0f)),
			Vertex(Vec3( 0.5f,  0.5f, -0.5f), Vec2( 1.0f, 1.0f)),
			Vertex(Vec3( 0.5f, -0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
			Vertex(Vec3( 0.5f, -0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
			Vertex(Vec3( 0.5f, -0.5f,  0.5f), Vec2( 0.0f, 0.0f)),
			Vertex(Vec3( 0.5f,  0.5f,  0.5f), Vec2( 1.0f, 0.0f)),
										
			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
			Vertex(Vec3( 0.5f, -0.5f, -0.5f), Vec2( 1.0f, 1.0f)),
			Vertex(Vec3( 0.5f, -0.5f,  0.5f), Vec2( 1.0f, 0.0f)),
			Vertex(Vec3( 0.5f, -0.5f,  0.5f), Vec2( 1.0f, 0.0f)),
			Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2( 0.0f, 0.0f)),
			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
										
			Vertex(Vec3(-0.5f,  0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
			Vertex(Vec3( 0.5f,  0.5f, -0.5f), Vec2( 1.0f, 1.0f)),
			Vertex(Vec3( 0.5f,  0.5f,  0.5f), Vec2( 1.0f, 0.0f)),
			Vertex(Vec3( 0.5f,  0.5f,  0.5f), Vec2( 1.0f, 0.0f)),
			Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2( 0.0f, 0.0f)),
			Vertex(Vec3(-0.5f,  0.5f, -0.5f), Vec2( 0.0f, 1.0f))
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		Shader ourShader("res/shaders/test.shader");

		Texture floor("res/textures/atlas.png");



		

		VirtualCamera camera;

		ourShader.setMat4("proj", camera.GetProjectionMatrix());

		Vec2 Position;
		float deltaTime = 0.0f;

		Renderer renderer;

		float x = 0;

		LevelGenerator generator(3.0f);

		std::vector<Vertex> buffer;
		World world("res/textures/level.png",3.0f);
		generator.GenerateLevel(world,&buffer);


		//Mesh mesh(std::vector<Vertex>(&vertices[0], &vertices[6 * 6]));
		Mesh mesh(buffer);



		while (running) {
			window->Clear();

			Position += Input::GetMousePositionRelative();

			Quaternion q1 = Quaternion::AngleAxis(Position.y * 0.06f, Vec3(1, 0, 0));
			Quaternion q2 = Quaternion::AngleAxis(Position.x * 0.06f, Vec3(0, 1, 0));

			Quaternion q3 = q1.Multiply(q2);

			camera.SetRotation(q3);

			Vec3 translation = Vec3(Input::GetHorizontal(), 0.0f, -Input::GetVertical()) * deltaTime * 3;
			std::cout << Input::GetVertical() << "  " << translation.z << std::endl;
			
			if (world.IsPositionFree(camera.position + Vec3(translation.x, 0, 0))) {
				camera.Translate(Vec3(translation.x, 0, 0));
			}
			if (world.IsPositionFree(camera.position + Vec3(0,translation.y, 0))) {
				camera.Translate(Vec3(0, translation.y, 0));
			}
			if (world.IsPositionFree(camera.position + Vec3(0,0,translation.z))) {
				camera.Translate(Vec3(0, 0,translation.z));
			}

			//camera.position = Vec3(10, 3, 10);

			glVertex2i(10, 10);

			float d = Time::GetDeltaTime();

			ourShader.setMat4("view", camera.GetViewMatrix());

			//ourShader.setMat4("view", Mat4(1.0f));

			renderer.Draw(mesh, ourShader, floor, Mat4(1.0f));

			window->Update();
			input->Update();
			time->Update();

			if (Input::GetKey(256)) {
				running = false;
			}

			deltaTime = Time::GetDeltaTime();
		}
	}

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<OnWindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<KeyEvent>(std::bind(&Input::OnKey, input, std::placeholders::_1));
		dispatcher.Dispatch<MouseMovementEvent>(std::bind(&Input::OnMouseMove, input, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonEvent>(std::bind(&Input::OnMouseButton, input, std::placeholders::_1));

	}

	bool Application::OnWindowClose(OnWindowCloseEvent & e)
	{
		running = false;
		return true;
	}

}

