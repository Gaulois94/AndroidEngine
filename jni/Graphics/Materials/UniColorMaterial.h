#ifndef DEF_UNIMATERIAL_INCLUDE
#define DEF_UNIMATERIAL_INCLUDE

#include "Color.h"
#include "Materials/Material.h"

class UniColorMaterial : public Material
{
	public:
		UniColorMaterial(const Color& color);
		UniColorMaterial(const float* color);

		~UniColorMaterial();

		virtual void init(Renderer* renderer);
		void setColor(const Color& color);
		void setColor(const float* color);
		Color getColor() const;
	private:
		float* m_color;
};

#endif
