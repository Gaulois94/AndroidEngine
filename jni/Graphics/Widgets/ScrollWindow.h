#ifndef  SCROLLWINDOW_INC
#define  SCROLLWINDOW_INC

#include "RenderDrawabled.h"
#include "Widgets/Slider.h"
#include "Materials/UniColorMaterial.h"
#include "Materials/TextureMaterial.h"

#define MAX_SCROLLWINDOW_COUNT     6
#define MAX_SCROLLWINDOW_DISTANCE 20

class ScrollWindow : public Active, public RenderDrawabled
{
	public:
		ScrollWindow(Updatable* parent, const Vector2ui& pixelSize=Vector2ui(512, 512));
		~ScrollWindow();

		void updateFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void onTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void onMoveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));

		void onUpdate(Render &render);
	private:
		Transformable m_childTrans;
		uint32_t m_onFocusCount;
		glm::vec2 m_onFocusPos;
		Vector2f m_xInterval;
		Vector2f m_yInterval;
		Vector2f m_value;
		Vector2f m_oldValue;
		TextureMaterial m_renderMaterial;
};

#endif
