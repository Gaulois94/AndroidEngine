#include "EventManager.h"

//Initialize the TouchCoord struct.
TouchCoord touchCoord[10];

bool touchInRect(const Rectangle3f& rect, uint32_t i)
{
	return (touchCoord[i].x > rect.x && touchCoord[i].x < rect.x + rect.width &&
			touchCoord[i].y > rect.y && touchCoord[i].y < rect.y + rect.height);
}

bool touchInRect(const Rectangle2f& rect, uint32_t i)
{
	return (touchCoord[i].x > rect.x && touchCoord[i].x < rect.x + rect.width &&
			touchCoord[i].y > rect.y && touchCoord[i].y < rect.y + rect.height);
}
