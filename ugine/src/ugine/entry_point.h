#ifndef UE_ENTRYPOINT
#define UE_ENTRYPOINT

#ifdef UE_PLATFORM_WINDOWS
	
	// define extern function
	extern Ugine::Application* Ugine::CreateApplication();

	// called automaticly by system
	int main(int argc, char** argv)
	{
		auto app = Ugine::CreateApplication();
		app->Run();
		delete app;
	}

#endif // UE_PLATFORM_WINDOWS
#endif // !UE_ENTRYPOINT
