#include "GridLayout.h"

GridLayout::GridLayout(Updatable* parent) : Drawable(parent, NULL)
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
	drawable->setApplyTransformation(this);
	resetPosition();
}

void GridLayout::resetPosition()
{
	//Get all Drawables' size and determine the maximum
	float maxSizeX = 0, maxSizeY = 0, maxSizeZ = 0;
	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		for(uint32_t j=0; j < m_widgets[i].size(); j++)
		{
			if(m_widgets[i][j] && m_widgetsSize[i][j].x != 0)
			{
				Rectangle3f colRect = m_widgets[i][j]->getInnerRect();
				Vector2ui& caseSize = m_widgetsSize[i][j];

				maxSizeX = fmax(colRect.width / (float)caseSize.x, maxSizeX);
				maxSizeY = fmax(colRect.height / (float)caseSize.y, maxSizeY);
				maxSizeZ = fmax(colRect.depth, maxSizeZ);
			}
		}
	}

	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		for(uint32_t j=0; j < m_widgets[i].size(); j++)
		{
			if(m_widgets[i][j] && m_widgetsSize[i][j].x != 0)
			{
				if(m_rescale)
					m_widgets[i][j]->setRequestSize(glm::vec3(maxSizeX * m_widgetsSize[i][j].x, maxSizeY * m_widgetsSize[i][j].y, 1.0), true);

				glm::vec3 widgetDefaultSize = m_widgets[i][j]->getDefaultSize();
				widgetDefaultSize.x = widgetDefaultSize.x == 0 ? 1.0 : widgetDefaultSize.x;
				widgetDefaultSize.y = widgetDefaultSize.y == 0 ? 1.0 : widgetDefaultSize.y;
				widgetDefaultSize.z = widgetDefaultSize.z == 0 ? 1.0 : widgetDefaultSize.z;

				m_widgets[i][j]->setPosition(glm::vec3(maxSizeX*i, maxSizeY*j, 0.0f) - m_widgets[i][j]->getDefaultPos() * m_widgets[i][j]->getInnerRect().getSize() / widgetDefaultSize);
			}
		}
	}

	//Reset the default size of the layout
	setDefaultSize(glm::vec3(m_widgets.size() * maxSizeX, ((m_widgets.size() > 0) ? m_widgets[0].size() : 0) * maxSizeY, maxSizeZ));

	setBackground(m_background);
}

void GridLayout::removeWidget(uint32_t x, uint32_t y)
{
	removeWidget(m_widgets[x][y]);
}

void GridLayout::removeWidget(Drawable* widget)
{
	if(widget == NULL)
		return;
	bool found = false;
	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		for(uint32_t j=0; j < m_widgets[i].size(); j++)
		{
			if(m_widgets[i][j] == widget)
			{
				found = true;
				m_widgets[i][j]->setParent(NULL);
				m_widgets[i][j] = NULL;
				m_widgetsSize[i][j].x = 0;
				m_widgetsSize[i][j].y = 0;


				//Delete the row and the column if it is the last one and it is empty
				bool del = true;

				//Delete the column if needed
				if(i == m_widgets.size()-1)
				{
					for(uint32_t k=0; k < m_widgets[i].size(); k++)
					{
						if(m_widgets[i][k])
						{
							del = false;
							break;
						}
					}

					if(del)
					{
						m_widgets.pop_back();
						m_widgetsSize.pop_back();
					}
				}

				//Delete the row if needed
				if(j == m_widgets[i].size() - 1)
				{
					for(uint32_t k=0; k < m_widgets.size(); k++)
					{
						if(m_widgets[k][j])
						{
							del = false;
							break;
						}
					}

					if(del)
						for(uint32_t k=0; k < m_widgets.size(); k++)
						{
							m_widgets[k].pop_back();
							m_widgetsSize[k].pop_back();
						}
				}

				goto endFor;
			}
		}
	}

	endFor:
	if(found)
		resetPosition();
}

void GridLayout::removeAll()
{
	//Delete the widgets as children
	for(uint32_t i=0; i < m_widgets.size(); i++)
		for(uint32_t j=0; j < m_widgets[i].size(); j++)
			if(m_widgets[i][j])
				m_widgets[i][j]->setParent(NULL);

	m_widgets.clear();
	m_widgetsSize.clear();
	resetPosition();
}

void GridLayout::setBackground(Drawable* background)
{
	m_background = background;
	if(m_background)
	{
		m_background->setApplyTransformation(this);
		m_background->setRequestSize(getDefaultSize());
		m_background->setPosition(-m_background->getDefaultPos());
	}
}

Rectangle3f GridLayout::getGlobalRect() const
{
	Rectangle3f rect = getRect();
	return getRectAddiction(rect, Updatable::getGlobalRect());
}

glm::mat4 GridLayout::getMatrix() const
{
	glm::mat4 m = Transformable::getMatrix();
	for(uint32_t i=0; i < m_parentTransformables.size(); i++)
		if(m_parentTransformables[i]->getApplyChildrenTransformable())
			m = m_parentTransformables[i]->getApplyChildrenTransformable()->getMatrix() * m;
	return m;
}
