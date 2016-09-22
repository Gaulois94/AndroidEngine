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

/** \brief ObjMaterial is a class for containing all the obj type material characteristic*/
class ObjMaterial : public Material
{
	public:
		/** \brief the ObjMaterial constructor.
		 * \param diffuseColor the diffuse color
		 * \param specularColor the specular color
		 * \param texture the material has a texture, tell it.
		 * \param useT use the transparence
		 * \param hlOn highligh on
		 * \param aOn ambient color on
		 * \param cOn color  on
		 * \param spHl specular Highlight
		 * \param alpha the transparence of the object*/
		ObjMaterial(const Color& diffuseColor, const Color& specularColor=Color::TRANSPARENT, const Texture* texture= NULL, bool useT=true, bool hlOn=false, bool aOn=true, bool cOn=true, float spHl=0.0f, float alpha=1.0);

		/** \brief set the diffuse color of this material
		 * \param diffuseColor the new diffuse color */
		void setDiffuseColor(const Color& diffuseColor);

		/** \brief set the specular color of this material
		 * \param specularColor the new specular color*/
		void setSpecularColor(const Color& specularColor);

		/** \brief get the diffuse color of this material
		 * \return the diffuse color*/
		Color getDiffuseColor() const;

		/** \brief get the specular color of this material
		 * \return the specular color*/
		Color getSpecularColor() const;

		void init(Render& render, const glm::mat4& mvp, const glm::mat4& modelMatrix);

		float transparent; /** <the transparence of the material*/
		float specularHighlight;/** <the value of the specular highlight*/
		bool  colorOn; /** <If the color is on*/
		bool  ambientOn;/** <If the ambient color is on*/
		bool highlightOn;/** <If the highlight is on */
/*		bool glassOn;
		bool FresnesOn;
		bool rayTraceOn;
		bool castShadowInvisibleSurface;*/
	private:
		float* m_diffuseColor;
		float* m_specularColor;
};

#endif
