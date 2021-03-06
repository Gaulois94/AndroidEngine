#include "SelectAnimation.h"

SelectAnimation::SelectAnimation(Updatable* parent, Material* material, const Texture* texture, const std::vector<Rectangle2ui>& rectAnimation, uint32_t nbFrame) : Animation(parent, material, texture, rectAnimation.size(), nbFrame), m_rectAnimation(NULL)
{
	m_rectAnimation = (Rectangle2ui*)malloc(rectAnimation.size()*sizeof(Rectangle2ui));
	for(uint32_t i=0; i < rectAnimation.size(); i++)
		m_rectAnimation[i] = rectAnimation[i];
}

SelectAnimation::SelectAnimation(Updatable* parent, Material* material, const Texture* texture, const std::vector<Rectangle2ui*>& rectAnimation, uint32_t nbFrame): Animation(parent, material, texture, rectAnimation.size(), nbFrame), m_rectAnimation(NULL)
{
	m_rectAnimation = (Rectangle2ui*)malloc(rectAnimation.size()*sizeof(Rectangle2ui));
	for(uint32_t i=0; i < rectAnimation.size(); i++)
		m_rectAnimation[i] = *(rectAnimation[i]);
}

SelectAnimation::~SelectAnimation()
{
	free(m_rectAnimation);
}

void SelectAnimation::setSubNSpriteCoords(uint32_t n)
{
	m_currentN = n%m_maxN;
	Sprite::setSubTextureRect(m_texture->getRect(m_rectAnimation[m_currentN]));
}

const Rectangle2ui* SelectAnimation::getCurrentTextureRect() const
{
	return (m_rectAnimation + m_currentN);
}
