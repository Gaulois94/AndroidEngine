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

class Texture : JniMadeOf
{
	public:
		Texture(int width, int height, int id, const Color& maskColor=Color::TRANSPARENT);
		Texture(int width, int height, const Color& mask=Color::TRANSPARENT);
		Texture(const unsigned char* pixels, int width, int height, bool alpha=true, const Color& mask=Color::TRANSPARENT);
		Texture(const Bitmap* bitmap, const Color& mask=Color::TRANSPARENT);
		~Texture();

		void setMaskColor(const Color& mask);

		//pos and size in pixels
		glm::vec2 pixelsToTextureCoord(const glm::vec2& pos) const;
		FloatRect2 getRect(const glm::vec2& pos, const glm::vec2& size) const;

		GLuint getID() const;
		int getWidth() const;
		int getHeight() const;

		Color getMaskColor() const;

	private:
		int m_width;
		int m_height;
		GLuint m_id;
		Color m_maskColor;
};

#endif
