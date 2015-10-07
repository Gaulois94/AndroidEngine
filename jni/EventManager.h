#ifndef DEF_EVENTMANAGER
#define DEF_EVENTMANAGER

/** \brief structure which contain the touch information*/
struct TouchCoord
{
	bool down; /** <Tell if we are currently touching the screen*/
	float startX; /** <Where the touch event has started on X axis*/
	float startY; /** <Where the touch event has started on Y axis*/
	float x; /** <The last x coords*/
	float y; /** <The last y coords*/
};

static TouchCoord touchCoord;

#endif
