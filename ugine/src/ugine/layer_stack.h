#pragma once

#include "core.h"
#include "layer.h"

#include <vector>

namespace Ugine 
{	
	class UE_API LayerStack
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
		unsigned int layerIndex_ = 0;
	};

}

