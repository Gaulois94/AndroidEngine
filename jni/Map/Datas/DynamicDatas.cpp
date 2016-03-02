#include "Datas/DynamicDatas.h"

StaticEntity::StaticEntity(createStaticAnim createStaticAnim, n, nX, posX, posY, sizeX, sizeY, spacX, spacY) :
	m_n(n), m_nX(nX), m_posX(posX), m_posY(posX), m_sizeX(sizeX), m_sizeY(sizeY), m_spacX(spacX), m_spacY(spacY), m_createStaticAnim(createStaticAnim)
{

}

Tile* StaticEntity::createStaticAnim(Updatable* parent, Texture* texture, uint32_t tileID, uint32_t posX, uint32_t posY)
{
	if(m_createStaticAnim)
		return m_createStaticAnim(parent, material, texture, m_n, m_nX, tileID, m_posX, m_posY, m_sizeX, m_sizeY, m_spacX, m_spacY, posX, posY);
	return NULL;
}
