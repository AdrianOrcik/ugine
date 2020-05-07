#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"
#include "../scripts/sorting_element.h"

#include <functional>
#include <map>

struct SortingElementData
{
	Ugine::TransformComponent* ElementA;
	Ugine::TransformComponent* ElementB;

	SortingElementData(Ugine::TransformComponent* elementA, Ugine::TransformComponent* elementB)
		:ElementA(elementA), ElementB(elementB)
	{}
};

//class Sandbox2D;
class SortingManager : public Ugine::ScriptComponent
{

public:
	SortingManager()
	{}

	~SortingManager()
	{
		LOG_INFO("Delete SortingManager - ScriptComponent");
	}

	std::vector<SortingElement*> Elemets;
	std::vector<SortingElementData*> BubbleElements;

	void BubbleSort()
	{
		BubbleElements.clear();

		for (int i = 0; i < Elemets.size(); i++)
		{
			Ugine::TransformComponent* transform =
				(Ugine::TransformComponent*)Elemets[i]->GetEntity()->GetComponent<Ugine::TransformComponent>();
			transform->SetLocalPosition({ (float)i / 10,0.0f });
		}

		for (int i = 0; i < Elemets.size() - 1; i++)
		{
			for (int j = 0; j < Elemets.size() - i - 1; j++)
			{
				if (Elemets[j]->Value > Elemets[j + 1]->Value)
				{
					Swap(Elemets[j], Elemets[j + 1]);
				}
			}
		}
	}

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{}

	virtual void OnUpdate(float Timestep) override
	{}

	int index = 0;
	void StepMove()
	{
		if (index < BubbleElements.size()) {
			SortingElementData* data = BubbleElements[index];
			data->ElementA->SetMovement(data->ElementB->GetWorldPosition(), 1.0f);
			data->ElementB->SetMovement(data->ElementA->GetWorldPosition(), 1.0f);
			index++;
		}
		else {
			LOG_ERROR("No More Steps!");
			index = 0;
		}
	}



private:
	void Swap(SortingElement * elementA, SortingElement * elementB)
	{
		//BubbleElements.insert(std::make_pair(
		//	(Ugine::TransformComponent*)elementA->GetEntity()->GetComponent<Ugine::TransformComponent>(),
		//	(Ugine::TransformComponent*)elementA->GetEntity()->GetComponent<Ugine::TransformComponent>()));

		BubbleElements.push_back(new SortingElementData((Ugine::TransformComponent*)elementA->GetEntity()->GetComponent<Ugine::TransformComponent>(), (Ugine::TransformComponent*)elementB->GetEntity()->GetComponent<Ugine::TransformComponent>()));

		SortingElement temp = *elementA;
		*elementA = *elementB;
		*elementB = temp;
	}
};