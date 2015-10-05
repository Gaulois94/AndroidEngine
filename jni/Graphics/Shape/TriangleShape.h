#ifndef DEF_INCLUDE_TRIANGLESHAPE
#define DEF_INCLUDE_TRIANGLESHAPE

#define GL_GLEXT_PROTOTYPES
#define GLM_FORCE_RADIANS

#define COORD_PER_TRIANGLES 3

#include "Drawable.h"
#include "Color.h"
#include "Materials/Material.h"
#include "Texture.h"
#include <vector>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/** \brief TriangleShape class. It is the class which contains all the informations about the vertex of the shape and their normal.*/
class TriangleShape : public Drawable
{
	public:
		/** \brief Create the TriangleShape object with glm::vec3 coords
		 * \param material its material
		 * \param vertexCoords the coordinates of the vertex
		 * \param normalCoords the normal value of the vertex.
		 * \param nbVertex the number of vertex
		 * \param mode the mode used by the vertex. See the mode accorded by OpenGL. By default its GL_TRIANGLES*/
		TriangleShape(Updatable* parent, Material* material, const glm::vec3* vertexCoords, const glm::vec3* normalCoords, int nbVertex, GLuint mode=GL_TRIANGLES);

		/** \brief Create the TriangleShape object from float array
		 * \param parent its parent
		 * \param material its material
		 * \param vertexCoords the coordinates of the vertex. 1 value per component (3 components per vertex : x, y, z)
		 * \param normalCoords the normal value of the vertex. 1 value per component (3 components per vertex : x, y, z)
		 * \param nbVertex the number of vertex
		 * \param mode the mode used by the vertex. See the mode accorded by OpenGL. By default its GL_TRIANGLES*/
		TriangleShape(Updatable* parent, Material* material, const float* vertexCoords, const float* normalCoords, int nbVertex, GLuint mode=GL_TRIANGLES);

		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));

		/** \brief set the datas of this triangle shape : its vertex coords, normal values. glm::vec3 version
		 * \param vertexCoords the coordinates of the vertex
		 * \param normalCoords the normal value of the vertex.
		 * \param nbVertex the number of vertex*/
		void setDatas(const glm::vec3* vertexCoords, const glm::vec3* normalCoords, int nbVertex);

		/** \brief set the datas of this triangle shape : its vertex coords, normal values. glm::vec3 version
		 * \param vertexCoords the coordinates of the vertex. 1 value per component (3 components per vertex : x, y, z)
		 * \param normalCoords the normal value of the vertex. 1 value per component (3 components per vertex : x, y, z)
		 * \param nbVertex the number of vertex*/
		void setDatas(const float* vertexCoords, const float* normalCoords, int nbVertex);

		/** \brief set an order for sending the vertex to opengl. for example for a square, you need only 4 vertex and draw 2 triangles (then 6 vertex with GL_TRIANGLES mode)
		 * \param drawOrder an array of the order
		 * \param size its size*/
		void setDrawOrder(const unsigned int* drawOrder, int size);

		/** \brief set the vertex coordinates
		 * \param vertexCoord the new vertex coordinates*/
		void setVertexCoord(const glm::vec3* vertexCoord);

		/** \brief set the normal coordinates
		 * \param vertexCoord the new normal coordinates*/
		void setNormalCoord(const glm::vec3* normalCoord);

		/** \brief get the number of vertex used by this TriangleShape
		 * \return the number of vertex*/
		int getNbVertex();

		/** \brief get the value of the vertex coordinates
		 * \param vertex the indice of the vertex
		 * \return the vertex coordinates*/
		glm::vec3 getPositionVertex(int vertex);

		/** \brief don't use the draw order*/
		void deleteDrawOrder();

		/** \brief tell if the draw order is used
		 * \return draw order used or not*/
		bool useDrawOrder();
	protected:
		void initVbos(const float* vertexCoords, const float* normalCoords);
		void deleteVbos();
		void setArrayVertex(const float* vertex);
		void setArrayNormal(const float* normal);

		int      m_nbVertex;
		int      m_mode;
		GLuint   m_drawOrderVboID;
		int      m_drawOrderLength;
};

float*     makeNormalCoords(const glm::vec3* vertexCoords, int nbVertex);
float*     makeNormalCoords(const float* vertexCoords, int nbVertex);
glm::vec3* convertFloatToGlm3(const float* vertexCoords, int nbVertex);
float* convertGlm3ToFloat(const glm::vec3* vertexCoords, int nbVertex);

#endif
