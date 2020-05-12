#include "uepch.h"

#include "application.h"
#include "log.h"

#include <GLFW/glfw3.h>
#include "ugine/renderer/renderer.h"
#include "ugine/input/input.h"

#include "ugine/ecs/ecs.h"
#include "ugine/coroutines/routine_manager.h"

#include <functional>
#include <iostream>

namespace Ugine {

	Application* Application::sInstance_ = nullptr;
	Application::Application()
	{

		UE_CORE_ASSERT(!sInstance_, "Application already exist!");
		sInstance_ = this;

		window_ = std::unique_ptr<Window>(Window::Create());
		window_->SetEventCallback(BIND_EVENT_APPLICATION(OnEvent));

		Renderer::Init();

		//TODO: memory leak
		imGuiLayer_ = DBG_NEW ImGuiLayer();
		PushOverlay(imGuiLayer_);
	}

	Application::~Application()
	{
	
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
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_APPLICATION(OnWindowResize));

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
			float time = (float)glfwGetTime();
			Timestep timestep = time - lastFrameTime_;
			lastFrameTime_ = time;

			if(!isMinimized_){
				for (Layer* layer : layerStack_)
					layer->OnUpdate(timestep);

				RoutineManager::Update(timestep);
				ECS::Update(timestep);
			}

			// application gui render
			imGuiLayer_->Begin();
			for (Layer* layer : layerStack_)
				layer->OnImGuiRender();
			imGuiLayer_->End();

			window_->OnUpdate();
			AppPoolInput();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning_ = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent & e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			isMinimized_ = true;
			return false;
		}

		isMinimized_ = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	void Application::AppPoolInput()
	{
		if (Input::IsExitButtonPressed())
			isRunning_ = false;
	}

}