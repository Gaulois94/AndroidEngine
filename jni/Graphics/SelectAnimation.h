#ifndef DEF_SELECTANIMATION
#define DEF_SELECTANIMATION

#include "Animation.h"

/** \brief The Animation class used for sprite which doesn't have the usual pattern of animation sub sprite*/
class SelectAnimation : public Animation
{
	public:
		/** \brief Animation constructor if sprites haven't the same size, or in the usual pattern.
		 * \param parent its parent
		 * \param material the animation material
		 * \param texture the animation texture
		 * \param rectAnimation array of information (size + position) for each sprites part of the animation*/
		PatternAnimation(Updatable* parent, Material* material, const Texture* texture, const std::vector<Rectangle2ui>& rectAnimation);

		virtual void setSubNSpriteCoords(uint32_t n)=0;

		~PatternAnimation();
	private:
		Rectangle2ui* m_rectAnimation;/** <Store the border of each animation. If null, we will use the other information about the animation (pad, ...)*/
}

#endif
