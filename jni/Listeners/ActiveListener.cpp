#include "Widgets/Active.h"

ActiveListener::ActiveListener() : m_func(NULL), m_active(NULL), m_param(NULL)
{}

ActiveListener::ActiveListener(void (*func)(Active*, void*), void* param) : m_func(func), m_active(NULL), m_param(param)
{}

void ActiveListener::setActive(Active* a)
{
	m_active = a;
}

void ActiveListener::fire()
{
	if(m_func)
		m_func(m_active, m_param);
}
