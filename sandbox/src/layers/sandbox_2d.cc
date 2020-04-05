#include "sandbox_2d.h"
#include "imgui/imgui.h"

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "platform/opengl/opengl_shader.h"

//todo: root assets structure copy to bin build folder during building process
//		or somehow make references

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), cameraController_(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
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
	//todo: implement square indices count formula into index buffer
	squareIB.reset(Ugine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	squareVA_->SetIndexBuffer(squareIB);

	flatColorShader_ = Ugine::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Ugine::Timestep ts)
{
	// camera update
	Ugine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Ugine::RenderCommand::Clear();

	Ugine::Renderer::BeginScene(cameraController_.GetCamera());

	std::dynamic_pointer_cast<Ugine::OpenGLShader>(flatColorShader_)->Bind();
	std::dynamic_pointer_cast<Ugine::OpenGLShader>(flatColorShader_)->SetUniformFloat4("uColor", squareColor_);

	Ugine::Renderer::Submit(flatColorShader_, squareVA_, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	Ugine::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor_));
	ImGui::End();
}

void Sandbox2D::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}
