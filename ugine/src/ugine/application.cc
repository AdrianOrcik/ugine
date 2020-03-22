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

		// create vertex buffer
		VertexArray_.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		
		// allocate vertex buffer memory
		std::shared_ptr<VertexBuffer> vertexBuffer;
		// create vertex buffer obj
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		// create buffer layout
		BufferLayout layout = 
		{
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color" }
		};
		
		// set layout
		vertexBuffer->SetLayout(layout);
		// add buffer into vertex array
		VertexArray_->AddVertexBuffer(vertexBuffer);

		// define indices
		unsigned int indices[3] = { 0,1,2 };
		// allocate index buffer
		std::shared_ptr<IndexBuffer> indexBuffer;
		// create index buffer object
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		// set index buffer for vertex array
		VertexArray_->SetIndexBuffer(indexBuffer);
		
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
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
			VertexArray_->Bind();
			glDrawElements(GL_TRIANGLES, VertexArray_->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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