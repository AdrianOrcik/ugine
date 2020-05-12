#ifndef UE_ENTRYPOINT
#define UE_ENTRYPOINT

#include <crtdbg.h>
#include <stdlib.h>

#ifdef UE_PLATFORM_WINDOWS

	// define extern function
	extern Ugine::Application* Ugine::CreateApplication();

	// called automaticly by system
	int main(int argc, char** argv)
	{
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		Ugine::Log::Init();
		auto app = Ugine::CreateApplication();
		app->Run();
		delete app;

		_CrtDumpMemoryLeaks();
	}

#endif // UE_PLATFORM_WINDOWS
#endif // !UE_ENTRYPOINT
