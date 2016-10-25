#include "Drawable.h"
#include "Button.h"
#include "Orientation.h"
#include "EventManager.h"
#include "Shape/Rectangle.h"
#include <cmath>

class Slider : public Drawable, public Active
{
	public:
		enum SliderStyle
		{
			LINEAIRE,
			BUTTON
		};

		Slider(Updatable *parent, Material* backgroundMaterial, Material* cursorMaterial, uint32_t valueMin, uint32_t valueMax, const Orientation& position = Orientation::VERTICAL, int pourcentageGlobalRectangle=100);

		~Slider();

		bool howActive();
		bool howDisactive();
		bool howSelect();
		bool howDeselect();

		void onUpdate(Render &render);
		void onDraw(Render& render, const glm::mat4& mvp);
		void onMove(const TouchEvent& te);

		void setOrientation(const Orientation &position);
		float getValue() const;
		void updateCursorPosition();
	private:
		Rectangle m_background;
		Rectangle m_cursorRectangle;
		Button m_cursor;

		float m_minValue;
		float m_maxValue;
		float m_value;
		float m_lastValue = 0;

		Orientation m_orientation;
		TouchCoord  m_touchCoord;
		bool m_hasStartMoving=false;
		int m_pourcentageGlobalRectangle;
};
