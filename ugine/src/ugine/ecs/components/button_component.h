#pragma once
#include "../component.h"
#include "ugine/ecs/components/transform_component.h"
#include "ugine/ecs/components/renderer_component.h"
#include "ugine/input/input.h"

namespace Ugine
{
	// vector of actions OnEnter, OnLeave, OnClick
	// Object is automatic bind on renderer

	class ButtonComponent : public Component
	{
	public:
		ButtonComponent()
		{
			//LOG_INFO("ButtonComponent Init");
		}

		~ButtonComponent()
		{
			//LOG_INFO("ButtonComponent Deleted");
		}

		// Inherited via Component
		virtual void Init() override
		{
			transformComponent_ = (TransformComponent*)owner->GetComponent<TransformComponent>();
			rendererComponent_ = (RendererComponent*)owner->GetComponent<RendererComponent>();
		}
		virtual void Update(float Timestep) override
		{
			std::pair<float, float> mousePosition = Input::GetMousePosition();
			//LOG_INFO("RawPosition: [{0}, {1}]", mousePosition.first, mousePosition.second);

			//OnHoverTrigger();
			//OnClickTrigger();
		}

		virtual void OnActive() override
		{
			//NOTE: Test onclick call back implementation
			OnClickCallback.push_back(std::bind(&ButtonComponent::TestOnClickCallback, this));
		}
		virtual void OnDeactive() override
		{}

		void TestOnClickCallback()
		{
			//LOG_INFO("CLICK EVENT! - {0}", owner->GetName());
		}

		void OnClickTrigger()
		{
			if (isHover_ && !isPressed_ 
				&& Input::IsMouseButtonPressed(0))
			{
				isPressed_ = true;
				//rendererComponent_->SetColor(Color::Red());

				//TODO: OnClick Callback
				for (auto& f : OnClickCallback)
				{
					f();
				}
			}

			if (isHover_ && !Input::IsMouseButtonPressed(0)){
				isPressed_ = false;
				//glm::vec4 color = Color::White();
				//color.a = 0.5f;
				//rendererComponent_->SetColor(color);
			}
		}

		void OnHoverTrigger()
		{
			float unit = 360.0f;
			float halfUnit = 180.0f;

			glm::vec2 unitArea = glm::vec2(transformComponent_->GetScale().x * halfUnit, transformComponent_->GetScale().y * halfUnit);
			glm::vec2 totalArea = unitArea + (transformComponent_->GetLocalPosition() * 10.0f);

			//LOG_INFO("Height: {0}",Input::GetWindowHeight());
			//LOG_INFO("Width: {0}", Input::GetWindowWidth());

			//int width = Application::Get().GetWindow().GetWidth();
			//int height = Application::Get().GetWindow().GetHeight();

			std::pair<float, float> mousePosition = Input::GetMousePosition();
		/*	LOG_INFO("RawPosition: [{0}, {1}]", mousePosition.first, mousePosition.second);*/
			//float xPosition = mousePosition.first - (Input::GetWindowWidth() / 2);
			//float yPosition = (mousePosition.second - (Input::GetWindowHeight() / 2)) - (unitArea.y * transformComponent_->GetLocalPosition().y);

			float objectPositionX = transformComponent_->GetLocalPosition().x * unit + (Input::GetWindowWidth() / 2);
			float objectPositionY = transformComponent_->GetLocalPosition().y * unit + (Input::GetWindowHeight() / 2);

			float DistanceX = objectPositionX - mousePosition.first;
			float DistanceY = objectPositionY - mousePosition.second; // -totalArea.y - (totalArea.y * (transformComponent_->GetLocalPosition().y * 10.0f * 4));

			if (abs(DistanceX) <  totalArea.x && abs(DistanceY) < totalArea.y)
			{
				//glm::vec4 color = rendererComponent_->GetColor();
				//color.a = 0.5f;
				//rendererComponent_->SetColor(color);
				isHover_ = true;
			}
			else 
			{
				//rendererComponent_->SetColor(Color::White());
				isHover_ = false;
			}

			//LOG_INFO("Size [{0}, {1}]", width, height);
			//LOG_INFO("Distance: [{0}, {1}]", DistanceX, DistanceY);
	
			//LOG_INFO("Position: [{0}, {1}]", xPosition, yPosition);
			//LOG_INFO("{0} - WindowPositon: [{1}, {2}]",owner->GetName(), objectPositionX, objectPositionY);

			//int height = Application::s
			//int height = (int)WindowsWindow::GetHeight();
			//int width = (int)WindowsWindow::GetWidth();
			//LOG_INFO("[{0}, {1}]", width, height);
			//LOG_INFO("DistanceX: {0}", DistanceX);
			//LOG_INFO("Normal: {0},{1}", mousePosition.first, mousePosition.second);
			//LOG_INFO("{0},{1}", xPosition, yPosition);

		}

		std::vector<std::function<void()>> OnEnterCallback;
		std::vector<std::function<void()>> OnLeaveCallback;
		std::vector<std::function<void()>> OnClickCallback;

	private:
		TransformComponent* transformComponent_ = nullptr;
		RendererComponent* rendererComponent_ = nullptr;
		bool isHover_ = false;
		bool isPressed_ = false;
	};
}