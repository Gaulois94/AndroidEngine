#ifndef  STATICDATAS_INC
#define  STATICDATAS_INC

#include "Graphics/Rectangle2.h"
#include "Graphics/Texture.h"
#include "Updatable.h"
#include "Map/Tiles/StaticTile.h"
#include "Graphics/Materials/Material.h"

typedef StaticTile*(*createStaticTilePtr)(Updatable* parent, const Texture*, const Rectangle2f&);

struct StaticDatas
{
	createStaticTilePtr createStaticTile;
	Material*           material;
};

#endif
