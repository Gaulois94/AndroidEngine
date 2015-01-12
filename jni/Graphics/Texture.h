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

class Texture : JniMadeOf
{
	public:
		Texture(int width, int height);
		Texture(const unsigned char* pixels, int width, int height, bool alpha=true);
		Texture(const Bitmap* bitmap);
		~Texture();

		//pos and size in pixels
		glm::vec2 pixelsToTextureCoord(const glm::vec2& pos) const;
		FloatRect2 getRect(const glm::vec2& pos, const glm::vec2& size) const;

		GLuint getID() const;
		int getWidth() const;
		int getHeight() const;
	private:
		int m_width;
		int m_height;
		GLuint m_id;
};

#endif
