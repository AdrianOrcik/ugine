#ifndef UE_ENTRYPOINT
#define UE_ENTRYPOINT

#ifdef UE_PLATFORM_WINDOWS
	
	// define extern function
	extern Ugine::Application* Ugine::CreateApplication();

	// called automaticly by system
	int main(int argc, char** argv)
	{
		Ugine::Log::Init();
		CORE_LOG_TRACE("INIT LOG!");
		LOG_WARN("Test");
		auto app = Ugine::CreateApplication();
		app->Run();
		delete app;
	}

#endif // UE_PLATFORM_WINDOWS
#endif // !UE_ENTRYPOINT
