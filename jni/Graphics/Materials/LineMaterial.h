#ifndef  LINEMATERIAL_INC
#define  LINEMATERIAL_INC

#include "Materials/Material.h"

class LineMaterial : public Material
{
	public:
		LineMaterial(const Color& c = Color::WHITE, float t = 1.0f);
		virtual void init(Render& render, const glm::mat4& mvp);
		void setColor(const Color& color);
		void setThickness(float t);
	private:
		float m_thickness;
		float m_color[4];
};

#endif
