#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"
#include "../scripts/sorting_element.h"

class Sandbox2D;
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

	void BubbleSort()
	{
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

		RefreshTransform();
	}

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{
		//LOG_INFO("INIT");
	}

	virtual void OnUpdate(float Timestep) override
	{
		//LOG_INFO("update");
	}

private:
	void RefreshTransform()
	{
		for (int i = 0; i < Elemets.size(); i++)
		{
			Ugine::TransformComponent* transform =
				(Ugine::TransformComponent*)Elemets[i]->GetEntity()->GetComponent<Ugine::TransformComponent>();
			transform->SetLocalPosition({ (float)i / 10,0.0f });
		}
	}

	void Swap(SortingElement * elementA, SortingElement * elementB)
	{
		SortingElement temp = *elementA;
		*elementA = *elementB;
		*elementB = temp;
	}
};