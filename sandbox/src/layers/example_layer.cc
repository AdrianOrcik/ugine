#include "example_layer.h"

#include "imgui/imgui.h"

#include "platform/opengl/opengl_shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), cameraController_(1280.0f / 720.0f)
{

}

void ExampleLayer::OnAttach()
{
	//textureVA_ = Ugine::VertexArray::Create();

	//float textureSquareVertices[5 * 4] = {
	//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	//	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	//	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	//	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	//};

	//Ugine::Ref<Ugine::VertexBuffer> textureVB;
	//textureVB.reset(Ugine::VertexBuffer::Create(textureSquareVertices, sizeof(textureSquareVertices)));

	//Ugine::BufferLayout textureLayout =
	//{
	//	{Ugine::ShaderDataType::Float3, "aPosition"},
	//	{Ugine::ShaderDataType::Float2, "aTexCoord"}
	//};

	//textureVB->SetLayout(textureLayout);
	//textureVA_->AddVertexBuffer(textureVB);

	//unsigned int texIndices[6] = { 0,1,2, 2,3,0 };

	//Ugine::Ref<Ugine::IndexBuffer> textureIB;
	//textureIB.reset(Ugine::IndexBuffer::Create(texIndices, sizeof(texIndices) / sizeof(uint32_t)));

	//textureVA_->SetIndexBuffer(textureIB);

	//auto textureShader = sharedLibrary_.Load("assets/shaders/texture.glsl");

	//texture_ = Ugine::Texture2D::Create("assets/textures/container.jpg");

	//std::dynamic_pointer_cast<Ugine::OpenGLShader>(textureShader)->Bind();
	//std::dynamic_pointer_cast<Ugine::OpenGLShader>(textureShader)->SetUniformInt("uTexture", 0);
	//std::dynamic_pointer_cast<Ugine::OpenGLShader>(textureShader)->SetUniformFloat3("uColor", squareColor_);
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Ugine::Timestep ts)
{
	//// camera update
	//cameraController_.OnUpdate(ts);

	//// render
	//Ugine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0 });
	//Ugine::RenderCommand::Clear();


	//Ugine::Renderer::BeginScene(cameraController_.GetCamera());

	//glm::mat4 transformMatrix = glm::mat4(1.0f);
	//auto textureShader = sharedLibrary_.Get("texture");
	//texture_->Bind(0);
	//std::dynamic_pointer_cast<Ugine::OpenGLShader>(textureShader)->SetUniformFloat3("uColor", squareColor_);
	//Ugine::Renderer::Submit(textureShader, textureVA_, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


	//Ugine::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	//ImGui::Begin("Settings");
	//ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor_));
	//ImGui::End();
}

void ExampleLayer::OnEvent(Ugine::Event & e)
{
	//cameraController_.OnEvent(e);
}
