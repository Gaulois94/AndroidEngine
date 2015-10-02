#ifndef DEF_BUTTON
#define DEF_BUTTON

#include "Widgets/Widget.h"
#include "Widgets/Active.h"
#include "Sprite.h"
#include "Text.h"

/** \brief Button class, use to create button*/
class Button : public Widget, public Active
{
	public:	
		/** \brief Button constructor with only a Text drawn
		 * \param parent its parent
		 * \param material its material. Could be NULL if you want to keep the Text Material.
		 * \param text the Text drawn
		 * \param rect the button rect. By default, it is the Text dimensions.*/
		Button(Updatable *parent, Material* material, const Text &text, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));

		/** \brief Button constructor with only a Sprite drawn
		 * \param parent its parent
		 * \param material its material. Could be NULL if you want to keep the Image Material.
		 * \param image the Sprite drawn
		 * \param rect the button rect. By default, it is the image dimensions.*/
		Button(Updatable *parent, Material* material, const Sprite &image, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));

		/** \brief Button constructor with a Sprite and a Text drawn
		 * \param parent its parent
		 * \param material its material
		 * \param image the Sprite drawn
		 * \param rect the button rect. By default, it is the image dimensions.*/
		Button(Updatable *parent, Material* material, const Text &text, const Sprite &image, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));

		/** \brief Button constructor, created from nothing
		 * \param parent its parent
		 * \param rect its rect*/
		Button(Updatable *parent=NULL, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));

		virtual void onUpdate(Render &render);
		virtual bool updateSelection();
		virtual bool updateActivation();

		virtual void selectIt();
		virtual void deselectIt();

		/** \brief set the Sprite used*
		 * \param image the new sprite*/
		void setBackground(const Sprite &image);

		/** \brief set the Text used
		 * \param string the new Text*/
		void setText(const Text &string);

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

		bool howSelect();
		bool howDeselect();
		bool howActive();
		bool howDisactive();
	protected:
		/** \brief center the text in the Button*/
		void centerText(); 
		bool m_hasBackground;
		bool m_hasLabel;

		Sprite m_background;
		Text m_text;
		Sprite m_backgroundLighten;
		Text m_textLighten;
		Sprite *m_currentBackground;
		Text *m_currentText;
};

#endif
