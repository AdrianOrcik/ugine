#include "uepch.h"
#include "ortho_camera_controller.h"

#include "ugine/input/input.h"
#include "ugine/input/key_codes.h"

namespace Ugine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool movement, bool zoom, bool rotation)
		: aspectRatio_(aspectRatio), camera_(-aspectRatio_ * zoomLevel_, aspectRatio_ * zoomLevel_, -zoomLevel_, zoomLevel_),
		isMovementEnabled_(movement), isZoomEnabled_(zoom), isRotationEnabled_(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if(isMovementEnabled_)
		{
			if (Input::IsKeyPressed(INPUT_KEY_A))
				cameraPosition_.x -= cameraTranslationSpeed_ * ts;
			else if (Input::IsKeyPressed(INPUT_KEY_D))
				cameraPosition_.x += cameraTranslationSpeed_ * ts;

			if (Input::IsKeyPressed(INPUT_KEY_W))
				cameraPosition_.y += cameraTranslationSpeed_ * ts;
			else if (Input::IsKeyPressed(INPUT_KEY_S))
				cameraPosition_.y -= cameraTranslationSpeed_ * ts;
		}

		if(isRotationEnabled_) 
		{
			if (Input::IsKeyPressed(INPUT_KEY_Q))
				cameraRotation_ += cameraRotationSpeed_ * ts;
			if (Input::IsKeyPressed(INPUT_KEY_E))
				cameraRotation_ -= cameraRotationSpeed_ * ts;

			camera_.SetRotation(cameraRotation_);
		}

		camera_.SetPosition(cameraPosition_);
		cameraTranslationSpeed_ = zoomLevel_;
	}

	void OrthographicCameraController::OnEvent(Event & e)
	{
		EventDispatcher dispather(e);
		dispather.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispather.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::SetZoomLevel(float level) 
	{
		zoomLevel_ = level;
		camera_.SetProjection(-aspectRatio_ * zoomLevel_, aspectRatio_ * zoomLevel_, -zoomLevel_, zoomLevel_);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent & e)
	{
		if (!isZoomEnabled_)return false;
		zoomLevel_ -= e.GetYOffset() * 0.25f;
		zoomLevel_ = std::max(zoomLevel_, 0.25f);
		camera_.SetProjection(-aspectRatio_ * zoomLevel_, aspectRatio_ * zoomLevel_, -zoomLevel_, zoomLevel_);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent & e)
	{
		aspectRatio_ = (float)e.GetWidth() / (float)e.GetHeight();
		camera_.SetProjection(-aspectRatio_ * zoomLevel_, aspectRatio_ * zoomLevel_, -zoomLevel_, zoomLevel_);
		return false;
	}
}