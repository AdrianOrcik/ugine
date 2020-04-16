#pragma once
#include "../component.h"
#include "ugine/renderer/primitives.h"
#include "ugine/renderer/renderer_2d.h"
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
			delete rendererStaticData_;
			delete rendererDynamicData_;
		}

		void SetPrimitive(PrimitiveType type) {
			if (type == PrimitiveType::Square)
			{
				rendererStaticData_->primitiveData = &Primitives::GenerateSquare();
			}
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
			//Renderer2D::Init(rendererStaticData_);
		}

		virtual void Update(float Timestep) override
		{
			LOG_INFO("Renderer");
			//Renderer2D::BegineScene(rendererDynamicData_->camera);
			//Ugine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		}
	private:
		RendererStaticData* rendererStaticData_;
		RendererDynamicData* rendererDynamicData_;
	};
}