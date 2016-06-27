#include "Widgets/FireUpdate.h"

FireUpdate::FireUpdate(void(*func)(void*), void* data) : m_func(func), m_data(data)
{}

void FireUpdate::fire()
{
	if(m_func)
		m_func(m_data);
}
