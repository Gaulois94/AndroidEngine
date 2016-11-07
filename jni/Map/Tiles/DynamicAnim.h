#ifndef  DYNAMICANIM_INC
#define  DYNAMICANIM_INC

#include "Map/Tiles/Tile.h"
#include "Graphics/SelectAnimation.h"

class DynamicAnim : public Tile
{
	public:
		DynamicAnim(Updatable* parent, Material* mtl, const Texture* texture, const std::vector<Rectangle2f*>& animRect, void* info, uint32_t currentN, uint32_t nbFrames, uint32_t posX, uint32_t posY);
	private:
		SelectAnimation m_anim;
};

#endif
