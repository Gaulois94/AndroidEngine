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

void Alert::close()
{
	if(m_listener)
		m_listener->fire();
	if(m_render)
	{
		m_render->setAlert(NULL);
		m_render = NULL;
	}
}
