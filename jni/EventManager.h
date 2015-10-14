#ifndef DEF_EVENTMANAGER
#define DEF_EVENTMANAGER

#include "Graphics/Rectangle3.h"
#include "Graphics/Rectangle2.h"

enum TouchEventType
{
	UP,
	DOWN,
	MOVE
};

/** \brief structure which contain the touch information*/
struct TouchCoord
{
	TouchEventType type; /** <The type of the touching*/
	float startX; /** <Where the touch event has started on X axis*/
	float startY; /** <Where the touch event has started on Y axis*/
	float x; /** <The last x coords*/
	float y; /** <The last y coords*/
};

extern TouchCoord touchCoord;

bool touchInRect(const Rectangle3f& rect);
bool touchInRect(const Rectangle2f& rect);

#endif
