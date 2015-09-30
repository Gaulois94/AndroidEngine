#include "Annimation.h"

PatternAnimation::PatternAnimation(Updatable* parent, Material* material, const Texture* texture, const Vector2ui& pos, const Vector2ui& pad, const Vector2ui& size, uint32_t nRow, uint32_t nSprite) : Animation (parent, material, texture, nSprite) : m_posX(pos.x), m_posY(pos.y), m_padX(pad.x), m_padY(pad.y), m_width(size.x), m_height(size.y), m_nX(n.x)
{}

void PatternAnimation::setSubNSpriteCoords(uint32_t n)
{
	//If we haven't texture, it is useless to set the texture rect
	if(m_texture)
	{
		n = n % m_maxN;
		glm::vec2 pos = glm::vec(m_posX + (m_padX + m_width) * n%m_nX, m_posY + (m_padY + m_height)*n/m_nY);
		Sprite::setSubTextureRect(m_texture.getRect(pos, glm::vec2(m_width, m_height)));
	}
}
