#pragma once
#include <glm/glm.hpp>

#include "ugine/log.h"
#include "ugine/ecs/components/transform_component.h"
#include "ugine/coroutines/routine_manager.h"
#include "../sorting_element.h"
#include <functional>

class TransformComponent;
class InsertRoutine : public Ugine::IEnumerator<void>
{
public:
	InsertRoutine(int originPosition, int insertPosition, std::vector<SortingElement*> Elements, float time);
	~InsertRoutine();

	void SetOnCompleted(std::function<void()>f) { onCompleted = f; }

	// Inherited via IEnumerator
	virtual bool HasMore() override;
	virtual void Next(float Timestep) override;
	virtual void OnCompleted() override;

private:
	float GetInterpolation2(float a, float b, float t);

private:
	glm::vec2 origin;
	glm::vec2 insert;
	std::vector<std::pair<float, float>> positions;

	float time_ = 0;
	float frameTime_ = 0;
	float currentTime_ = 0;

	int originPosition_ = 0;
	int insertPosition_ = 0;
	std::vector<SortingElement*> elements_;

	std::function<void()> onCompleted = NULL;
};