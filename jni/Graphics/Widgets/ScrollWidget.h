#ifndef  SCROLLWIDGET_INC
#define  SCROLLWIDGET_INC

#include "RenderDrawabled.h"
#include "Widgets/Slider.h"
#include "Materials/UniColorMaterial.h"
#include "Materials/TextureMaterial.h"
#include "Axis.h"
#include "logger.h"

#define MAX_SCROLLWINDOW_COUNT     6
#define MAX_SCROLLWINDOW_DISTANCE 20

/** \brief a Widget which handle scrolling*/
class ScrollWidget : public Active, public Drawable
{
	public:
		/** \brief Constructor.
		 * \param parent The parent
		 * \param clipBound The rectangle in which the Widget can move. It is defined with defConf and not by the Transformation
		 * \param defConf The default conf of the Widget.*/
		ScrollWidget(Updatable* parent, const Rectangle2f& clipBound = Rectangle2f(0.0, 0.0, 1.0, 1.0), const Rectangle3f& defConf = Rectangle3f(0.0, 0.0, 0.0, 0.0, 0.0, 0.0));

		/** \brief Destructor*/
		~ScrollWidget();

		void updateGPU(Render& r);
		void updateFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void onTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		bool onMoveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));

		void onUpdate(Render &render);

		/** \brief Set the maximum bound in which the Widget can move. Will automatically set its position if the position is outside the new bound
		 * \param r the new bound*/
		void setMaxBound(const Rectangle2f& r);

		/** \brief Set the move value of the object. It will be corrected by the maximum bound (see setMaxBound)
		 * \param mv the new position*/
		void setMoveValue(const Vector2f& mv);

		void setScrollSpeed(const Vector2f& s) {m_scrollSpeed = s;}

		void setActiveScroll(bool as) {m_activeScroll = as;}

		const Vector2f& getMoveValue() const{return m_value;}
		const Vector2f& getScrollSpeed() const{return m_scrollSpeed;}

		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f)){}
	private:
		Transformable m_childTrans;
		uint32_t m_onFocusCount;
		glm::vec2 m_onFocusPos;
		Vector2f m_xInterval;
		Vector2f m_yInterval;
		Vector2f m_value;
		Vector2f m_oldValue;
		Vector2f m_scrollSpeed;
		Rectangle2f m_maxBound;
		Axis m_axis = XY_AXIS;
		bool m_activeScroll=true;
};

#endif
