#include "PatternAnimation.h"

PatternAnimation::PatternAnimation(Updatable* parent, Material* material, const Texture* texture, const Vector2ui& pos, const Vector2ui& pad, const Vector2ui& size, const Vector2ui& n, uint32_t nSprite, uint32_t nbFrame) : Animation(parent, material, texture, nSprite, nbFrame), m_posX(pos.x), m_posY(pos.y), m_padX(pad.x), m_padY(pad.y), m_width(size.x), m_height(size.y), m_nX(n.x), m_nY(n.y)
{}

void PatternAnimation::setSubNSpriteCoords(uint32_t n)
{
	Animation::setSubNSpriteCoords(n);
	n = n % m_maxN;
	//If we haven't texture, it is useless to set the texture rect
	if(m_texture)
	{
		glm::vec2 pos = glm::vec2(m_posX + (m_padX+m_width) * (n%m_nX), m_posY + (m_padY + m_height)*(n/m_nX));
		Sprite::setSubTextureRect(m_texture->getRect(pos, glm::vec2(m_width, m_height)));
	}
}
