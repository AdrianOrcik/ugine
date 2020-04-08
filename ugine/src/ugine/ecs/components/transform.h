#pragma once

#include "../component.h"

#include "ugine/log.h"

#include <math.h>

namespace Ugine
{
	class Transform : public Ugine::Component
	{
	public:
		Transform(int x, int y)
			:x_(x), y_(y)
		{}

		void SetX(int x) { x_ = x; }
		void SetY(int y) { y_ = y; }

		inline int GetX() { return x_; }
		inline int GetY() { return y_; }

		inline double GetLength() const { return sqrt(pow(x_, 2) + pow(y_, 2)); }

		// Inherited via Component
		virtual void Init() override
		{

		}
		virtual void Update(float Timestep) override
		{
			LOG_INFO("[{0}, {1}]", GetX(), GetY());
		}

	private:
		int x_;
		int y_;
	};
}
