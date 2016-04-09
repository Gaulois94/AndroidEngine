#include "Map/Tiles/DefaultTile.h"

DefaultTile::DefaultTile(Updatable* parent, Material* mtl, const Texture* texture, const Rectangle2f& subRect) : Tile(parent, mtl, Rectangle3f(subRect, 0.0, 0.0)), m_sprite(this, mtl, texture)
{
	m_sprite.setSubTextureRect(subRect);
}

void DefaultTile::onDraw(Render& render, const glm::mat4& mvp)
{
	LOG_ERROR("DEFAULT TILE ON DRAW");
	m_sprite.draw(render, mvp);
}
