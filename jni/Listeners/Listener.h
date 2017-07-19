#ifndef  LISTENER_INC
#define  LISTENER_INC

class Active;
class Drawable;
class Updatable;

template <typename T>
class Listener
{
	public:
		Listener(void (*func)(T*, void*), void* param)
		{
			m_func  = func;
			m_param = param;
		}
		Listener(){}
		virtual ~Listener(){}
		void fire() {if(m_func) m_func(m_obj, m_param);}
		void fire(T* obj) {if(m_func) m_func(obj, m_param);}
		void setThis(T* obj) {m_obj = obj;}
	private:
		void (*m_func)(T*, void*)=NULL;
		T* m_obj;
		void* m_param=NULL;	
};

typedef Listener<Active>    ActiveListener;
typedef Listener<Drawable>  DrawableListener;
typedef Listener<Updatable> UpdatableListener;

#endif
