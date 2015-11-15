#ifndef DEF_COLORMATERIAL_INCLUDE
#define DEF_COLORMATERIAL_INCLUDE

#define GL_GLEXT_PROTOTYPES

#include "Texture.h"
#include "Color.h"
#include "Materials/Material.h"
#include "Render.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/** \brief ColorMaterial class. This material is used to set the color of an object for each call of the fragment shader (for example each point of a TriangleShape object)*/
class ColorMaterial : public Material
{
	public:
		/** \brief Constuctor associated with a Color array.
		 * \param color the array of color. One value per vertex
		 * \param nbVertex the size of the array*/
		ColorMaterial(const Color* color, int nbVertex);

		/** \brief Constuctor associated with a color components value (r, g, b) array.
		 * \param color the array of color. One value per component per vertex.
		 * \param nbVertex how many vertex this color array contain.*/
		ColorMaterial(const float* color, int nbVertex);

		virtual void init(Render& render, const glm::mat4& mvp);
		virtual void disableShader();

		/** \brief set the color of all the vertices
		 * \param color the array of color. One value per vertex
		 * \param nbVertex the size of the array*/

		void setColor(const Color* colors, int nbVertex);
		/** \brief set the color of all the vertices
		 * \param color the array of color. One value per component per vertex.
		 * \param nbVertex how many vertex this color array contain.*/
		void setColor(const float* colors, int nbVertex);

		/** \brief get the color of one particular vertice.
		 * \param vertex the vertice
		 * \return the color of this vertex*/
		Color getColor(int vertex) const;

		/** \brief get all the color contained by this material
		 * \return the array of this material. Should be deleted after use !*/
		Color* getColor() const;

		/** \brief get the number of vertex this material can handle
		 * \return the number of vertex*/
		int getNbVertex() const;
	private:
		int m_nbVertex;
};

#endif
