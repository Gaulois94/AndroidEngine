#ifndef TEXT_INCLUDE
#define TEXT_INCLUDE

#define GLM_FORCE_RADIANS

#include <GLES2/gl2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstring>

#include "Drawable.h"
#include "Color.h"
#include "Font.h"
#include "Renderer.h"

class Text : public Drawable
{
	public:
		Text(Material* material, Font* font, const char* text);
		Text();
		~Text();

		virtual void onDraw(Renderer* renderer, glm::mat4& mvp);
		void setFont(Font* font);
		void setText(const char* text);

		const Font* getFont() const;
		const char* getText() const;
	protected:
		void initVbos(float* letterCoords, float* textureCoord);
		Font*  m_font;
		char*  m_text;

		static short drawOrder[6];
};

#endif
