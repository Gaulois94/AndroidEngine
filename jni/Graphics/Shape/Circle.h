#ifndef DEF_CIRCLE_INCLUDE
#define DEF_CIRCLE_INCLUDE

#include <cmath>
#include "Shape/TriangleShape.h"
#include "Materials/Material.h"

/** \brief the Circle class. Used to create circles from triangles (it can be used to create all regular polygons too : a circle is just a regular polygons with infinity number of edges)*/
class Circle : public TriangleShape
{
	public:
		/** \brief The Circle constructor
		 * \param parent its parent
		 * \param material the material of the circle
		 * \param radius the radius of the circle. Set the scale for setting the futur radius or setNbEdge with the same number of edge than before.
		 * \param nbEdge the number of *edge* of this circle. My be superior than 3. This number can be used to create any regular polygons from 3 to infinity number of edges*/
		Circle(Updatable* parent, Material* material, float radius=1, uint32_t nbEdge=16); //size must be superior than 3. By default, radius is set to 1.0f. Set scale for setting radius.

		/** \brief set the number of edges of this circle. Can be call 'reconfigure' too
		 * \param nbEdge the new number of edges
		 * \param radius the new radius.*/
		void setNbEdge(uint32_t nbEdge, float radius=1);

		/** \brief get the number of edges of this circle
		 * \return the number of edges*/
		int getNbEdge() const;

		/** \brief get the center of this circle from its transformation matrix
		 * \return the center of this circle.*/
		glm::vec3 getCenter() const;
	private:
		static glm::vec3* initVertex(float radius, int nbEdge);
		float m_radius;
		int m_nbEdge;
		glm::vec3* buffer;
};
#endif
