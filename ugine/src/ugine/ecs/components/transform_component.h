#pragma once

#include "../component.h"

#include "ugine/log.h"

#include <math.h>
#include <glm/glm.hpp>
#include "tweeny/tweeny.h"

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
		{}

		~TransformComponent()
		{
			LOG_INFO("Delete Transform");
		}

		void SetLocalPosition( glm::vec2 position) { position_ = position; }
		void SetOffsetPosition(glm::vec2 positionOffset) { positionOffset_ = positionOffset; }
		void SetRotation( glm::vec2 rotation) { rotation_ = rotation; }
		void SetScale( glm::vec2 scale) { scale_ = scale; }

		glm::vec2 GetLocalPosition() { return position_; }
		glm::vec2 GetWorldPosition() { return (position_ + pivotOffset_ + positionOffset_); }
		glm::vec2 GetRotation() { return rotation_; }
		glm::vec2 GetScale() { return scale_; }

		// Inherited via Component
		virtual void Init() override
		{}

		virtual void Update(float Timestep) override
		{
			PivotCalculation();
		}

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
