#include "uepch.h"
#include "routine_manager.h"

namespace Ugine
{
	std::vector<IEnumerator<void>*> RoutineManager::routines_;
	void RoutineManager::StartCoroutine(IEnumerator<void>* routine)
	{
		routines_.push_back(routine);
	}

	void RoutineManager::DeleteRoutines()
	{
		//TODO: fix
		for (auto routine : routines_) {
			std::vector<IEnumerator<void>*>::iterator it = std::find(routines_.begin(), routines_.end(), routine);
			std::vector<IEnumerator<void>*>::iterator first = routines_.begin();
			int index = std::distance(first, it);
			routines_.erase(routines_.begin() + index);
		}
	}

	void RoutineManager::Update(float Timestep)
	{
		std::vector<IEnumerator<void>*> obsoleteRoutines;
		for (auto routine : routines_) {
			if (routine->HasMore()) 
			{
				routine->Next(Timestep);
			}
			else
			{
				obsoleteRoutines.push_back(routine);
			}
		}

		if (obsoleteRoutines.size() > 0)
		{
			for (auto routine : obsoleteRoutines) {
				std::vector<IEnumerator<void>*>::iterator it = std::find(routines_.begin(), routines_.end(), routine);
				std::vector<IEnumerator<void>*>::iterator first = routines_.begin();
				int index = std::distance(first, it);
				routines_.erase(routines_.begin() + index);
			}
		}
	}
}