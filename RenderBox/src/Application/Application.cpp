#include "Application.h"
#include "Events/EventDispatcher.h"
#include "Events/InputEvents.h"

#include "glShader.h"
#include "stb_image.h"

#include "Math/Vec3.h"
#include "Math/Mat4.h"

#include "Graphics/VirtualCamera.h"
#include "Utility/Log.h"


namespace Rb {


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		window = std::make_unique<Window>("Hello world", 1200.0f, 800.0f);
		window->Create();
		window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		input = std::make_shared<Input>();

		//Run();
	}

	Application::~Application() {}

	void Application::Run()
	{

		Log::Init();
		LOG_ERROR("poepie");
		LOG_INFO("poepie");
		LOG_WARN("poepie");
		LOG_TRACE("poepie");


		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		glShader ourShader("res/shaders/test.shader");

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);


		unsigned int vbo;
		glCreateBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		unsigned int ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		int width, height, nrChannels;
		unsigned char *data = stbi_load("res/textures/container.jpg", &width, &height, &nrChannels, 0);

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		VirtualCamera camera;

		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "proj");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, camera.GetProjectionMatrix().DataPointer());

		Vec2 Position;
		float deltaTime = 0.0f;



		while (running) {
			window->Clear();

			Mat4 henk(1.0);
			Mat4 rot(1.0);
			Mat4 rot2(1.0);
			Mat4 transfomers(1.0);

			henk = Mat4::Scale(Vec3(10.0f, 1.0f, 1.0f));

			//rot = Mat4::Rotate();
			//rot2 = Mat4::Rotate();


			Position += Input::GetMousePositionRelative();

			Quaternion q1 = Quaternion::AngleAxis(Position.y * 0.06f, Vec3(1, 0, 0));
			Quaternion q2 = Quaternion::AngleAxis(Position.x * 0.06f, Vec3(0, 1, 0));

			Quaternion q3 = q1.Multiply(q2);

			camera.SetRotation(q3);
			camera.Translate(Vec3(Input::GetVertical(), 0.0f, -Input::GetHorizontal()) * deltaTime * 3);

			//std::cout << Input::GetHorizontal() << "   " << Input::GetVertical() << std::endl;

			transfomers = Mat4::Translate(Vec3(0, 0, -2.5f));

			rot2 = Mat4::Rotate(q3);
			rot2 *= transfomers;

			henk = transfomers;

			GLfloat* test = henk.DataPointer();
			unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, test);

			transformLoc = glGetUniformLocation(ourShader.ID, "view");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, camera.GetViewMatrix().DataPointer());

			glDrawArrays(GL_TRIANGLES, 0, 36);

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

