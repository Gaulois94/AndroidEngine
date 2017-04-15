#ifndef  ALERT_INC
#define  ALERT_INC

#include "Updatable.h"
#include "Listeners/Callback.h"

/** \brief create an Alert Widget.
 * The Alert Widget is always at the top of the render of which it is attached*/
class Alert : public Updatable
{
	public:
		/** \brief Constructor
		 * \param render the Render of which the Alert is attached.*/
		Alert(Render* render);

		~Alert();

		/** \brief close the Alert (deleted from the Render). It becomes non-modal then*/
		virtual void close();

		/** \brief set the callback when the Alert is closed OR destroyed
		 * \param callback the Callback pointer.*/
		void setCloseCallback(Callback* callback) {m_listener = callback;}
	private:
		Render* m_render;
		Callback* m_listener=NULL;
};

#endif   /* ----- #ifndef ALERT_INC  ----- */
