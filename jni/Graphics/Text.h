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

/** \brief manage a text on the screen. */
class Text : public Drawable
{
	public:
		/** \brief Create a Text object from a font and a string.
		 * \param parent its parent
		 * \param material The text material
		 * \param font the text font
		 * \param text the text string*/
		Text(Updatable* parent, Material* material, Font* font, const char* text);

		/** \brief Create an empty text.*/
		Text();
		~Text();

		virtual void onDraw(Render& renderer, const glm::mat4& mvp=glm::mat4(1.0f));

		/** \brief set the font of the text
		 * \param font the new font. The user should store the font somewhere (for example on a ResourcesManager) */
		void setFont(Font* font);

		/** \brief set the text string.
		 * \param text the new string */
		void setText(const char* text);

		/** \brief get the text font.
		 * \return the font associated with the text.*/
		const Font* getFont() const;

		/** \brief get the text string.
		 * \return the text string.*/
		const char* getText() const;
	protected:
		void initVbos(float* letterCoords, float* textureCoord);
		Font*  m_font;
		char*  m_text;

		static short drawOrder[6];
};

#endif
