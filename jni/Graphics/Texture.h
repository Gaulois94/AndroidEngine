#ifndef TEXTURE_INCLUDE
#define TEXTURE_INCLUDE

#define GLM_FORCE_RADIANS

#include <iostream>
#include <GLES2/gl2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Bitmap.h"
#include "JniMadeOf.h"
#include "Rectangle2.h"
#include "logger.h"
#include "Color.h"

/** \brief a OpenGL texture class*/
class Texture : JniMadeOf
{
	public:
		/** \brief create a texture by its openglID, its width, height and maskColor (which color should not be displayed)
		 * \param width the texture's width
		 * \param height the texture's height 
		 * \param id the opengl ID from where the texture is stored
		 * \param maskColor the mask color of the texture. Default : Transparent
		 */
		Texture(int width, int height, int id, const Color& maskColor=Color::TRANSPARENT);

		/** \brief create an empty texture with a width, a height and a mask color
		 * \param width the texture width
		 * \param height the texture height
		 * \param maskColor the maskColor*/
		Texture(int width, int height, const Color& maskColor=Color::TRANSPARENT);

		/** \brief create a texture from a pixel array.
		 * \param pixels an array of pixels. Values are from 0.0f and 1.0f, one value per component (3 values per pixels, or 4 if alpha is enabled).
		 * \param width the texture width
		 * \param height the texture height
		 * \param alpha tell if pixels contains alpha component
		 * \param maskColor the mask color*/
		Texture(const unsigned char* pixels, int width, int height, bool alpha=true, const Color& maskColor=Color::TRANSPARENT);

		/** \brief create a texture a Bitmap object
		 * \param bitmap the bitmap which contains the informations about the pixels array (components plus dimensions)
		 * \param maskColor the texture mask color*/
		Texture(const Bitmap* bitmap, const Color& maskColor=Color::TRANSPARENT);
		~Texture();

		/** \brief set the mask color of the pixel
		 * \param mask the maskColor */
		void setMaskColor(const Color& mask);

		/** \brief Convert the pixels coordinates to the texture coordinates
		 * \param pos the pixels coordinates
		 * \return the texture coordinates*/
		glm::vec2 pixelsToTextureCoord(const glm::vec2& pos) const;

		/** \brief Convert the pixels rectangle to the texture rectangle coordinates
		 * \param pos the pixels(x, y) coordinates
		 * \param size the pixels(width, height) dimensions in pixels 
		 * \return the texture rect which correspond to the pos and size in parameters*/
		FloatRect2 getRect(const glm::vec2& pos, const glm::vec2& size) const;

		/** \brief get the opengl id texture from where the texture is stored in the graphics card.
		 * \return the texture ID */
		GLuint getID() const;

		/** \brief get the width of the texture in pixels
		 * \return the texture's width */
		int getWidth() const;

		/** \brief get the height of the texture in pixels
		 * \return the texture's height */
		int getHeight() const;

		/** \brief get the mask color of the texture
		 * \return the texture's mask color */
		Color getMaskColor() const;
	private:
		int m_width;
		int m_height;
		GLuint m_id;
		Color m_maskColor;
};

#endif
