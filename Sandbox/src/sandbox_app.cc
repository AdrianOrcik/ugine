#include <ugine.h>
#include <ugine/entry_point.h>

#include "layers/pathfind_2d.h"

class Sandbox : public Ugine::Application
{
public:
	Sandbox()
	{	
		PushLayer(DBG_NEW Pathfind_2d);
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