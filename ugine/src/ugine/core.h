#ifndef UE_CORE
#define UE_CORE

#include "uepch.h"

#ifdef UE_PLATFORM_WINDOWS
	#ifdef UE_BUILD_DLL
		#define UE_API __declspec(dllexport)
	#else
		#define UE_API __declspec(dllimport)
	#endif // UE_BUILD_DLL
#else
	//#error Ugine only supports Windows!

#endif // UE_PLATFORM_WINDOWS

#define BIT(x)(1<<x)
#endif // !UE_CORE
