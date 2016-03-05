#ifndef  STATICANIM_INC
#define  STATICANIM_INC

#include "Map/Tiles/Tile.h"
#include "Graphics/PatternAnimation.h"

class StaticAnim : public Tile
{
	public:
		StaticAnim(Updatable* parent, Material* mtl, const Texture* texture, uint32_t n, uint32_t nX, uint32_t currentN, uint32_t posX, uint32_t posY, uint32_t sizeX, uint32_t sizeY, uint32_t spacX, uint32_t spacY, uint32_t tilePosX, uint32_t tilePosY);
	private:
		PatternAnimation m_anim;
};

#endif
