#include "GridLayout.h"

GridLayout::GridLayout(Updatable* parent) : Updatable(parent), GroupTranformable()
{}

void GridLayout::resetPosition()
{
	//Get all Drawables' size and determine the maximum
	float maxSizeX = 0; maxSizeY = 0;
	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		for(uint32_t j=0; j < m_widgets[i].size(); j++)
		{
			if(m_widgets[i][j])
			{
				Rectangle3f colRect = m_widgets[i][j]->getRect();
				Vector2ui& caseSize = m_widgetsSize[i][j];

				maxSizeX = fmax(colRect.width / caseSize.x, maxSizeX);
				maxSizeY = fmax(colRect.height / caseSize.y, (maxSizeY > 0) ? maxSizeY : -maxSizeY);
			}
		}
	}

	//We start at the bottom
	float currentX = 0, currentY = 0;

	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		for(uint32_t j=0; j < m_widgets[i].size(); j++)
		{
			if(m_widgets[i][j])
			{
				glm::vec3 ds = m_widgets[i][j]->getDefaultSize();
				m_widgets[i][j]->setPosition(glm::vec3(maxSizeX*i, maxSizeY*j, 0.0f));
				m_widgets[i][j]->setScale(glm::vec3(maxSizeX, maxSizeY, 1) / ds * glm::vec3(m_widgetsSize[i][j].x, m_widgetsSize[i][j].y, 1.0));
			}
		}
	}
}
