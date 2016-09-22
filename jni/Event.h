#ifndef  EVENT_INC
#define  EVENT_INC

enum EventType
{
	KEYDOWN,
	KEYUP,
	TOUCH_MOVE,
	TOUCH_DOWN,
	TOUCH_UP
};

struct TouchEvent
{
	uint32_t pid;
	float x;
	float y;
};

struct KeyEvent
{
	uint32_t keyCode;
};

struct Event
{
	union
	{
		KeyEvent   keyEvent;
		TouchEvent touchEvent;
	};

	EventType type;
};

#endif
