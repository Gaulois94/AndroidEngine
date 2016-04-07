#ifndef  TEMPLATETILE_INC
#define  TEMPLATETILE_INC

#include "Graphics/Texture.h"
#include "Graphics/Rectangle2.h"
#include "Map/Tiles/StaticTile.h"
#include "Map/Tiles/DynamicAnim.h"
#include "Map/Tiles/Tile.h"
#include "Map/Tiles/TileObject.h"

template <class T> StaticTile* staticTileFactory(Updatable* parent, Material* mtl, const Texture* texture, const Rectangle2f& rect) 
{
	return (StaticTile*)(new T(parent, mtl, texture, rect));
}

template <class T> Tile* dynamicTileFactory(Updatable* parent, Material* mtl, const Texture* texture, const Rectangle2f* rect, const Rectangle2f** rectAnimation, uint32_t currentN, uint32_t nbFrames)
{
	return new T(parent, mtl, texture, rect, rectAnimation, currentN, nbFrames);
}

template <class T> TileObject* objectFactory(Updatable* parent, uint32_t nbCasesX, uint32_t nbCasesY, uint32_t tileSizeX, uint32_t tileSizeY)
{
	return new T(parent, nbCasesX, nbCasesY, tileSizeX, tileSizeY);
}

#endif
