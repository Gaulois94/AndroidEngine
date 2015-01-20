#ifndef DEF_INCLUDE_TRIANGLESHAPE
#define DEF_INCLUDE_TRIANGLESHAPE

#define GL_GLEXT_PROTOTYPES
#define GLM_FORCE_RADIANS

#include "Drawable.h"
#include "Color.h"
#include <vector>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TriangleShape : public Drawable
{
	public:
		//By default, colors is set to (0,0,0,0).
		//The uniColor will be the first Color from colors (or (0,0,0,0) if colors = NULL)
		TriangleShape(const glm::vec3* vertexCoord, int nbVertex, const Color* colors=NULL, bool uniColor=false, GLuint mode=GL_TRIANGLES);
		~TriangleShape();

		virtual void onDraw(Renderer* renderer);
		void setVertexCoord(const glm::vec3* vertexCoords);
		void setColors(const Color* colors);
		void setUniColor(const Color& color); //if you set the uniColor, don't forget to change 'useUniColor'
		void useUniColor(bool uniColor);

		bool isUsingUniColor();
		Color getUniColor();

		int getNbVertex();
		
		Color getColor(int vertex);
		glm::vec3 getPosition(int vertex);
	private:
		void initVbos(const float* vertexCoords, const float* colors);
		void setArrayVertex(const float* vertex);
		void setArrayColor(const float* colors);

		int    m_nbVertex;
		float* m_uniColor;
		bool   m_useUniColor;
		int    m_mode;
};

#endif
