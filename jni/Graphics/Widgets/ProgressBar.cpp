#include "Widgets/ProgressBar.h"

ProgressBar::ProgressBar(Updatable* parent, Material* backgroundMtl, Material* cursorMtl, float valueMax, const Orientation& position) : Drawable(parent, NULL, Rectangle3f(0.0, 0.0, 0.0, 1.0, 1.0, 0.0)), m_backgroundMtl(backgroundMtl), m_cursorMtl(cursorMtl), m_background(NULL, backgroundMtl), m_cursorRectangle(NULL, cursorMtl), m_maxValue(valueMax), m_orientation(position)
{
	m_cursorRectangle.setApplyTransformation(this);
	m_background.setApplyTransformation(this);
}

void ProgressBar::onDraw(Render& render, const glm::mat4& mvp)
{
	m_background.onDraw(render, mvp);
	if(m_cursorMtl)
	{
		//Save the old value of this material
		Rectangle2f cursorClipping = m_cursorMtl->getClipping();
		bool cursorEnableClipping  = m_cursorMtl->getEnableClipping();

		//Change the clipping of the rectangle
		m_cursorMtl->enableClipping(true);
		if(m_maxValue == 0)
			m_cursorMtl->setClipping(Rectangle2f(0.0, 0.0, 0.0, 0.0));
		else
		{
			switch(m_orientation)
			{
				case VERTICAL:
					m_cursorMtl->setClipping(Rectangle2f(0.0, 0.0, 1.0, m_value/m_maxValue));
					break;

				case HORIZONTAL:
					m_cursorMtl->setClipping(Rectangle2f(0.0, 0.0, m_value/m_maxValue, 1.0));
					break;
				default:
					break;
			}
		}

		m_cursorRectangle.onDraw(render, mvp);

		//Restore the clipping
		m_cursorMtl->enableClipping(cursorEnableClipping);
		m_cursorMtl->setClipping(cursorClipping);
	}
	else
		m_background.onDraw(render, mvp);
}
