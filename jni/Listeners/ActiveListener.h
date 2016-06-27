#ifndef  ACTIVELISTENER_INC
#define  ACTIVELISTENER_INC

#include "Listeners/Listener.h"

class Active;

class ActiveListener : public Listener
{
	public:
		ActiveListener();
		ActiveListener(void (*func)(Active*, void*), void* param);

		void setActive(Active* active);
		void fire();
	private:
		void (*m_func)(Active*, void*);
		Active* m_active;
		void* m_param;
};

#endif   /* ----- #ifndef ACTIVELISTENER_INC  ----- */
