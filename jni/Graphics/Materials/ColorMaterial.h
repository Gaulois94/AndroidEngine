#ifndef DEF_COLORMATERIAL_INCLUDE
#define DEF_COLORMATERIAL_INCLUDE

#define GL_GLEXT_PROTOTYPES

#include "Texture.h"
#include "Color.h"
#include "Materials/Material.h"
#include "Renderer.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ColorMaterial : public Material
{
	public:
		ColorMaterial(const Color* color, int nbVertex);
		ColorMaterial(const float* color, int nbVertex);

		virtual void init(Renderer* renderer);

		void setColor(const Color* colors, int nbVertex);
		void setColor(const float* colors, int nbVertex);

		Color getColor(int vertex) const;
		Color* getColor() const;

		int getNbVertex() const;
	private:
		int m_nbVertex;
};

#endif
