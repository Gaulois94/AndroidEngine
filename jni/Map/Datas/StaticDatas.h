#ifndef  STATICDATAS_INC
#define  STATICDATAS_INC

#include "Graphics/Rectangle2.h"
#include "Graphics/Texture.h"
#include "Updatable.h"

typedef StaticTile*(*createStaticTilePtr)(const Texture*, const Rectangle2f&);

struct StaticDatas
{
	createStaticTilePtr createStaticTile;
	Material*           material;
};

#endif
