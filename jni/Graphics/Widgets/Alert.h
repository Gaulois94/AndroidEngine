#ifndef  ALERT_INC
#define  ALERT_INC

#include "Updatable.h"

/** \brief create an Alert Widget.
 * The Alert Widget is always at the top of the render of which it is attached*/
class Alert : public Updatable
{
	public:
		/** \brief Constructor
		 * \param render the Render of which the Alert is attached.*/
		Alert(Render* render);
		~Alert();
		virtual void close();
	private:
		Render* m_render;
};

#endif   /* ----- #ifndef ALERT_INC  ----- */
