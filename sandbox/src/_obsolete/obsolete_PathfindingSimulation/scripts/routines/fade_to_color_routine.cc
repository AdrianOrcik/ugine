#include "fade_to_color_routine.h"

Ugine::FadeToColorRoutine::FadeToColorRoutine(NodeElement * node, float time, glm::vec4 fadeTo, glm::vec4 fadeFrom)
	:node_(node), time_(time), colorFadeTo_(fadeTo), colorFadefrom_(fadeFrom)
{
	renderer_ = ECS_GET_COMPONENT(node_->owner, Ugine::RendererComponent)
	if (colorFadefrom_ == glm::vec4(-1))
	{
		colorFadefrom_ = renderer_->GetColor();
	}
}

Ugine::FadeToColorRoutine::~FadeToColorRoutine()
{
}

bool Ugine::FadeToColorRoutine::HasMore()
{
	bool hasTime = currentTime_ < 0.1f;
	if (!hasTime)
		OnCompleted();

	bool exitTime = currentTime_ < 1.0f;
	if (!exitTime)
		delete this;

	return exitTime;
}

void Ugine::FadeToColorRoutine::Next(float Timestep)
{
	frameTime_ += Timestep;
	//NOTE: calculation of duration into range 0 - 1 for interpolation 
	currentTime_ = (frameTime_ / time_);
	float clampValue = currentTime_ > 1.0f ? 1.0f : currentTime_;

	float r = GetInterpolation2(colorFadefrom_.r, colorFadeTo_.r, clampValue);
	float g = GetInterpolation2(colorFadefrom_.g, colorFadeTo_.g, clampValue);
	float b = GetInterpolation2(colorFadefrom_.b, colorFadeTo_.b, clampValue);

	renderer_->SetColor(glm::vec4(r, g, b, 1.0f));
}

void Ugine::FadeToColorRoutine::OnCompleted()
{
	if(onCompleted != NULL)onCompleted();
	onCompleted = NULL;
}

float Ugine::FadeToColorRoutine::GetInterpolation2(float a, float b, float t)
{
	return a + (b - a) * t;
}
