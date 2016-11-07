#ifndef  TEMPLATETILE_INC
#define  TEMPLATETILE_INC

#include "Graphics/Texture.h"
#include "Graphics/Rectangle2.h"
#include "Map/Tiles/StaticTile.h"
#include "Map/Tiles/DynamicAnim.h"
#include "Map/Tiles/Tile.h"
#include "Map/Tiles/TileObject.h"

template <class T> StaticTile* staticTileFactory(Updatable* parent, Material* mtl, const Texture* texture, const Rectangle2f& rect, void* info) 
{
	return (StaticTile*)(new T(parent, mtl, texture, rect, info));
}

template <class T> StaticAnim* staticAnimFactory(Updatable* parent, Material* mtl, Texture* texture, void* info, uint32_t n, uint32_t nX, uint32_t filePosX, uint32_t filePosY, uint32_t spacingX, uint32_t spacingY, uint32_t sizeX, uint32_t sizeY)
{
	return new T(parent, mtl, texture, info, n, nX, filePosX, filePosY, spacingX, spacingY, sizeX, sizeY);
}

template <class T> DynamicAnim* dynamicTileFactory(Updatable* parent, Material* mtl, const Texture* texture, const std::vector<Rectangle2f*>& rectAnimation, void* info, uint32_t currentN, uint32_t nbFrames, uint32_t posX, uint32_t posY)
{
	return new T(parent, mtl, texture, rectAnimation, info, currentN, nbFrames, posX, posY);
}

template <class T> TileObject* objectFactory(Updatable* parent, uint32_t nbCasesX, uint32_t nbCasesY, uint32_t tileSizeX, uint32_t tileSizeY, void* info)
{
	return new T(parent, nbCasesX, nbCasesY, tileSizeX, tileSizeY, info);
}

#endif
