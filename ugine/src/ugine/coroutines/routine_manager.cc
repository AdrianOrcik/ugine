#include "uepch.h"
#include "routine_manager.h"

namespace Ugine
{
	std::vector<IEnumerator<void>*> RoutineManager::routines_;
	void RoutineManager::StartCoroutine(IEnumerator<void>* routine)
	{
		routines_.push_back(routine);
	}

	void RoutineManager::Update(float Timestep)
	{
		for (auto routine : routines_) {
			if(routine->HasMore()){
				routine->next(Timestep);
			}
		}
	}
}