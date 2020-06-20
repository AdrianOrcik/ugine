#pragma once
#include "ugine.h"

#include <glm/glm.hpp>

#include "ugine/log.h"
#include "../node_element.h"
#include "ugine/coroutines/routine_manager.h"

#include <functional>

namespace Ugine
{
	class FadeToColorRoutine : public IEnumerator<void>
	{
	public:
		FadeToColorRoutine(NodeElement* node, float time, glm::vec4 fadeTo, glm::vec4 fadeFrom = glm::vec4(-1));
		~FadeToColorRoutine();

		void SetOnCompleted(std::function<void()>f) { onCompleted = f; }

		// Inherited via IEnumerator
		virtual bool HasMore() override;
		virtual void Next(float Timestep) override;
		virtual void OnCompleted() override;

	private:
		float GetInterpolation2(float a, float b, float t);

	private:

		float time_ = 0;
		float frameTime_ = 0;
		float currentTime_ = 0;

		glm::vec4 colorFadeTo_ = { 0.0f,0.0f,0.0f,0.0f };
		glm::vec4 colorFadefrom_ = { 0.0f,0.0f,0.0f,0.0f };
		NodeElement* node_ = nullptr;
		Ugine::RendererComponent* renderer_ = nullptr;
		std::function<void()> onCompleted = NULL;
	};
}