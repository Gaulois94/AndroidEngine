#include "Widgets/AlertMessage.h"
#include "Render.h"

AlertMessage::AlertMessage(Render* render, Drawable* message, uint32_t nbFrame) : Alert(render), Transformable(), m_message(message), m_nbFrame(nbFrame)
{
	if(m_message)
	{
		m_message->setApplyTransformation(this);
		m_message->setParent(this);
		setDefaultConf(m_message->getInnerRect());
	}
}

void AlertMessage::update(Render& render)
{
	LOG_ERROR("M_CURRENTNBFRAME %d", m_currentNbFrame);
	if(m_nbFrame < m_currentNbFrame)
		close();
	else
	{
		m_currentNbFrame++;
		Updatable::update(render);
	}
}
