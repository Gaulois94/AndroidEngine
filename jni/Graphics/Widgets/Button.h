#ifndef DEF_BUTTON
#define DEF_BUTTON

#include "Widgets/Active.h"
#include "Rectangle3.h"
#include "GroupDrawable.h"
#include "Sprite.h"
#include "Text.h"

/** \brief Button class, use to create button*/
class Button : public GroupDrawable, public Active
{
	public:	
		/** \brief Button constructor with only a Text drawn
		 * \param parent its parent
		 * \param text the Text drawn
		 * \param rect the button rect. By default, it is the Text dimensions.*/
		Button(Updatable *parent, Text &text, const Rectangle3f &rect = Rectangle3f(0, 0, 0, 0, 0, 0));

		/** \brief Button constructor with only a Sprite drawn
		 * \param parent its parent
		 * \param image the Sprite drawn
		 * \param rect the button rect. By default, it is the image dimensions.*/
		Button(Updatable *parent, Sprite &image, const Rectangle3f &rect = Rectangle3f(0, 0, 0, 0, 0, 0));

		/** \brief Button constructor with a Sprite and a Text drawn
		 * \param parent its parent
		 * \param image the Sprite drawn
		 * \param rect the button rect. By default, it is the image dimensions.*/
		Button(Updatable *parent, Text &text, Sprite &image, const Rectangle3f &rect = Rectangle3f(0, 0, 0, 0, 0, 0));

		/** \brief Button constructor, created from nothing
		 * \param parent its parent
		 * \param rect its rect*/
		Button(Updatable *parent=NULL, const Rectangle3f &rect = Rectangle3f(0, 0, 0, 0, 0, 0));

		virtual void update(Render &render);
		virtual void onUpdate(Render &render);
		virtual void onFocus(uint32_t indicePointer, Render &render);

		/** \brief set the Sprite used*
		 * \param image the new sprite*/
		void setBackground(Sprite &image);

		/** \brief set the Text used
		 * \param string the new Text*/
		void setText(Text &string);

		/** \brief get the Text used
		 * \param the Text used*/
		const Text* getText() const;

		/** \brief get the Sprite used
		 * \param the Sprite used*/
		const Sprite* getBackground() const;

		/** \brief tell if the Button has a Sprite
		 * \param Button has a Sprite*/
		bool hasSprite() const;

		/** \brief tell if the Button has a Text
		 * \param Button has a Text*/
		bool hasText()  const;
	protected:
		/** \brief center the text in the Button*/
		void centerText(); 

		Sprite* m_background;
		Text* m_text;
};

#endif
