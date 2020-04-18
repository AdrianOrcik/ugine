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

		void SetPosition( glm::vec2 position) { position_ = position; }
		void SetRotation( glm::vec2 rotation) { rotation_ = rotation; }
		void SetScale( glm::vec2 scale) { scale_ = scale; }

		glm::vec2 GetPosition() { return position_; }
		glm::vec2 GetRotation() { return rotation_; }
		glm::vec2 GetScale() { return scale_; }

		//todo: implement tweeny effect

		bool MoveX(tweeny::tween<int> &, int p) 
		{

			SetPosition(glm::vec2(p, GetPosition().y));

			//printf("%+.3d |", p); // 3 digits with sign
			//for (int i = 0; i <= 100; i++) printf("%c", i == p ? '.' : ' '); // prints the line
			//printf("%c\n", p == 100 ? ';' : '|');
			return false;
		}

		// Inherited via Component
		virtual void Init() override
		{
			LOG_INFO("Tweener - Before");
			//auto helloworld = tweeny::from('h', 'e', 'l', 'l', 'o').to('w', 'o', 'r', 'l', 'd').during(50);
			//for (int i = 0; i < 50; i++) {
			//	for (char c : helloworld.step(1)) { printf("%c", c); }
			//	printf("\n");
			//}

			//auto xPositionTween = tweeny::from(0).to(100).during(100).via(tweeny::easing::linear).onStep(MoveX);
			//while (xPositionTween.progress() < 1.0f) {
			//	SetPosition(glm::vec2(xPositionTween, GetPosition().y));
			//	xPositionTween.step(0.01f);
			//}

			LOG_INFO("Tweener - After");
		}

		virtual void Update(float Timestep) override
		{
			//LOG_INFO("[{0}, {1}]", GetPosition().x, GetPosition().y);
		}

	private:
		glm::vec2 position_;
		glm::vec2 rotation_;
		glm::vec2 scale_;

	};
}
