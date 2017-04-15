#include "Widgets/AlertDialog.h"

AlertDialog::AlertDialog(Render* render, Drawable* innerDrawable, Button* cancel, Button* ok) : Alert(render), Transformable(), m_drawable(innerDrawable), m_cancelBut(cancel), m_okBut(ok)
{
	//Apply the AlertDialog as Parent
	if(m_drawable)
	{
		m_drawable->setParent(this);
		m_drawable->setApplyTransformation(this);
	}
	if(m_okBut)
	{
		m_okBut->setParent(this);
		m_okBut->setApplyTransformation(this);
	}
	if(m_cancelBut)
	{
		m_cancelBut->setParent(this);
		m_cancelBut->setApplyTransformation(this);
	}

	if(m_drawable)
	{
		m_drawable->setPosition(glm::vec3(0.0, 0.0, 0.0));
		Rectangle3f drawableRect = m_drawable->getInnerRect();
		Rectangle3f canButRect;
		Rectangle3f okButRect;

		if(m_cancelBut && m_okBut)
		{
			canButRect = m_cancelBut->getInnerRect();
			okButRect  = m_okBut->getInnerRect();

			//Rescale buttons
//			m_okBut->scale(glm::vec3(drawableRect.width / (2*okButRect.width), drawableRect.height/(2*okButRect.height) /* Keep the same ratio*/, 1.0));
			m_okBut->setRequestSize(glm::vec3(drawableRect.width/2.0f, m_okBut->getDefaultSize().y, m_okBut->getDefaultSize().z));
//			m_cancelBut->scale(glm::vec3(drawableRect.width / (2*canButRect.width), drawableRect.width/(2*canButRect.width) /* Keep the same ratio*/, 1.0));
			m_cancelBut->setRequestSize(glm::vec3(drawableRect.width/2.0f, m_cancelBut->getDefaultSize().y, m_cancelBut->getDefaultSize().z));

			//Place object
			double maxHeightBut = fmax(okButRect.height, canButRect.height);
			m_drawable->setPosition(glm::vec3(-drawableRect.x, maxHeightBut - drawableRect.y, 0.0));
			m_cancelBut->setPosition(glm::vec3(0.0, 0.0, 0.0));
			m_okBut->setPosition(glm::vec3(drawableRect.width/2.0, 0.0, 0.0));

			setDefaultSize(glm::vec3(drawableRect.width, maxHeightBut + drawableRect.height, drawableRect.depth));
		}

		else if(m_okBut)
		{
			//Rescale button
			okButRect  = m_okBut->getInnerRect();
			m_okBut->setRequestSize(glm::vec3(drawableRect.width, m_okBut->getDefaultSize().y, m_okBut->getDefaultSize().z));

			//Place objects on the screen
			m_drawable->setPosition(glm::vec3(-drawableRect.x, okButRect.height - drawableRect.y, 0.0));
			m_okBut->setPosition(glm::vec3(0.0, 0.0, 0.0));
			setDefaultSize(glm::vec3(drawableRect.width, okButRect.height + drawableRect.height, drawableRect.depth));
		}

		else if(m_cancelBut)
		{
			//Rescale button
			canButRect = m_cancelBut->getInnerRect();
//			m_cancelBut->scale(glm::vec3(drawableRect.width / canButRect.width, drawableRect.width/canButRect.width /* Keep the same ratio*/, 1.0));
			m_cancelBut->setRequestSize(glm::vec3(drawableRect.width, m_cancelBut->getDefaultSize().y, m_cancelBut->getDefaultSize().z));

			//Place objects on the screen
			m_drawable->setPosition(glm::vec3(-drawableRect.x, m_cancelBut->getRect().height - drawableRect.y, 0.0));
			m_cancelBut->setPosition(glm::vec3(0.0, 0.0, 0.0));
			setDefaultSize(glm::vec3(drawableRect.width, canButRect.height + drawableRect.height, drawableRect.depth));
		}
	}
}
