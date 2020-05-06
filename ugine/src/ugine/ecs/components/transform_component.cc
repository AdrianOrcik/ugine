#include "uepch.h"
#include "transform_component.h"

namespace Ugine
{
	void TransformComponent::SetMovement(glm::vec2 value, float t)
	{
		move = new Movement(this, value, t);
		RoutineManager::StartCoroutine((IEnumerator<void>*)move);
	}
}