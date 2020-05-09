#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"
#include "../scripts/sorting_element.h"

#include "ugine/ecs/components/transform_component.h"
#include "ugine/ecs/components/renderer_component.h"

#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/swap_routine.h"
#include "ugine/coroutines/routines/wait_seconds.h"

#include <functional>
#include <map>

struct SortingElementData
{
	Ugine::Entity* ElementA;
	Ugine::Entity* ElementB;
	bool IsSwaped;

	SortingElementData(Ugine::Entity* elementA,Ugine::Entity* elementB, bool isSwaped)
		:ElementA(elementA), ElementB(elementB), IsSwaped(isSwaped)
	{}

	Ugine::TransformComponent* GetTransformA() { return (Ugine::TransformComponent*)ElementA->GetComponent<Ugine::TransformComponent>(); }
	Ugine::TransformComponent* GetTransformB() { return (Ugine::TransformComponent*)ElementB->GetComponent<Ugine::TransformComponent>(); }

	Ugine::RendererComponent* GetRenderA() { return (Ugine::RendererComponent*)ElementA->GetComponent<Ugine::RendererComponent>(); }
	Ugine::RendererComponent* GetRenderB() { return (Ugine::RendererComponent*)ElementB->GetComponent<Ugine::RendererComponent>(); }

	SortingElement* GetSortingElementA() { return (SortingElement*)ElementA->GetComponent<SortingElement>(); }
	SortingElement* GetSortingElementB() { return (SortingElement*)ElementB->GetComponent<SortingElement>(); }
};

class SwapRoutine;
class SortingManager : public Ugine::ScriptComponent
{

public:
	SortingManager()
	{}

	~SortingManager()
	{
		LOG_INFO("Delete SortingManager - ScriptComponent");
	}

	std::vector<SortingElement*> Elements;
	std::vector<SortingElementData*> BubbleElements;

	void BubbleSort()
	{
		BubbleElements.clear();

		for (int i = 0; i < Elements.size(); i++)
		{
			Ugine::TransformComponent* transform =
				(Ugine::TransformComponent*)Elements[i]->GetEntity()->GetComponent<Ugine::TransformComponent>();
			transform->SetLocalPosition({ (float)i / 10.0f, 0.0f });

			Elements[i]->CurrentPosition = i;
		}

		for (int i = 0; i < Elements.size() - 1; i++)
		{
			for (int j = 0; j < Elements.size() - i - 1; j++)
			{
				if (Elements[j]->Value > Elements[j + 1]->Value)
				{
					Swap(Elements[j], Elements[j+1], true);
				}
				else {
					Swap(Elements[j], Elements[j+1], false);
				}
			}
		}

		for (int i = 0; i < Elements.size(); i++)
		{
			Elements[i]->SortedPosition = i;
		}
	}

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{}

	virtual void OnUpdate(float Timestep) override
	{}

	void StepMove();

private:
	int index_ = 0;

private:
	void SelectElements();
	void SwapElements();
	void UnselectElements();

	void SwapRoutineCompleted();

	bool HasElements() { return index_ < BubbleElements.size(); }

	void Swap(SortingElement * elementA, SortingElement * elementB, bool isSwaped)
	{
		BubbleElements.push_back(new SortingElementData(elementA->GetEntity(),elementB->GetEntity(), isSwaped));

		if(isSwaped){
			SortingElement temp = *elementA;
			*elementA = *elementB;
			*elementB = temp;
		}
	}
};