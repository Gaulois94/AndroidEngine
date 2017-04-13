#include "Widgets/Alert.h"
#include "Render.h"

Alert::Alert(Render* render) : Updatable(NULL), m_render(render)
{
	if(render)
		render->setAlert(this);
}

Alert::~Alert()
{
	close();
}

virtual void Alert::close()
{
	if(m_render)
		m_render->setAlert(NULL);
}
