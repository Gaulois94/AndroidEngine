#ifndef  FIREUPDATE_INC
#define  FIREUPDATE_INC

class FireUpdate
{
	public:
		/** \brief default constructor
		 * \param func the func to be called
		 * \param data the data passed to the func*/
		FireUpdate(void(*func)(void*), void* data);

		/** \brief call the func with the data if the func exists*/
		void fire();
	private:
		void (*m_func)(void*);
		void* m_data;
};

#endif
