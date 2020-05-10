#include <ugine.h>
#include <ugine/entry_point.h>

// todo: implement layer manager
#include "layers/sandbox_2d.h"
#include "layers/example_layer.h"

class Sandbox : public Ugine::Application
{
public:
	Sandbox()
	{	
		//PushLayer(new ExampleLayer());
		PushLayer(DBG_NEW Sandbox2D);
	}

	~Sandbox()
	{
		
	}
};

// called by ugine\entry_point.h
Ugine::Application* Ugine::CreateApplication() 
{
	LOG_TRACE("Sandbox Created!");
	return DBG_NEW Sandbox();
}