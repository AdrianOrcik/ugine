#pragma once

//TODO: make formulas to calculate waiting time based on speed from GUI
class Formulas
{
public:
	Formulas()
	{
		//sortSpeed_ = 0;
	}

	//static void SetSortSpeed(float value){sortSpeed_ = value;}
	static float GetRoutineWaitTime ()
	{
		//const float MIN_SORT_WAITING_TIME = 0.001f;
		//return (1.0f / (0.1f / 10.0f)) * MIN_SORT_WAITING_TIME;
		return 0.2f;
	}

	//static float sortSpeed_;
};