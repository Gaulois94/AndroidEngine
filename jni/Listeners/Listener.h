#ifndef  LISTENER_INC
#define  LISTENER_INC

class Listener
{
	public:
		virtual ~Listener(){}
		virtual void fire() = 0;
};

#endif
