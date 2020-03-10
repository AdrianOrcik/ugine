#ifndef EVENTS_KEY_EVENT
#define EVENTS_KEY_EVENT

#include "event.h"

#include <sstream>

namespace Ugine 
{
	
	class UE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return keyCode_; }
		EVENT_CLASS_CATEGORY(KEYBOARD | INPUT);

	protected:
		KeyEvent(int keyCode)
			:keyCode_(keyCode) {}

		int keyCode_;
	};

	class UE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			:KeyEvent(keyCode), repeatCount_(repeatCount) {}

		inline int GetRepeatCount() const { return repeatCount_; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keyCode_ << " (" << repeatCount_ << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_PRESSED);

	private:
		int repeatCount_;
	};

	class UE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			:KeyEvent(keyCode) {}
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keyCode_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_RELEASED);

	};
}

#endif // !UE_EVENTS_KEY_EVENT
