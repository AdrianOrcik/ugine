#pragma once

#include "ugine/renderer/orthographic_camera.h"
#include "ugine/core/timestep.h"

#include "ugine/events/application_event.h"
#include "ugine/events/mouse_event.h"

namespace Ugine {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return camera_; }
		const OrthographicCamera& GetCamera() const { return camera_; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float aspectRatio_;
		float zoomLevel_ = 1.0f;
		OrthographicCamera camera_;

		bool isRotationEnabled_;

		glm::vec3 cameraPosition_ = { 0.0f, 0.0f, 0.0f };
		float cameraRotation_ = 0.0f;
		float cameraTranslationSpeed_ = 5.0f;
		float cameraRotationSpeed_ = 180.0f;
	};

}