#pragma once

namespace Ugine
{
	class GraphicContext
	{
		// simple opengl render abstraction
		// opengl API need only these two functions for initialization
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}