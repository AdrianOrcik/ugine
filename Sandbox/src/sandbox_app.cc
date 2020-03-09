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
	return new Sandbox();
}