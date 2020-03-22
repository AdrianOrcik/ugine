#include "uepch.h"

#include "application.h"
#include "log.h"

#include <glad/glad.h>

namespace Ugine {

	Application* Application::sInstance_ = nullptr;

	// todo: refactor to separate helpers
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		UE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

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

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		// note: first must be set vertexBuffer!
		VertexBuffer_.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = 
			{
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"}
			};

			VertexBuffer_->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = VertexBuffer_->GetLayout();
		for (const auto& element : layout)
		{
			// todo: refactor to more efficient
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(uintptr_t)element.Offset);
			index++;
		}

		unsigned int indices[3] = { 0,1,2 };
		IndexBuffer_.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		
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