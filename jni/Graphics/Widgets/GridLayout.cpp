#include "GridLayout.h"

GridLayout::GridLayout(Updatable* parent) : Updatable(parent), GroupTransformable()
{}

void GridLayout::addWidget(Drawable* drawable, uint32_t x, uint32_t y, uint32_t nbXCases, uint32_t nbYCases)
{
	if(drawable == NULL || nbYCases < 1 || nbXCases < 1)
		return;

	//Complete the number of columns
	for(uint32_t i=m_widgets.size(); i <= x; i++)
	{
		m_widgets.push_back(std::vector<Drawable*>());
		m_widgetsSize.push_back(std::vector<Vector2ui>());
	}

	//Complete the number of rows
	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		for(uint32_t j=m_widgets[i].size(); j <= y; j++)
		{
			m_widgets[i].push_back(NULL);
			m_widgetsSize[i].push_back(Vector2ui());
		}
	}

	m_widgets[x][y]       = drawable;
	m_widgetsSize[x][y].x = nbXCases;
	m_widgetsSize[x][y].y = nbYCases;

	for(uint32_t i=x; i < x+nbXCases-1; i++)
	{
		for(uint32_t j=y; j < y+nbYCases-1; j++)
		{
			//Useful for accessing the drawable easily. Use m_widgetsSize for knowing if the widgets is indeed localized here or not
			m_widgets[i][j]       = drawable;
			m_widgetsSize[i][j].x = m_widgetsSize[i][j].y = 0;
		}
	}


	drawable->setParent(this);
	addTransformable(drawable);
	resetPosition();
}

void GridLayout::resetPosition()
{
	//Get all Drawables' size and determine the maximum
	float maxSizeX = 0, maxSizeY = 0;
	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		for(uint32_t j=0; j < m_widgets[i].size(); j++)
		{
			if(m_widgets[i][j] && m_widgetsSize[i][j].x != 0)
			{
				Rectangle3f colRect = m_widgets[i][j]->getRect();
				Vector2ui& caseSize = m_widgetsSize[i][j];

				maxSizeX = fmax(colRect.width / (float)caseSize.x, maxSizeX);
				maxSizeY = fmax(colRect.height / (float)caseSize.y, maxSizeY);
			}
		}
	}

	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		for(uint32_t j=0; j < m_widgets[i].size(); j++)
		{
			if(m_widgets[i][j] && m_widgetsSize[i][j].x != 0)
			{
				m_widgets[i][j]->setResquestSize(glm::vec3(maxSizeX * m_widgetsSize[i][j].x, maxSizeY * m_widgetsSize[i][j].y, 1.0), true);
				m_widgets[i][j]->setPosition(glm::vec3(maxSizeX*i, maxSizeY*j, 0.0f));
			}
		}
	}
}
