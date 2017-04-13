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
#include "Render.h"
#include "TextInterface.h"

/** \brief manage a text on the screen.
 * The height of a text is 1.0f exactly. The width depends of the length of the text and the Font.
 * The default position is (0.0, 0.0, 0.0) */
class Text : public Drawable, public TextInterface
{
	public:
		/** \brief Create a Text object from a font and a string.
		 * \param parent its parent
		 * \param material The text material
		 * \param font the text font
		 * \param text the text string*/
		Text(Updatable* parent, Material* material, const Font* font, const char* text);

		/** \brief Create an empty text.*/
		Text();

		virtual void setText(const char* text);
		virtual void setFont(const Font* font);

		virtual void onDraw(Render& renderer, const glm::mat4& mvp=glm::mat4(1.0f));

		glm::vec2 getCharPosition(uint32_t index, bool useScale=true) const;
		glm::vec2 getCharSize(uint32_t index) const;
		int getCharAt(float x, float y);
	protected:
		void initVbos(float* letterCoords, float* textureCoord);
};

#endif
