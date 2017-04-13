#ifndef  ALERTDIALOG_INC
#define  ALERTDIALOG_INC

#include "Widgets/Alert.h"
#include "Widgets/Button.h"

class AlertDialog : public Alert, public Transformable
{
	public:
		AlertDialog(Render* render, Drawable* innerDrawwable, Button* cancel, Button* ok);
	private:
		Drawable* m_drawable;
		Button* m_cancelBut;
		Button* m_okBut;
};

#endif
