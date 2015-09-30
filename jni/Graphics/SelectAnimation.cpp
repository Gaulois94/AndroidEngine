#include "SelectAnimation.h"

SelectAnimation::SelectAnimation(Updatable* parent, Material* material, const Texture* texture, const std::vector<Rectangle2ui> rectAnimation) : animation(parent, material, texture, rectAnimation.size()), m_rectAnimation(NULL)
{
	m_rectAnimation = (Rectangle2ui*)malloc(rectAnimation.size()*sizeof(Rectangle2ui));
	for(uint32_t i=0; i < rectAnimation.size(); i++)
		m_rectAnimation = rectAnimation[i];
}

void SelectAnimation::setSubNSpriteCoords(uint32_t n)
{
	m_currentN = n%m_maxN;
	Sprite::setSubTextureRect(*m_rectAnimation[m_currentN]);
}
