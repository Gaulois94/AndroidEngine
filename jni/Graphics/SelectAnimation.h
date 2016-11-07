#ifndef DEF_SELECTANIMATION
#define DEF_SELECTANIMATION

#include "Animation.h"
#include <vector>

/** \brief The Animation class used for sprite which doesn't have the usual pattern of animation sub sprite*/
class SelectAnimation : public Animation
{
	public:
		/** \brief Animation constructor if sprites haven't the same size, or in the usual pattern.
		 * \param parent its parent
		 * \param material the animation material
		 * \param texture the animation texture
		 * \param rectAnimation array of information (size + position) for each sprites part of the animation
		 * \param nbFrame the number of frame before updating the sprite*/
		SelectAnimation(Updatable* parent, Material* material, const Texture* texture, const std::vector<Rectangle2ui>& rectAnimation, uint32_t nbFrame);
		~SelectAnimation();

		virtual void setSubNSpriteCoords(uint32_t n);

		const Rectangle2ui* getCurrentTextureRect() const;
	private:
		Rectangle2ui* m_rectAnimation;/** <Store the border of each animation.*/
};

#endif
