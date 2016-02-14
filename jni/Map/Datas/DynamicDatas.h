#ifndef  DYNAMICDATAS_INC
#define  DYNAMICDATAS_INC

#include "Map/Tile.h"
#include "Graphique/Texture.h"
#include "Graphique/Rectangle2.h"

typedef Tile*(*createDynamicTilePtr)(const Rectangle2f*, Texture*, const Rectangle2f**, uint32_t, uint32_t, uint32_t);

struct DynamicEntity
{
	std::vector          tileRects;
	createDynamicTilePtr createDynamicTile;
	Material*            material;
};

#endif
