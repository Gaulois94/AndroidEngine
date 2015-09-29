#ifndef DEF_ANIMATION
#define DEF_ANIMATION

#include "Sprite.h"
#include "Vector2.h"

/** \brief basic Animation class*/
class Animation : public Sprite
{
	public:
		/** \brief Basic constructor of the Animation
		 * \param material the sprite material
		 * \param texture the animation texture
		 * \param n How many sub sprite the texture contains
		 * \param nbFrame After how many frame should we change the animation sub sprite */
		Animation(Material* material, Texture* texture, uint32_t n, uint32_t nbFrame);

		/** \brief set the current sub sprite to the n position.
		 * \param n the n sub sprite of the animation.*/
		virtual void setSubNSpriteCoords(uint32_t n)=0;
		void onDraw(Renderer* renderer, glm::mat4& mvp);
	private:
		uint32_t m_n;
		uint32_t m_nbFrame;
}

#endif
