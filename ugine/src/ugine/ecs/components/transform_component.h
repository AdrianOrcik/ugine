#pragma once

#include "../component.h"

#include "ugine/log.h"

#include <math.h>
#include <glm/glm.hpp>
//#include "tweeny/tweeny.h"

#include "ugine/coroutines/coroutines.h"
#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/movement.h"

#include <future>
#include <thread>

namespace Ugine
{
	enum TransformPivot
	{
		Top,
		Middle,
		Bottom
	};

	class TransformComponent : public Component
	{
	public:
		TransformComponent()
			:position_(glm::vec2(0.0f,0.0f)), rotation_(glm::vec2(0.0f, 0.0f)), scale_(glm::vec2(1.0f, 1.0f)), pivot_(TransformPivot::Bottom)
		{
			//currentTime = 99;
		}

		~TransformComponent()
		{
			LOG_INFO("Delete Transform");
		}

		void SetLocalX(float x) { position_.x = x; }
		void SetLocalY(float y) { position_.y = y; }
		void SetLocalPosition( glm::vec2 position) { position_ = position; }
		void SetOffsetPosition(glm::vec2 positionOffset) { positionOffset_ = positionOffset; }
		void SetRotation( glm::vec2 rotation) { rotation_ = rotation; }
		void SetScale( glm::vec2 scale) { scale_ = scale; }

		glm::vec2 GetLocalPosition() { return position_; }
		glm::vec2 GetWorldPosition() { return (position_ + pivotOffset_ + positionOffset_); }
		glm::vec2 GetRotation() { return rotation_; }
		glm::vec2 GetScale() { return scale_; }
		//Coro c;
		//ccrContext z = 0;
		
		// Inherited via Component
		virtual void Init() override
		{
			//r.add(myfunctor());
			//RoutineManager::StartCoroutine(macro_routine);
		}

		virtual void Update(float Timestep) override
		{
			//c.macro_routine(&z);

			//LOG_INFO(GetWorldPosition().x);
			PivotCalculation();
			//Movement(Timestep);
		}

		void SetMovement(glm::vec2 value, float t)
		{
			Movement* move = new Movement(value, t);
			RoutineManager::StartCoroutine((IEnumerator<void>*)move);
		}

		//void macro_routine(ccrContParam)
		//{
		//	ccrBeginContext;
		//	int i;
		//	ccrEndContext(foo);

		//	ccrBegin(foo);
		//	for (foo->i = 0; foo->i < 5; foo->i++) {
		//		LOG_INFO("Routine: {0}", foo->i);
		//		ccrReturnV;
		//	}
		//	ccrFinishV;
		//}



		// -- comment
		//void Movement(float Timestep)
		//{

		//	if(currentTime < 1.0f){
		//		glm::vec2 tmp;
		//		position_.x = GetInterpolation2((float)startPos.x, (float)finalPos.x, (float)currentTime);
		//		//tmp.y = GetInterpolation2((float)startPos.y, (float)finalPos.y, (float)currentTime);
		//		currentTime += Timestep * t_ * 5.0f;
		//	}

		//	if (currentTime >= 1.0f)
		//	{
		//		MovementStatus = 0;
		//	}
		//}

		//std::function<void()> OnMoveCompleted;

		//glm::vec2 finalPos;
		//glm::vec2 startPos;
		//float t_;
		//float currentTime;
		//int MovementStatus = 0; // 0 - ready , 1 - inProgress
		//void SetMovement(glm::vec2 value, float t)
		//{
		//	startPos = GetWorldPosition();
		//	finalPos = value;
		//	t_ = t;
		//	currentTime = 0;
		//	MovementStatus = 1;
		//}

		// -- comment

	private:
		void PivotCalculation()
		{
			glm::vec2 offset = glm::vec2(0,0);
			offset.y = GetScale().y / 2.0f;

			switch (pivot_)
			{
				case TransformPivot::Bottom:
					pivotOffset_ = glm::vec2(0.0f, offset.y);
					return;
				case TransformPivot::Top:
					pivotOffset_ = glm::vec2(0.0f, -offset.y);
					return;			
			}
		}

	private:
		glm::vec2 position_;
		glm::vec2 rotation_;
		glm::vec2 scale_;

		TransformPivot pivot_;
		glm::vec2 pivotOffset_;
		glm::vec2 positionOffset_;
	};

}
