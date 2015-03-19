#include "Shape/Sphere.h"

Sphere::Sphere(Material* material, unsigned int nbLongitude, unsigned int nbLatitude) : TriangleShape::TriangleShape(material, buffer=initVertex(nbLongitude, nbLatitude), NULL, nbLongitude*nbLatitude), m_nbLongitude(nbLongitude), m_nbLatitude(nbLatitude)
{
	setNormalCoord(buffer); //The position and the normal of vertex are the same
	free(buffer);

	unsigned int* b=initOrder(nbLongitude, nbLatitude);
	setDrawOrder(b, nbLongitude*(nbLatitude-1)*6);
	free(b);
}

glm::vec3* Sphere::initVertex(unsigned int nbLongitude, unsigned int nbLatitude)
{
	glm::vec3* vertexCoord = (glm::vec3*)malloc(nbLongitude*nbLatitude*sizeof(glm::vec3));
	for(unsigned int i=0; i < nbLongitude; i++)
	{
		double theta = 2*PI/(nbLongitude) * i;
		for(unsigned int j=0; j < nbLatitude; j++)
		{
			double phi = PI/(nbLatitude-1) * j;
			double pos[] = {sin(phi)*cos(theta), cos(phi), sin(theta)*sin(phi)};
			for(unsigned int k=0; k < 3; k++)
				vertexCoord[i*nbLatitude + j][k] = pos[k];
		}
	}

	return vertexCoord;
}

unsigned int* Sphere::initOrder(unsigned int nbLongitude, unsigned int nbLatitude)
{
	unsigned int* order = (unsigned int*)malloc(nbLongitude*(nbLatitude-1)*sizeof(unsigned int)*6);
	for(unsigned int i=0; i < nbLongitude; i++)
	{
		for(unsigned int j=0; j < nbLatitude-1; j++)
		{
			unsigned int o[] = {nbLatitude*i, nbLatitude*i+1, nbLatitude*(i+1)+1,
						        nbLatitude*i, nbLatitude*(i+1)+1, nbLatitude*(i+1)
			};

			for(unsigned int k=0; k < 6; k++)
				order[(nbLatitude-1)*i*6 + j*6 + k] = o[k];
		}
	}

	return order;
}
