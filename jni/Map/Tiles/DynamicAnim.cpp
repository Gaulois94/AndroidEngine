#include "DynamicAnim.cpp"

DynamicAnim::DynamicAnim(Updatable* parent, Material* mtl, const Texture* texture, const std::vector<Rectangle2f*>& animRect, void* info, uint32_t currentN, uint32_t nbFrames, uint32_t posX, uint32_t posY) : Tile(parent, mtl, Rectangle3f(0, 0, 0, animRect[0]->width, animRect[0]->height, 0.0), info), m_anim(this, mtl, texture, animRect, nbFrames)
{
	m_anim.setSubNSpriteCoords(currentN);
	m_anim.setApplyTransformation(this);
}
