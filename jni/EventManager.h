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
	TouchEventType type=UP; /** <The type of the touching*/
	float startX=0.0f; /** <Where the touch event has started on X axis*/
	float startY=0.0f; /** <Where the touch event has started on Y axis*/
	float x=0.0f; /** <The last x coords*/
	float y=0.0f; /** <The last y coords*/
};

extern TouchCoord touchCoord[10];

bool touchInRect(const Rectangle3f& rect, uint32_t indice);
bool touchInRect(const Rectangle2f& rect, uint32_t indice);

#endif
