#pragma once
#include "../component.h"
#include "ugine/renderer/primitives.h"
#include "ugine/renderer/renderer_2d.h"
#include "ugine/ecs/components/transform_component.h"

namespace Ugine 
{	
	class RendererComponent : public Component
	{
	public:
		RendererComponent( )
		{
		}

		RendererComponent(RendererComponent& renderer)
		{
		}

		~RendererComponent() 
		{
		}

		glm::vec4 GetColor() { return color_; }
		void SetColor(glm::vec4 color)
		{
			color_ = color;
		}

		void SetCamera(const OrthographicCamera* camera)	
		{
			camera_ = camera;
		}

		// Inherited via Component
		virtual void Init() override
		{
			transformComponent_ = (TransformComponent*)owner->GetComponent<TransformComponent>();

			if(Renderer2D::Data == nullptr)
				Renderer2D::Init();
		}

		virtual void Update(float Timestep) override
		{
			Renderer2D::OnBegin(*camera_);
			Ugine::Renderer2D::Draw(transformComponent_->GetLocalPosition(), transformComponent_->GetScale(), color_);
		}

		virtual void OnActive() override
		{}

		virtual void OnDeactive() override
		{}

	private:
		TransformComponent* transformComponent_	= nullptr;
		const OrthographicCamera* camera_;

		//todo: add more data
		glm::vec4 color_;
	};
}