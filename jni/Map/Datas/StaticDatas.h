#ifndef  STATICDATAS_INC
#define  STATICDATAS_INC

#include "Graphics/Rectangle2.h"
#include "Graphics/Texture.h"
#include "Updatable.h"
#include "Map/Tiles/StaticTile.h"
#include "Map/Datas/TileData.h"
#include "Graphics/Materials/Material.h"

typedef StaticTile*(*createStaticTilePtr)(Updatable* parent, Material* mtl, const Texture*, const Rectangle2f&, void* info);

struct StaticDatas : public TileData
{
	createStaticTilePtr createStaticTile;
	Material*           material;
	void* info;
};

#endif
