#ifndef DEF_SPRITE_INCLUDE
#define DEF_SPRITE_INCLUDE

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <GLES2/gl2.h>

#include "Drawable.h"
#include "Texture.h"
#include "Rectangle2.h"

/** \brief Square with a Texture.*/
class Sprite : public Drawable
{
	public:
		/** \brief Initialise the sprite by taking the whole texture.
		 * \param parent The sprite parent
		 * \param material The Sprite material.
		 * \param texture A pointer to the Sprite texture.*/
		Sprite(Updatable* parent, Material* material, const Texture* texture);

		/** \brief draw the sprite. If the texture is null, the function will draw a white square.
		 * \param render The Render where the drawable will be drawn
		 * \param transformation Transform the coord of the drawable itself transformed by the renderer's camera before.*/
		void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));

		/** \brief Set the sprite texture.
		 * \param texture the new texture.
		 * \param resetSubTextureRect reset the sprite texture rectangle (the rectangle from where the sprite will draw the pixels). */
		void setTexture(const Texture* texture, bool resetSubTextureRect=true);

		/** \brief set the texture rect.
		 * \param subTextureRect the subtexture rect. */
		void setSubTextureRect(const FloatRect2& subTextureRect);

		/** \brief get the texture from which the sprite is associated.
		 * \return the sprite texture. */
		const Texture* getTexture() const;

		/** \brief get the subtexture rectangle of the sprite.
		 * \return the subtexture rect.*/
		const FloatRect2& getSubTextureRect() const;
	protected:
		void initVbos(float* vertexCoords, float* textureCoords);
		FloatRect2 m_subTextureRect;
		const Texture* m_texture;
};

#endif
