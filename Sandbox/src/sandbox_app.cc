#include <ugine.h>

#include "platform/opengl/opengl_shader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Ugine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), camera_(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition_(0.0f)
	{
	/*	// RENDER TRIANGLE
		{
			// create vertex buffer
			triangleVertexArray_.reset(Ugine::VertexArray::Create());

			float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
				 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
			};

			// allocate vertex buffer memory
			Ugine::Ref<Ugine::VertexBuffer> vertexBuffer;
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
			Ugine::Ref<Ugine::IndexBuffer> indexBuffer;
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
		}*/

		// RENDER BLUE SQUARE
		{
			squareVA_.reset(Ugine::VertexArray::Create());

			float squareVertices[3 * 4] = {
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.5f,  0.5f, 0.0f,
				-0.5f,  0.5f, 0.0f
			};

			Ugine::Ref<Ugine::VertexBuffer> squareVB;
			squareVB.reset(Ugine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

			Ugine::BufferLayout squareLayout =
			{
				{Ugine::ShaderDataType::Float3, "aPosition"}
			};

			squareVB->SetLayout(squareLayout);
			squareVA_->AddVertexBuffer(squareVB);

			unsigned int squareIndices[6] = { 0,1,2, 2,3,0 };

			Ugine::Ref<Ugine::IndexBuffer> squareIB;
			squareIB.reset(Ugine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

			squareVA_->SetIndexBuffer(squareIB);

			std::string squareVertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 aPosition;

				uniform mat4 uViewProjection;
				uniform mat4 uTransform;

				out vec3 vPosition;

				void main()
				{
					vPosition = aPosition;
					gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
				}
			)";

			std::string squareFragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;

				in vec3 vPosition;

				uniform vec3 uColor;

				void main()
				{
					color = vec4(uColor, 1.0);
				}
			)";

			squareShader_.reset(Ugine::Shader::Create(squareVertexSrc, squareFragmentSrc));
		}

		// RENDER TEXTURE SQUARE	
		/*{
			textureVA_.reset(Ugine::VertexArray::Create());

			float textureSquareVertices[5 * 4] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
			};

			Ugine::Ref<Ugine::VertexBuffer> textureVB;
			textureVB.reset(Ugine::VertexBuffer::Create(textureSquareVertices, sizeof(textureSquareVertices)));

			Ugine::BufferLayout textureLayout =
			{
				{Ugine::ShaderDataType::Float3, "aPosition"},
				{Ugine::ShaderDataType::Float2, "aTexCoord"}
			};

			textureVB->SetLayout(textureLayout);
			textureVA_->AddVertexBuffer(textureVB);

			unsigned int texIndices[6] = { 0,1,2, 2,3,0 };

			Ugine::Ref<Ugine::IndexBuffer> textureIB;
			textureIB.reset(Ugine::IndexBuffer::Create(texIndices, sizeof(texIndices) / sizeof(uint32_t)));

			textureVA_->SetIndexBuffer(textureIB);

			std::string textureVertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 aPosition;
				layout(location = 1) in vec2 aTexCoord;

				uniform mat4 uViewProjection;
				uniform mat4 uTransform;

				out vec3 vPosition;
				out vec2 vTexCoord;

				void main()
				{
					vPosition = aPosition;
					vTexCoord = aTexCoord;
					gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
				}
			)";

			std::string textureFragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;

				in vec3 vPosition;
				in vec2 vTexCoord;

				uniform sampler2D uTexture;
				
				void main()
				{
					color = texture(uTexture,vTexCoord);
				}
			)";

			textureShader_.reset(Ugine::Shader::Create(textureVertexSrc, textureFragmentSrc));
			texture_ = Ugine::Texture2D::Create("assets/textures/container.jpg");

			std::dynamic_pointer_cast<Ugine::OpenGLShader>(textureShader_)->Bind();
			std::dynamic_pointer_cast<Ugine::OpenGLShader>(textureShader_)->SetUniformInt("uTexture", 0);
		}*/
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
			
		// assign and setup uniform
		//std::dynamic_pointer_cast<Ugine::OpenGLShader>(squareShader_)->Bind();
		//std::dynamic_pointer_cast<Ugine::OpenGLShader>(squareShader_)->SetUniformFloat3("uColor", squareColor_);

		glm::mat4 transformMatrix = glm::mat4(1.0f);
		//glm::vec3 position(1.0f, 0.0f, 0.0f);
		//glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		//transformMatrix = glm::translate(glm::mat4(1.0f), position) * scale;
			
		//solid square
		{
			std::dynamic_pointer_cast<Ugine::OpenGLShader>(squareShader_)->Bind();
			std::dynamic_pointer_cast<Ugine::OpenGLShader>(squareShader_)->SetUniformFloat3("uColor", squareColor_);

			Ugine::Renderer::Submit(squareShader_, squareVA_, transformMatrix);
		}

		//texture square
		//{
		//	texture_->Bind();
		//	Ugine::Renderer::Submit(textureShader_, textureVA_, transformMatrix);
		//}

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

		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor_));
		ImGui::End();
	}

private:
	//Ugine::Ref<Ugine::Shader> triangleShader_;
	//Ugine::Ref<Ugine::VertexArray> triangleVertexArray_;

	Ugine::Ref<Ugine::Shader> squareShader_;
	Ugine::Ref<Ugine::VertexArray> squareVA_;

	Ugine::Ref<Ugine::Shader> textureShader_;
	Ugine::Ref<Ugine::VertexArray> textureVA_;

	Ugine::Ref<Ugine::Texture2D> texture_;

	Ugine::OrthographicCamera camera_;
	glm::vec3 cameraPosition_;
	float cameraMoveSpeed_ = 5.0f;

	float cameraRotation_ = 0.0f;
	float cameraRotationSpeed_ = 180.0f;

	glm::vec3 squareColor_ = { 0.2f, 0.3f, 0.8f };
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