#ifndef DEF_ANIMATION
#define DEF_ANIMATION

#include "Sprite.h"
#include "Vector2.h"

/** \brief basic Animation class*/
class Animation : public Sprite
{
	public:
		/** \brief Basic constructor of the Animation
		 * \param parent its parent
		 * \param material the sprite material
		 * \param texture the animation texture
		 * \param n How many sub sprite the texture contains
		 * \param nbFrame After how many frame should we change the animation sub sprite */
		Animation(Updatable* parent, Material* material, const Texture* texture, uint32_t n, uint32_t nbFrame);

		/** \brief set the current sub sprite to the n position.
		 * \param n the n sub sprite of the animation.*/
		virtual void setSubNSpriteCoords(uint32_t n);
		void onUpdate(Render& render);

		/** \brief tell if the animation should continue or not.
		 * \param inAnimation The animation continue
		 * \param reset The new animation sprite. 
		 * -1 = unchanged*/
		void setInAnimation(bool inAnimation, int reset=-1);

		/** \brief tell if the animation is playing
		 * \return the animation is playing*/
		bool inAnimation() const;
	protected:
		uint32_t m_maxN; /** <How many sub sprite animation have we in this animation ? */
		uint32_t m_currentN;/** <Store the current played animation*/
		uint32_t m_iFrame; /** <Store how many frames have we played  this current sub animation*/
		uint32_t m_nbFrame;/** <Store how many frame should we wait before set the sub animation*/
		bool m_inAnimation;
};

#endif
