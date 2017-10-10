#include "Animation.h"

Animation::Animation(Updatable* parent, Material* material, const Texture* texture, uint32_t n, uint32_t nbFrame) : Sprite(parent, material, texture), m_maxN(n), m_currentN(0), m_iFrame(0), m_nbFrame(nbFrame), m_inAnimation(true)
{
}

void Animation::onUpdate(Render& render)
{
	if(m_inAnimation)
	{
		if(m_iFrame >= m_nbFrame)
		{
			m_iFrame =  0;
			setSubNSpriteCoords((m_currentN+1)%m_maxN);
		}
		else
			m_iFrame++;
	}
	Sprite::onUpdate(render);
}

void Animation::setSubNSpriteCoords(uint32_t n)
{
	if(m_maxN > 0)
		m_currentN = n % m_maxN;
}

void Animation::setInAnimation(bool inAnimation, int reset)
{
	if(reset >=0)
		setSubNSpriteCoords(reset%m_maxN);
	m_inAnimation = inAnimation;
}

bool Animation::inAnimation() const
{
	return m_inAnimation;
}
