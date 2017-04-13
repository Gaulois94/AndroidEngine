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
		Rectangle3f drawableRect = m_drawable->getRect();
		Rectangle3f canButRect;
		Rectangle3f okButRect;

		if(m_cancelBut && m_okBut)
		{
			canButRect = m_cancelBut->getRect();
			okButRect  = m_okBut->getRect();

			//Rescale buttons
			m_okBut->scale(glm::vec3(drawableRect.width / (2*okButRect.width), drawableRect.height/(2*okButRect.height) /* Keep the same ratio*/, 1.0));
			m_cancelBut->scale(glm::vec3(drawableRect.width / (2*canButRect.width), drawableRect.width/(2*canButRect.width) /* Keep the same ratio*/, 1.0));

			//Place object
			double maxHeightBut = fmax(m_okBut->getRect().height, m_cancelBut->getRect().height);
			m_drawable->setPosition(glm::vec3(-drawableRect.x, maxHeightBut - drawableRect.y, 0.0));
			m_cancelBut->setPosition(glm::vec3(0.0, 0.0, 0.0));
			m_okBut->setPosition(glm::vec3(drawableRect.width/2.0, 0.0, 0.0));

			setDefaultSize(glm::vec3(drawableRect.width, maxHeightBut + drawableRect.height, drawableRect.depth));
		}

		else if(m_okBut)
		{
			//Rescale button
			okButRect  = m_okBut->getRect();
			m_okBut->scale(glm::vec3(drawableRect.width / okButRect.width, drawableRect.width/okButRect.width /* Keep the same ratio*/, 1.0));

			//Place objects on the screen
			m_drawable->setPosition(glm::vec3(-drawableRect.x, okButRect.height - drawableRect.y, 0.0));
			m_okBut->setPosition(glm::vec3(0.0, 0.0, 0.0));
			setDefaultSize(glm::vec3(drawableRect.width, okButRect.height + drawableRect.height, drawableRect.depth));
		}

		else if(m_cancelBut)
		{
			//Rescale button
			canButRect = m_cancelBut->getRect();
			m_cancelBut->scale(glm::vec3(drawableRect.width / canButRect.width, drawableRect.width/canButRect.width /* Keep the same ratio*/, 1.0));

			//Place objects on the screen
			m_drawable->setPosition(glm::vec3(-drawableRect.x, canButRect.height - drawableRect.y, 0.0));
			m_cancelBut->setPosition(glm::vec3(0.0, 0.0, 0.0));
			setDefaultSize(glm::vec3(drawableRect.width, canButRect.height + drawableRect.height, drawableRect.depth));
		}
	}
}
