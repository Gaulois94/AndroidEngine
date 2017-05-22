#ifndef DEF_BUTTON
#define DEF_BUTTON

#include "Widgets/Active.h"
#include "Rectangle3.h"
#include "GroupDrawable.h"
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

		/** \brief Button constructor with only a Drawable drawn
		 * \param parent its parent
		 * \param image the background drawn
		 * \param rect the button rect. By default, it is the image dimensions.*/
		Button(Updatable *parent, Drawable &image, const Rectangle3f &rect = Rectangle3f(0, 0, 0, 0, 0, 0));

		/** \brief Button constructor with a Drawable and a Text drawn
		 * \param parent its parent
		 * \param image the background drawn
		 * \param rect the button rect. By default, it is the image dimensions.*/
		Button(Updatable *parent, Text &text, Drawable &image, const Rectangle3f &rect = Rectangle3f(0, 0, 0, 0, 0, 0));

		/** \brief Button constructor, created from nothing
		 * \param parent its parent
		 * \param rect its rect*/
		Button(Updatable *parent=NULL, const Rectangle3f &rect = Rectangle3f(0, 0, 0, 0, 0, 0));

		virtual void update(Render &render);
		virtual void onUpdate(Render &render);

		virtual void onDraw(Render &render, const glm::mat4& mvp=glm::mat4(1.0f)){}
		void onFocus(const TouchEvent& te, Render &render, const glm::mat4& mvp=glm::mat4(1.0f));
		void onTouchUp(const TouchEvent& te);

		/** \brief set the Drawable used*
		 * \param image the new sprite*/
		void setBackground(Drawable &image);

		/** \brief set the Text used
		 * \param string the new Text*/
		void setText(Text &string);

		/** \brief get the Text used
		 * \param the Text used*/
		const Text* getText() const;

		/** \brief get the Drawable used
		 * \param the Drawable used*/
		const Drawable* getBackground() const;

		/** \brief tell if the Button has a background
		 * \param Button has a background*/
		bool hasBackground() const;

		/** \brief tell if the Button has a Text
		 * \param Button has a Text*/
		bool hasText()  const;

		virtual void setRequestSize(const glm::vec3& v, bool keepPos=true);
	protected:
		/** \brief center the text in the Button*/
		void centerText(); 
		void setBackgroundScale();

		Drawable* m_background;
		Text* m_text;
};

#endif
