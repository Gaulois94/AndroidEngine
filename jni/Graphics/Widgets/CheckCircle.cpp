#include "CheckCircle.h"

CheckCircle::CheckCircle(Updatable* parent, Material* littleMtl, Material* bigMtl, float radius, uint32_t nbEdge) : GroupDrawable(parent, NULL, m_bigCircle.getDefaultConf()), Active(), m_littleCircle(NULL, littleMtl, radius/2.0, nbEdge), m_bigCircle(NULL, bigMtl, radius, nbEdge)
{
	m_littleCircle.setPositionOrigin(m_littleCircle.getDefaultPos() + m_littleCircle.getDefaultSize()/2.0f);
	m_littleCircle.setPosition(m_bigCircle.getDefaultPos() + m_bigCircle.getDefaultSize()/2.0f);
}

void CheckCircle::onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(!m_isActive)
		Active::activeIt();
	else
		Active::disactiveIt();
}

void CheckCircle::setLittleMtl(Material* mtl)
{
	m_littleCircle.setMaterial(mtl);
}

void CheckCircle::setBigMtl(Material* mtl)
{
	m_bigCircle.setMaterial(mtl);
}

void CheckCircle::activeIt()
{
	m_littleCircle.setCanUpdate(true);
	Active::activeIt();
}

void CheckCircle::disactiveIt()
{
	m_littleCircle.setCanUpdate(false);
	Active::disactiveIt();
}
