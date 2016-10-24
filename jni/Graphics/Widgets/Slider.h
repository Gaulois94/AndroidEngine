#include "Drawable.h"
#include "Button.h"
#include "Orientation.h"
#include "EventManager.h"

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
		void onUpdate(Render &render);
		void onDraw(Render& render, const glm::mat4& mvp);
		void onMove(uint32_t pointerEvent);

		void setOrientation(const Orientation &position);
		float getValue() const;
	private:
		Rectangle m_background;
		Button m_cursor;

		float m_minValue;
		float m_maxValue;
		float m_value;

		Orientation m_position;
		TouchCoord  m_touchCoord;
		int m_pourcentageGlobalRectangle;
};
