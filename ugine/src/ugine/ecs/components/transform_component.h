#pragma once

#include "../component.h"

#include "ugine/log.h"

#include <math.h>
#include <glm/glm.hpp>
#include "tweeny/tweeny.h"

namespace Ugine
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent()
			:position_(glm::vec2(0.0f,0.0f)), rotation_(glm::vec2(0.0f, 0.0f)), scale_(glm::vec2(1.0f, 1.0f))
		{}

		~TransformComponent()
		{
			LOG_INFO("Delete Transform");
		}

		void SetPosition( glm::vec2 position) { position_ = position; }
		void SetRotation( glm::vec2 rotation) { rotation_ = rotation; }
		void SetScale( glm::vec2 scale) { scale_ = scale; }

		glm::vec2 GetPosition() { return position_; }
		glm::vec2 GetRotation() { return rotation_; }
		glm::vec2 GetScale() { return scale_; }

		// Inherited via Component
		virtual void Init() override
		{}

		virtual void Update(float Timestep) override
		{}

	private:
		glm::vec2 position_;
		glm::vec2 rotation_;
		glm::vec2 scale_;

	};
}
