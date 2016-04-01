#ifndef  DEFAULTTILE_INC
#define  DEFAULTTILE_INC

#include "Map/Tiles/Tile.h"
#include "Graphics/Sprite.h"

class DefaultTile : public Tile
{
	public:
		DefaultTile(Updatable* parent, Material* mtl, const Texture* texture, const Rectangle2f& subRect);
		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
	private:
		Sprite m_sprite;
};

#endif
