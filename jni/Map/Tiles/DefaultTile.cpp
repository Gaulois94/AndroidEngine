#include "Map/Tiles/DefaultTile.h"

DefaultTile::DefaultTile(Updatable* parent, Material* mtl, const Texture* texture, const Rectangle2f& subRect, void* info) : Tile(parent, mtl, Rectangle3f(subRect, 0.0, 0.0), info), m_sprite(this, mtl, texture)
{
	addTransformable(&m_sprite);
	m_sprite.setSubTextureRect(subRect);
}

void DefaultTile::onDraw(Render& render, const glm::mat4& mvp)
{
}
