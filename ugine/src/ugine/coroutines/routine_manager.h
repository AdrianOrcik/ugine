#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "ugine/coroutines/coroutines.h"

namespace Ugine
{
	template<class T>
	class IEnumerator
	{
	public:
		virtual bool HasMore() = 0;
		virtual T next(float Timestep) = 0;
	};

	class RoutineManager
	{
		//todo: implement routine garbage collector
	public:
		static void StartCoroutine(IEnumerator<void>* routine);
		static void Update(float Timestep);
	private:
		static std::vector<IEnumerator<void>*> routines_;
	};
}