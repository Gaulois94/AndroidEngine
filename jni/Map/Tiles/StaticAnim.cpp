#include "Map/Tiles/StaticAnim.h"

StaticAnim::StaticAnim(Updatable* parent, Material* mtl, const Texture* texture, void* info, uint32_t tileID, uint32_t n, uint32_t nX, uint32_t posX, uint32_t posY, uint32_t sizeX, uint32_t sizeY, uint32_t spacX, uint32_t spacY, uint32_t tilePosX, uint32_t tilePosY) : Tile(parent, mtl, Rectangle3f(0, 0, 0, sizeX, sizeY, 0), info), m_anim(this, mtl, texture, Vector2ui(posX, posY), Vector2ui(spacX, spacY), Vector2ui(sizeX, sizeY), nX, n, 10)
{
	m_anim.setSubNSpriteCoords(tileID);	
}

void StaticAnim::onDraw(Render& render, const glm::mat4& mvp)
{}
