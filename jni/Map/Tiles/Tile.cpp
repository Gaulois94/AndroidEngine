#include "Map/Tiles/Tile.h"

Tile::Tile(Updatable* parent, Material* mtl, const Rectangle3f& rect, void* info) : Drawable(parent, mtl, rect), m_info(info), m_canDestroy(false)
{}

void* Tile::getInfo()
{
	return m_info;
}

bool Tile::canDestroy()
{
	return m_canDestroy;
}
