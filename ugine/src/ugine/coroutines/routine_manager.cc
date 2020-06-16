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
		routines_.erase(routines_.begin(), routines_.end());
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
			obsoleteRoutines.erase(obsoleteRoutines.begin(), obsoleteRoutines.end());
		}
	}
}