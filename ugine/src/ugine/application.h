#ifndef UE_APPLICATION
#define UE_APPLICATION

#include "core.h"

namespace Ugine {
	class UE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// used by client sandbox
	// declaration of function, entry_point.h mark as external
	Application* CreateApplication();
}

#endif // !UE_APPLICATION
