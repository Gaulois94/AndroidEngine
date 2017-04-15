#ifndef  ALERTDIALOG_INC
#define  ALERTDIALOG_INC

#include "Widgets/Alert.h"
#include "Widgets/Button.h"

/** \class AlertDialog
 * \brief Alert object to propose a dialog with maximum two outside possible (ok and cancel).
 * The Button and the message are at the charge of the user, as are their Listeners*/
class AlertDialog : public Alert, public Transformable
{
	public:
		/** \brief Constructor
		 * \param render The render from where the AlertDialog will be modal (use getRenderParent !)
		 * \param innerDrawable The drawable of the AlertDialog (A text, an image, etc)
		 * \param cancel The Cancel Button (at the left). You have to handle its own listener.
		 * \param ok The OK Button (at the right). You have to handle its own listener*/
		AlertDialog(Render* render, Drawable* innerDrawable, Button* cancel, Button* ok);
	private:
		Drawable* m_drawable;
		Button* m_cancelBut;
		Button* m_okBut;
};

#endif
