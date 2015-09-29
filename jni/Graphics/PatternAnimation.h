#ifndef DEF_PATTERNANNIMATION
#define DEF_PATTERNANNIMATION

#include "Animation.h"
#include "Texture.h"

/** \brief PatternAnimation class handle */
class PatternAnimation : public Animation
{
	public:
		/** \brief Pattern Animation basic constructor
		 * \param material the material annimation
		 * \param texture the animation texture
		 * \param pos the start of the animation texture in pixel. It is used because a tileset animation could contain a lot of sub animation (then we need to know where to start).
		 * \param pad the distance (x, y) between two animation sprite
		 * \param size the size (width, height) of each sprite
		 * \param n the number of sprite(row, column)
		 * \param nSprite the number of sprites*/
		PatternAnimation(Material* material, const Texture* texture, const Vector2ui& pos, const Vector2ui& pad, const Vector2ui& size, const Vector2ui& n, uint32_t nSprite);
	private:
		uint32_t m_posX, m_posY, m_padX, m_padY, m_width, m_height, m_nX, m_nY;
};

#endif
