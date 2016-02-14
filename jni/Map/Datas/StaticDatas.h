#ifndef  STATICDATAS_INC
#define  STATICDATAS_INC

#include "Graphique/Rectangle2.h"

typedef Tile*(*createStaticTilePtr)(Texture*, const Rectangle2f*);

struct StaticDatas
{
	createStaticTilePtr createStaticTile;
	Material*           material;
};

#endif
