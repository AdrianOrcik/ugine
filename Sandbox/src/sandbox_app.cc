#include <ugine.h>

class Sandbox : public Ugine::Application
{
public:
	Sandbox()
	{

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