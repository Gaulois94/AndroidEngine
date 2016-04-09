#include "Map/Datas/AnimDatas.h"

DynamicEntity::DynamicEntity(createDynamicAnimPtr create) : createDynamicAnim(create), material(NULL), info(NULL)
{
}

DynamicEntity::~DynamicEntity()
{
	for(std::vector<Rectangle2f*>::iterator it=m_tileRects.begin(); it != m_tileRects.end(); it++)
		delete ((*it));
}

void DynamicEntity::addTile(Rectangle2f* subRect, const char* name, const char* type)
{
	m_tileRects.push_back(subRect);
	m_names.push_back(name);
	m_types.push_back(type);
}

const std::vector<Rectangle2f*>* DynamicEntity::getSubRects() const
{
	return &m_tileRects;
}

const std::vector<std::string>*  DynamicEntity::getNames() const
{
	return &m_names;
}

const std::vector<std::string>*  DynamicEntity::getTypes() const
{
	return &m_types;
}

StaticEntity::StaticEntity(createStaticAnimPtr create, uint32_t n, uint32_t nX, uint32_t posX, uint32_t posY, uint32_t sizeX, uint32_t sizeY, uint32_t spacX, uint32_t spacY) :
	material(NULL), info(NULL),	m_n(n), m_nX(nX), m_posX(posX), m_posY(posX), m_sizeX(sizeX), m_sizeY(sizeY), m_spacX(spacX), m_spacY(spacY), m_createStaticAnim(create)
{

}

StaticAnim* StaticEntity::createStaticAnim(Updatable* parent, const Texture* texture, uint32_t tileID, uint32_t posX, uint32_t posY) const
{
	if(m_createStaticAnim)
		return m_createStaticAnim(parent, material, texture, info, m_n, m_nX, tileID, m_posX, m_posY, m_sizeX, m_sizeY, m_spacX, m_spacY, posX, posY);
	return NULL;
}

const std::vector<std::string>*  StaticEntity::getNames() const
{
	return &m_names;
}

const std::vector<std::string>*  StaticEntity::getTypes() const
{
	return &m_types;
}


void StaticEntity::addEntity(const char* name, const char* type)
{
	m_names.push_back(name);
	m_types.push_back(type);
}
