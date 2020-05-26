#pragma once

class Formulas
{
public:
	static void SetSortSpeed(const float value){sortSpeed_ = value;}
	static float GetRoutineWaitTime ()
	{
		//NOTE: simple proportion - trojclenka
		const float MAX_SORT_WAITING_TIME = 0.5f;
		return (0.1f / sortSpeed_) * MAX_SORT_WAITING_TIME;
	}

	static float sortSpeed_;
};