#include "Map/MapFiles.h"

MapFile::MapFile(const Texture* texture) : m_texture(texture)
{}

const Texture* MapFile::getTexture() const
{
	return m_texture;
}

StaticFile::StaticFile(const Texture* texture, uint32_t spacX, uint32_t spacY, uint32_t sizeX, uint32_t sizeY) : MapFile(texture), m_spacingX(spacX), m_spacingY(spacY), m_tileSizeX(sizeX), m_tileSizeY(sizeY)
{
}

StaticFile::~StaticFile()
{
	for(uint32_t i=0; i < m_tileDatas.size(); i++)
		if(m_tileDatas[i])
			delete m_tileDatas[i];
}

void StaticFile::addStaticDatas(StaticDatas* tileDatas)
{
	m_tileDatas.push_back(tileDatas);
}

Tile* StaticFile::createTile(Updatable* parent, uint32_t tileID, bool def)
{
	if(tileID >= m_tileDatas.size())
		return NULL;
	if(!m_tileDatas[tileID])
		return NULL;

    //Get how many tiles we have in a row.
    //True value : (tWidth - tileSizeX + tileSizeX + spacingX -1) / (tileSizeX + spacingX) + 1 
    //where tileSizeX + spacingX -1 is for rounded the value to the upper case if needed;
	uint32_t numberTileX = (m_texture->getWidth() + m_spacingX - 1) / (m_spacingX + m_tileSizeX) + 1;
	Rectangle2f subRect;

	subRect.x      = (tileID % numberTileX) * (m_tileSizeX + m_spacingX);
	subRect.y      = (tileID / numberTileX) * (m_tileSizeY + m_spacingY);
	subRect.width  = m_tileSizeX;
	subRect.height = m_tileSizeY;

    if(!def)
	{
		if(m_tileDatas[tileID]->createStaticTile)
			return m_tileDatas[tileID]->createStaticTile(parent, m_tileDatas[tileID]->material, m_texture, subRect);
		else
			return NULL;
	}
    return new DefaultTile(parent, NULL, m_texture, subRect);
}

DynamicFile::DynamicFile(Texture* texture) : MapFile(texture)
{}

DynamicFile::~DynamicFile()
{
    for(std::map<std::string, DynamicEntity*>::iterator it=m_dynamicEntities.begin(); it != m_dynamicEntities.end(); it++)
        if(it->second)
            delete it->second;

    for(std::map<std::string, StaticEntity*>::iterator it=m_staticEntities.begin(); it != m_staticEntities.end(); it++)
        if(it->second)
            delete it->second;
}

void DynamicFile::addDynamicEntity(const std::string& key, DynamicEntity* entity)
{
    m_dynamicEntities.insert(std::pair<std::string, DynamicEntity*>(key, entity));
}

void DynamicFile::addStaticEntity(const std::string& key, StaticEntity* entity)
{
    m_staticEntities.insert(std::pair<std::string, StaticEntity*>(key, entity));
}

DynamicEntity* DynamicFile::getDynamicEntity(const std::string& name)
{
    for(std::map<std::string, DynamicEntity*>::iterator it=m_dynamicEntities.begin(); it != m_dynamicEntities.end(); it++)
        if(it->first == name)
            return it->second;
	return NULL;
}

StaticEntity* DynamicFile::getStaticEntity(const std::string& name)
{
    for(std::map<std::string, StaticEntity*>::iterator it=m_staticEntities.begin(); it != m_staticEntities.end(); it++)
        if(it->first == name)
            return it->second;
	return NULL;
}

DynamicEntity* DynamicFile::getLastDynamicEntity()
{
    return (m_dynamicEntities.rbegin()->second);
}

StaticEntity*  DynamicFile::getLastStaticEntity()
{
    return (m_staticEntities.rbegin()->second);
}
