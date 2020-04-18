#include "uepch.h"
#include "layer_stack.h"

namespace Ugine
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers_)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers_.emplace(layers_.begin() + layerIndex_, layer);
		layerIndex_++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers_.push_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layers_.begin(), layers_.end(), layer);
		if (it != layers_.end())
		{
			layers_.erase(it);
			layerIndex_--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(layers_.begin(), layers_.end(), overlay);
		if (it != layers_.end())
			layers_.erase(it);
	}
}