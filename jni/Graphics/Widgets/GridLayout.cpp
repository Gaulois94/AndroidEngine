#include "GridLayout.h"

GridLayout::GridLayout(Updatable* parent) : Drawable(parent, NULL), m_changeCallback(GridLayout::childrenTransfListener, (void*)this)
{}

void GridLayout::addWidget(Drawable* drawable, uint32_t x, uint32_t y, uint32_t nbXCases, uint32_t nbYCases)
{
	if(drawable == NULL || nbYCases < 1 || nbXCases < 1)
		return;

	//Complete the number of columns
	for(uint32_t i=m_widgets.size(); i <= x+nbXCases-1; i++)
	{
		m_widgets.push_back(std::vector<Drawable*>());
		m_widgetsSize.push_back(std::vector<Vector2ui>());
	}

	//Complete the number of rows
	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		for(uint32_t j=m_widgets[i].size(); j <= y+nbYCases-1; j++)
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
	drawable->setChangeCallback(&m_changeCallback);
	resetPosition();
}

void GridLayout::setPadding(const Vector2f& padding)
{
	m_padding = padding;
	resetPosition();
}

void GridLayout::resetPosition()
{
	std::vector<std::vector<glm::vec3>> crSize; //Column / row size
	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		crSize.push_back(std::vector<glm::vec3>());
		for(uint32_t j=0; j < m_widgets[i].size(); j++)
			crSize[i].push_back(glm::vec3(0.0, 0.0, 0.0));
	}

	//Get all Drawables' size and determine the maximum
	float maxSizeZ = 0;
	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		float maxSizeY = 0;
		for(uint32_t j=0; j < m_widgets[i].size(); j++)
		{
			if(m_widgets[i][j] && (m_widgetsSize[i][j].x != 0 || m_widgetsSize[i][j].y != 0))
			{
				Rectangle3f colRect = m_widgets[i][j]->getInnerRect();
				Vector2ui& caseSize = m_widgetsSize[i][j];

				//Update the cr table and get the maxSizeX for row
				float maxSizeX = 0;
				if(caseSize.x != 0)
					maxSizeX = colRect.width / (float)caseSize.x;
				maxSizeY       = (caseSize.y != 0) ? fmax(colRect.height / (float)caseSize.y, maxSizeY) : maxSizeY;
				for(uint32_t k=0; k < j; k++)
				{
					maxSizeX       = fmax(crSize[i][k].x, maxSizeX);
					crSize[i][k].x = maxSizeX;
				}

				//Update the cr table from column
				for(uint32_t k=0; k < i; k++)
					crSize[k][j].y = maxSizeY;

				maxSizeZ = fmax(colRect.depth, maxSizeZ);
				for(uint32_t i2=0; i2 < m_widgetsSize[i][j].x; i2++)
					crSize[i+i2][j].x = maxSizeX;

				for(uint32_t j2=0; j2 < m_widgetsSize[i][j].y; j2++)
					crSize[i][j+j2].y = maxSizeY;
			}
		}
	}

	//Update the size and position of all widgets
	//
	//Get the current position of all widgets
	float currentPosX=0;
	for(uint32_t i=0; i < m_widgets.size(); i++)
	{
		float currentPosY=0;
		for(uint32_t j=0; j < m_widgets[i].size(); j++)
		{
			if(m_widgets[i][j] && m_widgetsSize[i][j].x != 0)
			{
				m_widgets[i][j]->setChangeCallback(NULL);
				if(m_rescale)
				{
					/* Need to get the widgets size (all column and row size aren't the same...*/
					float currentSizeX=0;
					float currentSizeY=0;
					for(uint32_t i2=0; i2 < m_widgetsSize[i][j].x; i2++)
						currentSizeX+=crSize[i+i2][j].x;

					for(uint32_t j2=0; j2 < m_widgetsSize[i][j].y; j2++)
						currentSizeY+=crSize[i][j+j2].y;
					m_widgets[i][j]->setRequestSize(glm::vec3(currentSizeX, currentSizeY, 1.0), true);
				}

				glm::vec3 widgetDefaultSize = m_widgets[i][j]->getDefaultSize();
				widgetDefaultSize.x = widgetDefaultSize.x == 0 ? 1.0 : widgetDefaultSize.x;
				widgetDefaultSize.y = widgetDefaultSize.y == 0 ? 1.0 : widgetDefaultSize.y;
				widgetDefaultSize.z = widgetDefaultSize.z == 0 ? 1.0 : widgetDefaultSize.z;

//				m_widgets[i][j]->setPosition(glm::vec3(currentPosX, currentPosY, 0.0f) - m_widgets[i][j]->getDefaultPos() * m_widgets[i][j]->getInnerRect().getSize() / widgetDefaultSize);
				m_widgets[i][j]->setPosition(glm::vec3(currentPosX, currentPosY, 0.0f) - m_widgets[i][j]->getDefaultPos());
				m_widgets[i][j]->setChangeCallback(&m_changeCallback);
			}
			currentPosY+=crSize[i][j].y + m_padding.y;
		}
		if(m_widgets[i].size() > 0)
			currentPosX+=crSize[i][0].x + m_padding.x;
	}

	float completeSizeX = 0;
	float completeSizeY = 0;

	for(uint32_t i=0; i < crSize.size(); i++)
	{
		if(crSize[i].size() > 0)
			completeSizeX += crSize[i][0].x;
		completeSizeX += m_padding.x;
	}

	for(uint32_t i=0; crSize.size() > 0 && i < crSize[0].size(); i++)
		completeSizeY += crSize[0][i].y + m_padding.y;

	//Reset the default size of the layout
	setDefaultSize(glm::vec3(completeSizeX, completeSizeY, maxSizeZ));
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
				m_widgets[i][j]->setApplyTransformation(NULL);
				m_widgets[i][j]->setChangeCallback(NULL);
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
			{
				m_widgets[i][j]->setChangeCallback(NULL);
				m_widgets[i][j]->setApplyTransformation(NULL);
				m_widgets[i][j]->setParent(NULL);
			}

	m_widgets.clear();
	m_widgetsSize.clear();
	resetPosition();
}

Rectangle3f GridLayout::getGlobalRect() const
{
	Rectangle3f rect = getRect();
	return getRectAddiction(rect, Updatable::getGlobalRect());
}

void GridLayout::childrenTransfListener(void* data)
{
	GridLayout* self = (GridLayout*)data;
	self->resetPosition();
}
