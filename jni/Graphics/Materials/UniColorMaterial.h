#ifndef DEF_UNIMATERIAL_INCLUDE
#define DEF_UNIMATERIAL_INCLUDE

#include "Color.h"
#include "Materials/Material.h"

/** \brief UniColorMaterial is a material for all objects which need to be colored by an unique color.*/
class UniColorMaterial : public Material
{
	public:
		/** \brief Constructor associated with a Color object
		 * \param color the color associated with this material.*/
		UniColorMaterial(const Color& color);

		/** \brief Constructor associated with a color component array
		 * \param color the color associated with this material. The 3 first values must contain (r, g, b) component.*/
		UniColorMaterial(const float* color);

		~UniColorMaterial();

		virtual void init(Render& render, const glm::mat4& mvp, const glm::mat4& modelMatrix);
		virtual void disableShader();

		/** \brief Set the alpha component of the color
		 * \param alpha the new value for the alpha component*/
		void setAlpha(float alpha) {m_color[3] = alpha;}

		/** \brief set the color of this material
		 * \param color the new color*/
		void setColor(const Color& color);

		/** \brief set the color of this material
		 * \param color the (r, g, b) new color array*/
		void setColor(const float* color);

		/** \brief get the color used by this material
		 * \return the material color.*/
		Color getColor() const;

		/** \brief get the alpha component value
		 * \return the alpha component value*/
		float getAlpha() const{return m_color[3];}
	private:
		float* m_color;
};

#endif
