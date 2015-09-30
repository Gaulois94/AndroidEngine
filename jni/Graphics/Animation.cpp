#include "Animation.h"

Animation::Animation(Updatable* parent, Material* material, Texture* texture, uint32_t n, uint32_t nbFrame) : Sprite(parent, material, texture), m_maxN(n), m_currentN(0), m_iFrame(0), m_nbFrame(nbFrame);

void Animation::onDraw(Renderer* renderer, glm::mat4& mvp)
{
	if(m_iFrame >= m_nbFrame)
	{
		m_iFrame =  0;
		setSubNSpriteCoords((m_currentN+1)%m_maxN);
	}
	else
		m_iFrame++;
	Sprite::onDraw(renderer, mvp);
}
