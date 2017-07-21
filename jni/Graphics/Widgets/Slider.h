#ifndef SLIDER_INC
#define SLIDER_INC

#include "Drawable.h"
#include "Button.h"
#include "Graphics/Widgets/Orientation.h"
#include "EventManager.h"
#include "Shape/Rectangle.h"
#include <cmath>

class Slider : public Drawable
{
	public:
		enum SliderStyle
		{
			LINEAIRE,
			BUTTON
		};

		Slider(Updatable *parent, Material* backgroundMaterial, Material* cursorMaterial, float valueMin, float valueMax, const Orientation& position = Orientation::VERTICAL, int pourcentageGlobalRectangle=100);

		~Slider();

		void onUpdate(Render& render);
		void draw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		bool onMoveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));

		void setOrientation(const Orientation &position);
		float getValue() const;
		void updateCursorPosition();

		void setLimits(float valueMin, float valueMax);
		void setValue(float value);
	private:
		Rectangle m_background;
		Rectangle m_cursorRectangle;
		Button m_cursor;

		float m_minValue;
		float m_maxValue;
		float m_value = 0;

		Orientation m_orientation;
		glm::vec4 m_oldCoord;
		bool m_hasStartMoving=false;
		int m_pourcentageGlobalRectangle;
};

#endif
