#ifndef UE_LAYER_STACK
#define UE_LAYER_STACK

#include "core.h"
#include "layer.h"

#include <vector>

namespace Ugine 
{	
	extern "C" class UE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return layers_.begin(); }
		std::vector<Layer*>::iterator end() { return layers_.end(); }

	private:
		std::vector<Layer*> layers_;
		std::vector<Layer*>::iterator layerInsert_;
	};

}

#endif // !UE_LAYER_STACK
