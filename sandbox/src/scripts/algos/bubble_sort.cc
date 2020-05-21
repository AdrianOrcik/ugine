#include "bubble_sort.h"

BubbleSort::BubbleSort()
{}

BubbleSort::~BubbleSort()
{}

void BubbleSort::Sort()
{
	OnSimulationStart();


	index_ = 0;
	arrayIndex = 0;

	//SwapPairClear();
	SetElementCurrentPosition();
	AddStepArray(Elements);
	for (int i = 0; i < Elements.size() - 1; i++)
	{
		for (int j = 0; j < Elements.size() - i - 1; j++)
		{
			//current > current + 1
			if (Elements[j]->Value > Elements[j + 1]->Value)
			{
				//Swap automatically split data into 3 steps? NO! because I need consistent step cycle
				AddStep(StepData(j, j + 1), BubbleStepType::BeforeSwap);
				AddStep(StepData(j, j + 1), BubbleStepType::Swap);
				AddStep(StepData(), BubbleStepType::AfterSwap);

				//Swap(Elements[j], Elements[j + 1], true);
				SortingElement* tmp = Elements[j];
				Elements[j] = Elements[j + 1];
				Elements[j + 1] = tmp;				
				AddStepArray(Elements);
			}
			else 
			{
				AddStep(StepData(j, j + 1), BubbleStepType::Select);
				//Swap(Elements[j], Elements[j + 1], false);
			}
		}
	}

	//SetElementSortedPosition();
	
	//SelectElements();

	Run();
}

void BubbleSort::Run()
{
	if (index_ >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::Yellow());
		OnSimulationDone();
		LOG_ERROR("Done!");
		return;
	}

	simulationSteps_[index_].OnCompletedCallback = std::bind(&BubbleSort::Run, this);
	simulationSteps_[index_].Execute();
	index_++;
}

void BubbleSort::AddStep(StepData data, BubbleStepType stepType)
{
	simulationSteps_.push_back(BubbleStep(this, data, stepType));
}

//void BubbleSort::SelectElements()
//{
//	if (!HasMorePair())
//	{
//		LOG_ERROR("Select - No More Steps!");
//
//		SetElementsColor(Ugine::Color::Yellow());
//		//todo: reset values on beginning
//		PairIndex = 0;
//		OnSimulationDone();
//		return;
//	}
//
//	SortingPairElement* data = SwapPair[PairIndex];
//
//	data->GetRenderA()->SetColor(Ugine::Color::Blue());
//	data->GetRenderB()->SetColor(Ugine::Color::Blue());
//
//	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);
//	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
//
//	if (data->IsSwaped)
//		waitfor->SetOnCompleted(std::bind(&BubbleSort::SwapElements, this));
//	else
//		waitfor->SetOnCompleted(std::bind(&BubbleSort::UnselectElements, this));
//}
//
//void BubbleSort::SwapElements()
//{
//	SortingPairElement* data = SwapPair[PairIndex];
//
//	data->GetRenderA()->SetColor(Ugine::Color::Red());
//	data->GetRenderB()->SetColor(Ugine::Color::Red());
//
//	//todo: implement some logic operation into sorting elements data
//	int currentA = data->GetSortingElementA()->CurrentPosition;
//	int currentB = data->GetSortingElementB()->CurrentPosition;
//		
//	data->GetSortingElementA()->CurrentPosition = currentB;
//	data->GetSortingElementB()->CurrentPosition = currentA;
//
//	Ugine::SwapRoutine* swapRoutine = DBG_NEW Ugine::SwapRoutine(data->GetTransformA(), data->GetTransformB(), 10.0f);
//	std::function<void(void)> function = std::bind(&BubbleSort::UnselectElements, this);
//	swapRoutine->SetOnCompleted(function);
//
//	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
//}
//
//void BubbleSort::UnselectElements()
//{
//	SortingPairElement* data = SwapPair[PairIndex];
//	data->GetRenderA()->SetColor(Ugine::Color::White());
//	data->GetRenderB()->SetColor(Ugine::Color::White());
//
//	PairIndex++;
//	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);
//	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
//	waitfor->SetOnCompleted(std::bind(&BubbleSort::SelectElements, this));
//}
