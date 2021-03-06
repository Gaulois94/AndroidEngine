#include "Map/Tiles/StaticTile.h"

StaticTile::StaticTile(Updatable* parent, Material* mtl, const Texture* texture, const Rectangle2f& subRect, const Rectangle2f& conf, void* info) : Tile(parent, mtl, Rectangle3f(conf, 0, 0), info), m_sprite(this, mtl, texture)
{
	m_sprite.setSubTextureRect(subRect);
}

void StaticTile::onDraw(Render& render, const glm::mat4& mvp)
{
}

void StaticTile::setMaterial(Material* material)
{
	Drawable::setMaterial(material);
	m_sprite.setMaterial(material);
}
