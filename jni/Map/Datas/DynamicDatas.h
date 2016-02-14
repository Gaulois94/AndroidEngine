#ifndef  DYNAMICDATAS_INC
#define  DYNAMICDATAS_INC

#include "Map/Tile/DynamicTile.h"
#include "Graphics/Texture.h"
#include "Graphics/Rectangle2.h"
#include "Updatable.h"
#include <vector>

typedef DynamicTile*(*createDynamicTilePtr)(Updatable*, Material*, Texture*, const Rectangle2f&, const std::vector<Rectangle2f*>&, uint32_t, uint32_t);

struct DynamicEntity
{
	std::vector          tileRects;
	createDynamicTilePtr createDynamicTile;
	Material*            material;
};

#endif
