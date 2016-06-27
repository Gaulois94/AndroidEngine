#ifndef  GROUPACTIVABLE_INC
#define  GROUPACTIVABLE_INC

#include "Graphics/Widgets/Active.h"
#include <vector>

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
		 * \param onChange the ActiveListener which will be called*/
		void setOnChangeListener(const ActiveListener& onChange);

		/** \brief Get the ActiveListener called when the Active has changed
		 * \return the function*/
		ActiveListener getOnChangeListener();

		/** \brief Set the Active number i to the state active
		 * \param i the index of the Active.*/
		void setActive(uint32_t i);

		static void changeActive(Active* act, void* grpAct);
	protected:
		Active* m_currentActive;
		std::vector<Active*> m_vectorActive;

		ActiveListener m_onChange;
};

#endif
