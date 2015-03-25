#ifndef DEF_OBJMATERIAL_INCLUDE
#define DEF_OBJMATERIAL_INCLUDE

#define GLM_FORCE_RADIANS

#include "Texture.h"
#include "Rectangle2.h"
#include "Materials/Material.h"
#include "Color.h"

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <GLES2/gl2.h>

//Class material. The shader should contain all the variables used
class ObjMaterial : public Material
{
	public:
		ObjMaterial(const Color& diffuseColor, const Color& specularColor=Color::TRANSPARENT, const Texture* texture= NULL, bool useT=true, bool hlOn=false, bool aOn=true, bool cOn=true, float spHl=0.0f, float alpha=1.0);

		void setDiffuseColor(const Color& diffuseColor);
		void setSpecularColor(const Color& specularColor);

		Color getDiffuseColor() const;
		Color getSpecularColor() const;

		void init(Renderer* renderer, const glm::mat4& mvp);

		float transparent;
		float specularHighlight;
		bool  colorOn;
		bool  ambientOn;
		bool highlightOn;
/*		bool glassOn;
		bool FresnesOn;
		bool rayTraceOn;
		bool castShadowInvisibleSurface;*/
	private:
		float* m_diffuseColor;
		float* m_specularColor;
};

#endif
