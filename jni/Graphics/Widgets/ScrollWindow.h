#ifndef  SCROLLWINDOW_INC
#define  SCROLLWINDOW_INC

#include "RenderDrawabled.h"
#include "Widgets/Slider.h"
#include "Materials/UniColorMaterial.h"

class ScrollWindow : public Active, public Drawable
{
	public:
		ScrollWindow(Updatable* parent);
		~ScrollWindow();

		void onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void onTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void onMoveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));

		void onUpdate(Render &render);
	private:
		uint32_t m_onFocusCount;
		glm::vec2 m_onFocusPos;
};

#endif
