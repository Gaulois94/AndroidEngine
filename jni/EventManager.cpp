#include "EventManager.h"

//Initialize the TouchCoord struct.
TouchCoord touchCoord = {.type=UP, .startX=0, .startY=0, .x=0, .y=0};

bool touchInRect(const Rectangle3f& rect)
{
	return (touchCoord.x > rect.x && touchCoord.x < rect.x + rect.width &&
			touchCoord.y > rect.y && touchCoord.y < rect.y + rect.height);
}

bool touchInRect(const Rectangle2f& rect)
{
	return (touchCoord.x > rect.x && touchCoord.x < rect.x + rect.width &&
			touchCoord.y > rect.y && touchCoord.y < rect.y + rect.height);
}
