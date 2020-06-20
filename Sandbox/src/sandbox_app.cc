#include <ugine.h>
#include <ugine/entry_point.h>

#include "layers/sandbox2D.h"

class Sandbox : public Ugine::Application
{
public:
	Sandbox()
	{	
		PushLayer(DBG_NEW Sandbox2D);
	}

	~Sandbox()
	{
		
	}
};

// called by ugine\entry_point.h
Ugine::Application* Ugine::CreateApplication() 
{
	LOG_INFO("App Created!");
	return DBG_NEW Sandbox();
}