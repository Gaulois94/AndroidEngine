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

class TriangleShape : public Drawable
{
	public:
		TriangleShape(Material* material, const glm::vec3* vertexCoords, const glm::vec3* normalCoords, int nbVertex, GLuint mode=GL_TRIANGLES);
		TriangleShape(Material* material, const float* vertexCoords, const float* normalCoords, int nbVertex, GLuint mode=GL_TRIANGLES);

		virtual void onDraw(Renderer* renderer, glm::mat4& mvp);
		void setDatas(const glm::vec3* vertexCoords, const glm::vec3* normalCoords, int nbVertex);
		void setDatas(const float* vertexCoords, const float* normalCoords, int nbVertex);

		void setDrawOrder(const unsigned int* drawOrder, int size);
		void setVertexCoord(const glm::vec3* vertexCoord);
		void setNormalCoord(const glm::vec3* normalCoord);

		int getNbVertex();
		glm::vec3 getPositionVertex(int vertex);
		void deleteDrawOrder();

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
