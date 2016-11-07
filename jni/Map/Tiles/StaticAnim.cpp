#include "Map/Tiles/StaticAnim.h"

StaticAnim::StaticAnim(Updatable* parent, Material* mtl, const Texture* texture, void* info, uint32_t n, uint32_t nX, uint32_t currentN, uint32_t posX, uint32_t posY, uint32_t sizeX, uint32_t sizeY, uint32_t spacX, uint32_t spacY, uint32_t tilePosX, uint32_t tilePosY) : Tile(parent, mtl, texture, info, Rectangle3f(0, 0, 0, sizeX, sizeY, 0)), m_anim(this, mtl, texture, Vector2f(posX, posY), Vector2f(spacX, spacY), Vector2f(sizeX, sizeY), nX, n, 10)
{}
