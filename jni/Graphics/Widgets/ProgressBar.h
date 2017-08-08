#ifndef  PROGRESSBAR_INC
#define  PROGRESSBAR_INC

#include "Drawable.h"
#include "Graphics/Widgets/Orientation.h"
#include "Shape/Rectangle.h"

class ProgressBar : public Drawable
{
	public:
		ProgressBar(Updatable* parent, Material* backgroundMtl, Material* cursorMtl, float valueMax, const Orientation& position = Orientation::HORIZONTAL);

		void onDraw(Render& render, const glm::mat4& mvp = glm::mat4(1.0f));

		void setValue(float val) {m_value = val;}
		void setMaxRange(float maxR) {m_maxValue = maxR;}

		void setOrientation(const Orientation& ori) {m_orientation = ori;}
	private:
		Material* m_backgroundMtl;
		Material* m_cursorMtl;

		Rectangle m_background;
		Rectangle m_cursorRectangle;

		float m_maxValue;
		float m_value = 0;

		Orientation m_orientation;
};

#endif
