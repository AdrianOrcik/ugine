#pragma once

#include "sorting_algo.h"

#include <algorithm>

#include "ugine/coroutines/routine_manager.h"
#include "../routines/swap_routine.h"
#include "ugine/coroutines/routines/wait_seconds.h"

struct Step {
	Step(int num1) : num_1(num1) {}
	Step(int num1, int num2) : num_1(num1), num_2(num2) {}
	int num_1;
	int num_2;
};

class SimulationStep;
class InsertionSort : public SortingAlgo
{
public:
	InsertionSort();
	~InsertionSort();

	// Inherited via SortingAlgo
	virtual void Sort() override;

	std::vector<SortingElement*> BaseElements;

private:
	void SelectElements();
	void SwapElements();

	void Run();

	//void Select(int num);
	//void Insert(int num1, int num2);

	//nonsorted base array
	//std::vector<SortingElement*> BaseElements;

	std::vector<SimulationStep> steps;

};

//TODO: refactor new way of simulation
enum SimulationStepType{Pivot, Select, Insert};

struct StepData
{
	int pos1;
	int pos2;

	StepData(int a, int b = -1)
		:pos1(a), pos2(b)
	{

	} 
};

class SimulationStep
{
public:
	SimulationStep(InsertionSort* insert, StepData structData, SimulationStepType type)
		:sort(insert), data(structData), stepType(type)
	{
	}

	~SimulationStep() = default;

	void Execute()
	{

		if (stepType == SimulationStepType::Select)
		{
			Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.5f);
			Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
			std::cout << "Select " << data.pos1 << std::endl;
			sort->BaseElements[data.pos1]->GetRenderer()->SetColor(Ugine::Color::Red());
			waitfor->SetOnCompleted(std::bind(&SimulationStep::Complet, this));
		}
		else if (stepType == SimulationStepType::Pivot)
		{
			Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.5f);
			Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
			std::cout << "Pivot " << data.pos1 << std::endl;
			sort->BaseElements[data.pos1]->GetRenderer()->SetColor(Ugine::Color::Blue());
			waitfor->SetOnCompleted(std::bind(&SimulationStep::Complet, this));
		}
		else 
		{
			
			Ugine::SwapRoutine* swapRoutine = DBG_NEW Ugine::SwapRoutine(sort->BaseElements[data.pos1]->GetTransform(), sort->BaseElements[data.pos2]->GetTransform(), 5.0f);
			swapRoutine->SetOnCompleted(std::bind(&SimulationStep::Complet, this));
			Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
			std::cout << "Insert from " << data.pos1 << " to " << data.pos2 << std::endl;
			//TODO: implement new routine for insertion
		}
	}

	void Complet()
	{
		OnCompleted();
	}

	std::function<void()> OnCompleted;

private:
	SimulationStepType stepType;
	StepData data;
	InsertionSort* sort;
};