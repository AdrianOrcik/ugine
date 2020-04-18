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
			rendererStaticData_ = new RendererStaticData();
			rendererDynamicData_ = new RendererDynamicData();

			SetPrimitive(PrimitiveType::Square);
			SetShader("assets/shaders/Texture.glsl");
			SetTexture("");
		}

		~RendererComponent() {
			delete rendererStaticData_->primitiveData;
			delete rendererStaticData_;
			delete rendererDynamicData_;
		}

		void SetPrimitive(PrimitiveType type) 
		{
			rendererStaticData_->primitiveData = Primitives::Generate(type);
		}

		void SetShader(const std::string path)				
		{
			rendererStaticData_->shaderPath = path;
		}

		void SetTexture(const std::string path)				
		{ 
			rendererStaticData_->texturePath = path;
		}

		void SetColor(glm::vec4 color)						
		{ 
			rendererDynamicData_->color = color;
		}

		void SetCamera(const OrthographicCamera* camera)	
		{
			rendererDynamicData_->camera = camera; 
		}

		// Inherited via Component
		virtual void Init() override
		{
			transformComponent_ = (TransformComponent*)owner->GetComponent<TransformComponent>();
			Renderer2D::Init(rendererStaticData_);
		}

		virtual void Update(float Timestep) override
		{
			//LOG_INFO("Renderer");
			Renderer2D::OnBegin(*rendererDynamicData_->camera);
			Ugine::Renderer2D::Draw(transformComponent_->GetPosition(), transformComponent_->GetScale(), rendererDynamicData_->color);
		}
	private:
		RendererStaticData* rendererStaticData_;
		RendererDynamicData* rendererDynamicData_;
		TransformComponent* transformComponent_;

	};
}