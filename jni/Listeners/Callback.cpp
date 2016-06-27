#include "Listeners/Callback.h"

Callback::Callback() : m_func(NULL), m_data(NULL)
{}

Callback::Callback(void(*func)(void*), void* data) : m_func(func), m_data(data)
{}

void Callback::fire()
{
	if(m_func)
		m_func(m_data);
}
