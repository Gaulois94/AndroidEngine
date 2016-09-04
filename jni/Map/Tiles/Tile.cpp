#include "Map/Tiles/Tile.h"
#include "logger.h"

Tile::Tile(Updatable* parent, Material* mtl, const Rectangle3f& rect, void* info) : Drawable(parent, mtl, rect), m_info(info), m_canDestroy(false), m_nbCasesX(1), m_nbCasesY(1)
{
}

void* Tile::getInfo()
{
	return m_info;
}

bool Tile::canDestroy()
{
	return m_canDestroy;
}

uint32_t Tile::getNbCasesX() const
{
	return m_nbCasesX;
}

uint32_t Tile::getNbCasesY() const
{
	return m_nbCasesY;
}
