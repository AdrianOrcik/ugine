#ifndef UE_LAYER
#define UE_LAYER

#include "core.h"
#include "events/event.h"

namespace Ugine
{

	class UE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return debugName_; }

	private:
		std::string debugName_;

	};

}

#endif // !UE_LAYER
