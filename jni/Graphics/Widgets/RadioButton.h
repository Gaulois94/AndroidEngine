#ifndef  RADIOBUTTON_INC
#define  RADIOBUTTON_INC

#include "GroupActivable.h"
#include "CheckCircle.h"

class RadioButton : public Updatable, GroupActivable
{
	public:
		RadioButton(Updatable* parent);
		void addCircle(Circle* circle);
	private:
};

#endif
