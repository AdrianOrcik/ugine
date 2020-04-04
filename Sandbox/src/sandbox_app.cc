#include <ugine.h>
#include <ugine/entry_point.h>

#include "platform/opengl/opengl_shader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TestLayer : public Ugine::Layer
{
public:
	TestLayer()
		:Layer("TestLayer"), cameraController_(1280.0f / 720.0f)
	{

		// RENDER TEXTURE SQUARE	
		{
			textureVA_ = Ugine::VertexArray::Create();

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

			auto textureShader = sharedLibrary_.Load("assets/shaders/texture.glsl");

			texture_ = Ugine::Texture2D::Create("assets/textures/container.jpg");

			std::dynamic_pointer_cast<Ugine::OpenGLShader>(textureShader)->Bind();
			std::dynamic_pointer_cast<Ugine::OpenGLShader>(textureShader)->SetUniformInt("uTexture", 0);
			std::dynamic_pointer_cast<Ugine::OpenGLShader>(textureShader)->SetUniformFloat3("uColor", squareColor_);
		}
	}

	void OnUpdate(Ugine::Timestep ts) override
	{
		// camera update
		cameraController_.OnUpdate(ts);

		// render
		Ugine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0 });
		Ugine::RenderCommand::Clear();


		Ugine::Renderer::BeginScene(cameraController_.GetCamera());

		glm::mat4 transformMatrix = glm::mat4(1.0f);
		auto textureShader = sharedLibrary_.Get("texture");
		texture_->Bind(0);
		std::dynamic_pointer_cast<Ugine::OpenGLShader>(textureShader)->SetUniformFloat3("uColor", squareColor_);
		Ugine::Renderer::Submit(textureShader, textureVA_, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		

		Ugine::Renderer::EndScene();
	}

	void OnEvent(Ugine::Event& e) override
	{
		cameraController_.OnEvent(e);
		LOG_INFO("{0}", e);
	}

	virtual void OnImGuiRender() override
	{

		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor_));
		ImGui::End();
	}

private:

	Ugine::ShaderLibrary sharedLibrary_;

	Ugine::Ref<Ugine::VertexArray> squareVA_;

	Ugine::Ref<Ugine::VertexArray> textureVA_;

	Ugine::Ref<Ugine::Texture2D> texture_;

	glm::vec3 cameraPosition_;
	float cameraMoveSpeed_ = 5.0f;

	float cameraRotation_ = 0.0f;
	float cameraRotationSpeed_ = 180.0f;

	Ugine::OrthographicCameraController cameraController_;
	glm::vec3 squareColor_ = { 1.0f, 1.0f, 1.0f };
};

class Sandbox2D : public Ugine::Layer
{
public:
	Sandbox2D()
		:Layer("Sandbox2D"), cameraController_(1280.0f / 720.0f)
	{

	}

	virtual void OnAttach() override
	{
		squareVA_ = Ugine::VertexArray::Create();
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ugine::Ref<Ugine::VertexBuffer> squareVB;
		squareVB.reset(Ugine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{Ugine::ShaderDataType::Float3, "aPosition"}
		});
		squareVA_->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ugine::Ref<Ugine::IndexBuffer> squareIB;
		squareIB.reset(Ugine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		squareVA_->SetIndexBuffer(squareIB);

		flatColorShader_ = Ugine::Shader::Create("assets/shaders/FlatColor.glsl");
	}

	virtual void OnDetach() override
	{

	}

	void OnUpdate(Ugine::Timestep ts) override
	{
		// camera update
		cameraController_.OnUpdate(ts);

		// render update
		Ugine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Ugine::RenderCommand::Clear();

		Ugine::Renderer::BeginScene(cameraController_.GetCamera());

		std::dynamic_pointer_cast<Ugine::OpenGLShader>(flatColorShader_)->Bind();
		std::dynamic_pointer_cast<Ugine::OpenGLShader>(flatColorShader_)->SetUniformFloat4("uColor", squareColor_);

		Ugine::Renderer::Submit(flatColorShader_, squareVA_, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		Ugine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor_));
		ImGui::End();
	}

	void OnEvent(Ugine::Event& e) override
	{
		cameraController_.OnEvent(e);
	}

private:
	Ugine::OrthographicCameraController cameraController_;

	// tmp
	Ugine::Ref<Ugine::VertexArray> squareVA_;
	Ugine::Ref<Ugine::Shader> flatColorShader_;

	glm::vec4 squareColor_ = { 0.2f, 0.3f, 0.8f, 1.0f };
};

class Sandbox : public Ugine::Application
{
public:
	Sandbox()
	{	
		//PushLayer(new TestLayer());
		PushLayer(new Sandbox2D);
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