#ifndef UE_CORE
#define UE_CORE

#ifdef UE_PLATFORM_WINDOWS
	#ifdef UE_BUILD_DLL
		#define UE_API __declspec(dllexport)
	#else
		#define UE_API __declspec(dllimport)
	#endif // UE_BUILD_DLL
#else
	//#error Ugine only supports Windows!

#endif // UE_PLATFORM_WINDOWS

#ifndef UE_ENABLE_ASSERTS
	#define UE_ERROR
	#define UE_CORE_ERROR
	#define UE_ASSERT(x, ...) { if(!(x)) { UE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define UE_CORE_ASSERT(x, ...) { if(!(x)) { UE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define UE_ASSERT(x, ...)
	#define UE_CORE_ASSERT(x, ...)
#endif // !UE_ENABLE_ASSERTS


#define BIT(x)(1<<x)

//todo: check how to work binds
#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#endif // !UE_CORE
