#ifndef  STATICTILE_INC
#define  STATICTILE_INC

#include "Map/Tiles/Tile.h"

class StaticTile : public Tile
{
	public:
		StaticTile(Material* mtl, Texture* texture, const Rectangle2f& subRect, const Rectangle2f& conf);
		void onDraw();
	private:
		Sprite m_sprite;
};

#endif
