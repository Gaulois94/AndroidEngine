#ifndef  TEMPLATETILE_INC
#define  TEMPLATETILE_INC

#include "Graphics/Texture.h"
#include "Graphics/Rectangle2.h"
#include "Tiles/StaticTile.h"
#include "Tiles/DynamicTile.h"
#include "Tiles/Tile.h"
#include "Tiles/Object.h"

template <class T> StaticTile* staticTileFactory(Material* mtl, Texture* texture, const Rectangle2f* rect) 
{
	return new T(mtl, texture, rect);
}

template <class T> Tile* dynamicTileFactory(Material* mtl, Texture* texture, const Rectangle2f* rect, const Rectangle2f** rectAnimation, uint32_t currentN, uint32_t nbFrames)
{
	return new T(mtl, texture, rect, rectAnimation, currentN, nbFrames);
}

template <class T> Object* objectFactory(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t tileSizeX, uint32_t tileSizeY)
{
	return new T(nbCasesX, nbCasesY, tileSizeX, tileSizeY);
}

#endif
