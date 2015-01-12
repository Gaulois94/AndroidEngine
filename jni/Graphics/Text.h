#ifndef TEXT_INCLUDE
#define TEXT_INCLUDE

#define GLM_FORCE_RADIANS

#include <GLES2/gl2.h>
#include <EGL/egl.h>
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
		Text(Font* font, const char* text, const Color& color);
		Text();
		~Text();

		virtual void onDraw(Renderer* renderer);
		void setFont(Font* font);
		void setText(const char* text);
		void setColor(const Color& color);

		const Font* getFont();
		const char* getText();
		const Color& getColor();
	protected:
		virtual void initVbos();
		float* m_letterCoords;
		float* m_textureCoords;
		Font* m_font;
		char* m_text;
		Color m_color;

		static short drawOrder[6];
};

#endif
