#include "Map/Tiles/TileObject.h"

TileObject::TileObject(Updatable* parent, uint32_t nbCasesX, uint32_t nbCasesY, uint32_t tileSizeX, uint32_t tileSizeY, void* info) : Tile(parent, NULL, Rectangle3f(0.0, 0.0, 0.0, nbCasesX*tileSizeX, nbCasesY*tileSizeY, 0.0), info), m_tileSizeX(tileSizeX), m_tileSizeY(tileSizeY)
{
	m_nbCasesX = nbCasesX;
	m_nbCasesY = nbCasesY;
	for(uint32_t i=0; i < nbCasesX; i++)
	{
		m_tiles.push_back(std::vector<Tile*>());
		for(uint32_t j=0; j < nbCasesY; j++)
			m_tiles[i].push_back(NULL);
	}
}

void TileObject::onDraw(Render& render, const glm::mat4& mvp)
{
}

void TileObject::addTile(Tile* tile, uint32_t x, uint32_t y)
{
	if(!tile || x >= m_nbCasesX || y >= m_nbCasesY)
		return;

	LOG_ERROR("ADD TILE IN OBJECT");
	addTransformable(tile);
	tile->setParent(this);
	tile->setPosition(glm::vec3(x*m_tileSizeX, (m_nbCasesY - 1 - y) * m_tileSizeY, 0.0));
	LOG_ERROR("RELATIVE POSITION %d, %d", x*m_tileSizeX, (m_nbCasesY - 1 - y) * m_tileSizeY);
	m_tiles[x][y] = tile;
}
