#ifndef  GROUPACTIVABLE_INC
#define  GROUPACTIVABLE_INC

#include "Graphics/Widgets/Active.h"
#include <vector>

typedef void (*changeFunc_t)(Active*, void*);

/** \brief basic class for activating only an Active at once.*/
class GroupActivable
{
	public:
		GroupActivable();
		void update();

		/** \brief add an activable to the GroupActivable
		 * \param active The Active to add*/
		void addActive(Active* active);

		/** \brief Set the function to call when the Active has changed
		 * \param f the function to call
		 * \param param the parameter to send*/
		void setOnChange(void(*f)(Active*, void*), void* param);

		/** \brief Get the function called when the Active has changed
		 * \return the function*/
		changeFunc_t getOnChangeFunc();

		/** \brief Get the parameter send to the function onChange
		 * \return the parameter*/
		void* getOnChangeParam();

		/** \brief Set the Active number i to the state active
		 * \param i the index of the Active.*/
		void setActive(uint32_t i);

		static void changeActive(Active* act, void* grpAct);
	protected:
		Active* m_currentActive;
		std::vector<Active*> m_vectorActive;
		void (*m_onChange)(Active*, void*);
		void* m_param;
};

#endif
