#include "LateralCylinder.h"

LateralCylinder::LateralCylinder(Updatable* parent, Material* material, float radius, float height, int nbMeridian) : TriangleShape(parent, material, buffer=initVertex(radius, height, nbMeridian), NULL, 6*nbMeridian), m_nbMeridian(nbMeridian)
{
	free(buffer);
	buffer = initNormal(nbMeridian);
	setNormalCoord(buffer);
	free(buffer);
	buffer=NULL;
}

int LateralCylinder::getNbMeridian()
{
	return m_nbMeridian;
}

glm::vec3* LateralCylinder::initVertex(float radius, float height, int nbMeridian)
{
	glm::vec3* vertexCoord = (glm::vec3*)malloc(6*nbMeridian*sizeof(glm::vec3));
	for(int i=0; i < nbMeridian; i++)
	{
		double pos[] = {radius*cos(i*2*PI/nbMeridian), radius*sin(i*2*PI/nbMeridian), -height/2,
					    radius*cos((i+1)*2*PI/nbMeridian), radius*sin((i+1)*2*PI/nbMeridian), -height/2,
					    radius*cos((i+1)*2*PI/nbMeridian), radius*sin((i+1)*2*PI/nbMeridian), height/2,

					    radius*cos(i*2*PI/nbMeridian), radius*sin(i*2*PI/nbMeridian), -height/2,
					    radius*cos((i+1)*2*PI/nbMeridian), radius*sin((i+1)*2*PI/nbMeridian), height/2,
					    radius*cos(i*2*PI/nbMeridian), radius*sin(i*2*PI/nbMeridian), height/2
					   };

		for(int j=0; j < 18; j++)
			vertexCoord[6*i+j/3][j%3] = pos[j];
	}

	return vertexCoord;
}

glm::vec3* LateralCylinder::initNormal(int nbMeridian)
{
	glm::vec3* vertexCoord = (glm::vec3*)malloc(6*nbMeridian*sizeof(glm::vec3));
	for(int i=0; i < nbMeridian; i++)
	{

		double pos[] = {cos(i*2*PI/nbMeridian), sin(i*2*PI/nbMeridian), 0.0,
					    cos((i+1)*2*PI/nbMeridian), sin((i+1)*2*PI/nbMeridian), 0.0,
					    cos((i+1)*2*PI/nbMeridian), sin((i+1)*2*PI/nbMeridian), 0.0,

					    cos(i*2*PI/nbMeridian), sin(i*2*PI/nbMeridian), 0.0,
					    cos((i+1)*2*PI/nbMeridian), sin((i+1)*2*PI/nbMeridian), 0.0,
					    cos(i*2*PI/nbMeridian), sin(i*2*PI/nbMeridian), 0.0
					   };

		for(int j=0; j < 18; j++)
			vertexCoord[6*i+j/3][j%3] = pos[j];
	}

	return vertexCoord;
}
