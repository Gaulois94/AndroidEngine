#ifndef  FIREUPDATE_INC
#define  FIREUPDATE_INC

#include "stdlib.h"

class Callback
{
	public:
		/** \brief default constructor. The function callback and the data send will both be at NULL*/
		Callback();

		/** \brief Another constructor. Init the function callback and the data send
		 * \param func the func to be called
		 * \param data the data passed to the func*/
		Callback(void(*func)(void*), void* data);

		/** \brief call the func with the data if the func exists*/
		void fire();
	private:
		void (*m_func)(void*);
		void* m_data;
};

#endif
