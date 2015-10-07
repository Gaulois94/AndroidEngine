#ifndef DEF_EVENTMANAGER
#define DEF_EVENTMANAGER

/** \brief structure which contain the touch information*/
struct TouchCoord
{
	static bool down; /** <Tell if we are currently touching the screen*/
	static float startX; /** <Where the touch event has started on X axis*/
	static float startY; /** <Where the touch event has started on Y axis*/
	static float x; /** <The last x coords*/
	static float y; /** <The last y coords*/
};

#endif
