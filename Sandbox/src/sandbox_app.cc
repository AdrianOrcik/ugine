#include <ugine.h>
#include "imgui/imgui.h"

class ExampleLayer : public Ugine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), camera_(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition_(0.0f)
	{
		// RENDER TRIANGLE
		{
			// create vertex buffer
			triangleVertexArray_.reset(Ugine::VertexArray::Create());

			float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
				 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
			};

			// allocate vertex buffer memory
			std::shared_ptr<Ugine::VertexBuffer> vertexBuffer;
			// create vertex buffer obj
			vertexBuffer.reset(Ugine::VertexBuffer::Create(vertices, sizeof(vertices)));

			// create buffer layout
			Ugine::BufferLayout layout =
			{
				{ Ugine::ShaderDataType::Float3, "a_Position"},
				{ Ugine::ShaderDataType::Float4, "a_Color" }
			};

			// set layout
			vertexBuffer->SetLayout(layout);
			// add buffer into vertex array
			triangleVertexArray_->AddVertexBuffer(vertexBuffer);

			// define indices
			unsigned int indices[3] = { 0,1,2 };
			// allocate index buffer
			std::shared_ptr<Ugine::IndexBuffer> indexBuffer;
			// create index buffer object
			indexBuffer.reset(Ugine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			// set index buffer for vertex array
			triangleVertexArray_->SetIndexBuffer(indexBuffer);

			std::string vertexSrc = R"(
					#version 330 core

					layout(location = 0) in vec3 a_Position;
					layout(location = 1) in vec4 a_Color;

					uniform mat4 uViewProjection;

					out vec3 v_Position;
					out vec4 v_Color;

					void main()
					{
						v_Position = a_Position;
						v_Color = a_Color;
						gl_Position = uViewProjection * vec4(a_Position, 1.0);
					}
				)";

			std::string fragmentSrc = R"(
					#version 330 core

					layout(location = 0) out vec4 color;

					in vec3 v_Position;
					in vec4 v_Color;

					void main()
					{
						color = vec4(v_Position * 0.5 + 0.5, 1.0);
						color = v_Color;
					}
				)";

			triangleShader_.reset(new Ugine::Shader(vertexSrc, fragmentSrc));
		}

		// RENDER BLUE SQUARE
		{
			blueVertexArray_.reset(Ugine::VertexArray::Create());

			float squareVertices[3 * 4] = {
				-0.75f, -0.75f, 0.0f,
				 0.75f, -0.75f, 0.0f,
				 0.75f,  0.75f, 0.0f,
				-0.75f,  0.75f, 0.0f
			};

			std::shared_ptr<Ugine::VertexBuffer> squareVB;
			squareVB.reset(Ugine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

			Ugine::BufferLayout squareLayout =
			{
				{Ugine::ShaderDataType::Float3, "a_Position"}
			};

			squareVB->SetLayout(squareLayout);
			blueVertexArray_->AddVertexBuffer(squareVB);

			unsigned int squareIndices[6] = { 0,1,2, 2,3,0 };

			std::shared_ptr<Ugine::IndexBuffer> squareIB;
			squareIB.reset(Ugine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

			blueVertexArray_->SetIndexBuffer(squareIB);

			std::string BluevertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;

				uniform mat4 uViewProjection;

				out vec3 v_Position;

				void main()
				{
					v_Position = a_Position;
					gl_Position = uViewProjection * vec4(a_Position, 1.0);
				}
			)";

			std::string BluefragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;

				in vec3 v_Position;

				void main()
				{
					color = vec4(0.0, 0.0, 1.0, 1.0);
				}
			)";

			blueShader_.reset(new Ugine::Shader(BluevertexSrc, BluefragmentSrc));
		}
	}

	void OnUpdate(Ugine::Timestep ts) override
	{
		//LOG_INFO("ExampleLayer::Update");

		//if (Ugine::Input::IsKeyPressed(INPUT_KEY_SPACE))
		//	LOG_TRACE("Pressed");

		if (Ugine::Input::IsKeyPressed(INPUT_KEY_LEFT))
			cameraPosition_.x -= cameraMoveSpeed_ * ts;
		else if (Ugine::Input::IsKeyPressed(INPUT_KEY_RIGHT))
			cameraPosition_.x += cameraMoveSpeed_ * ts;

		if (Ugine::Input::IsKeyPressed(INPUT_KEY_UP))
			cameraPosition_.y += cameraMoveSpeed_ * ts;
		else if (Ugine::Input::IsKeyPressed(INPUT_KEY_DOWN))
			cameraPosition_.y -= cameraMoveSpeed_ * ts;

		if (Ugine::Input::IsKeyPressed(INPUT_KEY_A))
			cameraRotation_ += cameraRotationSpeed_ * ts;
		if (Ugine::Input::IsKeyPressed(INPUT_KEY_D))
			cameraRotation_ -= cameraRotationSpeed_ * ts;
		
		Ugine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0 });
		Ugine::RenderCommand::Clear();

		camera_.SetPosition(cameraPosition_);
		camera_.SetRotation(cameraRotation_);

		Ugine::Renderer::BeginScene(camera_);
			
		Ugine::Renderer::Submit(blueShader_, blueVertexArray_);
		Ugine::Renderer::Submit(triangleShader_, triangleVertexArray_);
			
		Ugine::Renderer::EndScene();
	}

	void OnEvent(Ugine::Event& event) override
	{
		LOG_INFO("{0}", event);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

private:
	std::shared_ptr<Ugine::Shader> triangleShader_;
	std::shared_ptr<Ugine::VertexArray> triangleVertexArray_;

	std::shared_ptr<Ugine::Shader> blueShader_;
	std::shared_ptr<Ugine::VertexArray> blueVertexArray_;

	Ugine::OrthographicCamera camera_;
	glm::vec3 cameraPosition_;
	float cameraMoveSpeed_ = 5.0f;

	float cameraRotation_ = 0.0f;
	float cameraRotationSpeed_ = 180.0f;
};


class Sandbox : public Ugine::Application
{
public:
	Sandbox()
	{	
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
		
	}
};

// called by ugine\entry_point.h
Ugine::Application* Ugine::CreateApplication() 
{
	LOG_TRACE("Sandbox Created!");
	return new Sandbox();
}