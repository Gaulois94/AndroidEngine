#include "Map/Tiles/TileObject.h"

TileObject::TileObject(Updatable* parent, uint32_t nbCasesX, uint32_t nbCasesY, uint32_t tileSizeX, uint32_t tileSizeY, void* info) : Tile(parent, NULL, Rectangle3f(0.0, 0.0, 0.0, nbCasesX*tileSizeX, nbCasesY*tileSizeY, 0.0), info), m_nbCasesX(nbCasesX), m_nbCasesY(nbCasesY), m_tileSizeX(tileSizeX), m_tileSizeY(tileSizeY)
{
	for(uint32_t i=0; i < nbCasesX; i++)
	{
		m_tiles.push_back(std::vector<Tile*>());
		for(uint32_t j=0; j < nbCasesY; j++)
			m_tiles[i].push_back(NULL);
	}
}

void TileObject::onDraw(Render& render, const glm::mat4& mvp)
{
	for(uint32_t i=0; i < m_nbCasesX; i++)
		for(uint32_t j=0; j < m_nbCasesY; j++)
			if(m_tiles[i][j])
				m_tiles[i][j]->draw(render, mvp);
}

void TileObject::addTile(Tile* tile, uint32_t x, uint32_t y)
{
	if(x >= m_nbCasesX || y >= m_nbCasesY)
		return;
	tile->setParent(this);
	tile->setPosition(glm::vec3(x*m_tileSizeX, y*m_tileSizeY, 0.0));
	m_tiles[x][y] = tile;
}

uint32_t TileObject::getNbCasesX() const
{
	return m_nbCasesX;
}

uint32_t TileObject::getNbCasesY() const
{
	return m_nbCasesY;
}
