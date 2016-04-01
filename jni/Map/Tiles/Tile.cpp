#include "Map/Tiles/Tile.h"

Tile::Tile(Updatable* parent, Material* mtl, const Rectangle3f& rect) : Drawable(parent, mtl, rect), m_info(0), m_canDestroy(false)
{}

uint32_t Tile::getInfo()
{
	return m_info;
}

bool Tile::canDestroy()
{
	return m_canDestroy;
}