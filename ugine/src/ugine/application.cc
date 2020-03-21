#include "uepch.h"

#include "application.h"
#include "log.h"

#include <glad/glad.h>

namespace Ugine {

	Application* Application::sInstance_ = nullptr;

	Application::Application()
	{
		UE_CORE_ASSERT(!sInstance_, "Application already exist!");
		sInstance_ = this;

		window_ = std::unique_ptr<Window>(Window::Create());
		window_->SetEventCallback(BIND_EVENT_APPLICATION(OnEvent));

		imGuiLayer_ = new ImGuiLayer();
		PushOverlay(imGuiLayer_);

		// render definition
		glGenVertexArrays(1, &VertexArray_);
		glBindVertexArray(VertexArray_);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		VertexBuffer_.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indices[3] = { 0,1,2 };
		IndexBuffer_.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		Shader_.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
		delete &layerStack_;
		delete &window_;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack_.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) 
	{
		layerStack_.PushOverlay(layer);
		layer->OnAttach();
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_APPLICATION(OnWindowClose));

		//CORE_LOG_TRACE("{0}", e);

		for (auto it = layerStack_.end(); it != layerStack_.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (isRunning_)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			Shader_->Bind();
			glBindVertexArray(VertexArray_);
			glDrawElements(GL_TRIANGLES, IndexBuffer_->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : layerStack_)
				layer->OnUpdate();

			// application gui render
			imGuiLayer_->Begin();
			for (Layer* layer : layerStack_)
				layer->OnImGuiRender();
			imGuiLayer_->End();

			window_->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning_ = false;
		return true;
	}

}