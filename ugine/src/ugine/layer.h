#pragma once

#include "core.h"
#include "events/event.h"
#include "ugine/core/timestep.h"

namespace Ugine
{

	class UE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return debugName_; }

	private:
		std::string debugName_;

	};
}

