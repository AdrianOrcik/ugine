#pragma once

#include "uepch.h"
#include "../core.h"

namespace Ugine
{
	enum class EventType
	{
		NONE = 0,
		WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,
		APP_TICK, APP_UPDATE, APP_RENDER,
		KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
		MOUSE_BUTTON_PRESS, MOUSE_BUTTON_RELEASE, MOUSE_MOVE, MOUSE_SCROLL
	};

	enum EventCategory
	{
		None = 0,
		APPLICATION = BIT(0),
		INPUT = BIT(1),
		KEYBOARD = BIT(2),
		MOUSE = BIT(3),
		MOUSE_BUTTON = BIT(4)
	};

#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class UE_API Event
	{
		friend class EventDispatcher;
	public:

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		// Definition of inline function
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() &category;
		}
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: event_(event)
		{

		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (event_.GetEventType() == T::GetStaticType())
			{
				event_.Handled = func(*(T*)&event_);
				return false;
			}
			return true;
		}

	private:
		Event& event_;

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
