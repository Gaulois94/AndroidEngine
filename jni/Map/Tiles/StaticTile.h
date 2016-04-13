#ifndef  STATICTILE_INC
#define  STATICTILE_INC

#include "Map/Tiles/Tile.h"
#include "Graphics/Sprite.h"

class StaticTile : public Tile
{
	public:
		StaticTile(Updatable* parent, Material* mtl, const Texture* texture, const Rectangle2f& subRect, const Rectangle2f& conf, void* info);
		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void setMaterial(Material* material);
	private:
		Sprite m_sprite;
};

#endif
