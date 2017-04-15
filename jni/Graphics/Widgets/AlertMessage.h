#ifndef  ALERTMESSAGE_INC
#define  ALERTMESSAGE_INC

#include "Widgets/Alert.h"
#include "Transformable.h"
#include "Drawable.h"

/** \class AlertMessage
 * \brief Alert object to propose a message (Drawable) and will close after a number of frames determined (if still updatable)*/
class AlertMessage : public Alert, public Transformable
{
	public:
		/** \brief Constructor.
		 * \param message the Drawable which will be modal and will close in nbFrame frames
		 * \param nbFrame the number of frame before the AlertDialog will close */
		AlertMessage(Render* render, Drawable* message, uint32_t nbFrame);
		void update(Render& render);
	private:
		Drawable* m_message;
		uint32_t m_nbFrame;
		uint32_t m_currentNbFrame=0;

};

#endif
