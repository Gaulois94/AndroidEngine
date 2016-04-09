#include "Map/Traces/StaticTrace.h"

StaticTrace::StaticTrace(Updatable* parent, const std::string& name, uint32_t sizeX, uint32_t sizeY, uint32_t nbCasesX, uint32_t nbCasesY,
						 uint32_t padX, uint32_t padY) : Trace(parent, Rectangle3f(padX, padY, 0.0, sizeX * nbCasesX + padX, sizeY * nbCasesY + padY, 0.0), name),
						m_nbCasesX(nbCasesX), m_nbCasesY(nbCasesY), m_sizeX(sizeX), m_sizeY(sizeY), m_padX(padX), m_padY(padY)
{
	for(uint32_t i=0; i < nbCasesX; i++)
	{
		m_tiles.push_back(std::vector<Tile*>());
		for(uint32_t j=0; j < nbCasesY; j++)
			m_tiles[i].push_back(NULL);
	}
}

void StaticTrace::onUpdate(Render& render)
{
	Trace::onUpdate(render);
}

Tile* StaticTrace::getTile(uint32_t x, uint32_t y)
{
	if(x >= m_nbCasesX * m_sizeX - m_padX || y >= m_nbCasesY * m_sizeY - m_padY)
		return NULL;
	return m_tiles[(x - m_padX)/m_sizeX][(y - m_padY)/m_sizeY];
}

void StaticTrace::addTile(Tile* tile, uint32_t x, uint32_t y)
{
	if(x >= m_nbCasesX * m_sizeX - m_padX || y >= m_nbCasesY * m_sizeY - m_padY)
		return;
	m_tiles[(x-m_padX)/m_sizeX][(y-m_padY)/m_sizeY] = tile;
	Trace::addTile(tile, x, y);
}

void StaticTrace::addTileInTraceCoord(Tile* tile, uint32_t x, uint32_t y)
{
	if(x >= m_nbCasesX || y >= m_nbCasesY)
		return;
	m_tiles[x][y] = tile;
	Trace::addTile(tile, x*m_sizeX + m_padX, y*m_sizeY + m_padX);

}
