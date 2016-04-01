#include "Map/Traces/DynamicTrace.h"

DynamicTrace::DynamicTrace(Updatable* parent, const char* name, uint32_t nbCasesX, uint32_t nbCasesY, uint32_t sizeX, uint32_t sizeY) : Trace(parent, Rectangle3f(0.0, 0.0, 0.0, nbCasesX*sizeX, nbCasesY*sizeY, 0.0), name), m_sizeX(sizeX), m_sizeY(sizeY), m_nbCasesX(nbCasesX), m_nbCasesY(nbCasesY)
{
	for(uint32_t i=0; i < nbCasesX; i++)
	{
		m_tiles.push_back(std::vector<Tile*>());
		for(uint32_t j=0; j < nbCasesY; j++)
			m_tiles[i].push_back(NULL);
	}
}

void DynamicTrace::onUpdate(Render& render)
{
	Trace::onUpdate(render);
}

Tile* DynamicTrace::getTile(uint32_t x, uint32_t y)
{
	if(x >= m_nbCasesX * m_sizeX || y >= m_nbCasesY * m_sizeY)
		return NULL;
	return m_tiles[x/m_sizeX][y/m_sizeY];
}

void DynamicTrace::addTile(Tile* tile, uint32_t x, uint32_t y)
{
	if(x >= m_nbCasesX * m_sizeX || y >= m_nbCasesY * m_sizeY)
		return;
	m_tiles[x/m_sizeX][y/m_sizeY] = tile;
}
