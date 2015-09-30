#include "Shape/Sphere.h"

Sphere::Sphere(Updatable* parent, Material* material, float radius, unsigned int nbLongitude, unsigned int nbLatitude) : TriangleShape(parent, material, buffer=initVertex(radius, nbLongitude, nbLatitude), NULL, nbLongitude*nbLatitude), m_nbLongitude(nbLongitude), m_nbLatitude(nbLatitude)
{
	//Normalize normales
	for(unsigned int i=0; i < nbLongitude*nbLatitude; i++)
		for(unsigned int j=0; j < 3; j++)
			buffer[i][j] /= radius;
	setNormalCoord(buffer); //The position and the normal of vertex are the same
	free(buffer);

	unsigned int* b=initOrder(nbLongitude, nbLatitude);
	setDrawOrder(b, nbLongitude*(nbLatitude-1)*6);
	free(b);
}

glm::vec3* Sphere::initVertex(float radius, unsigned int nbLongitude, unsigned int nbLatitude)
{
	glm::vec3* vertexCoord = (glm::vec3*)malloc(nbLongitude*nbLatitude*sizeof(glm::vec3));
	for(unsigned int i=0; i < nbLongitude; i++)
	{
		double theta = 2*PI/nbLongitude * i;
		for(unsigned int j=0; j < nbLatitude; j++)
		{
			double phi = PI/(nbLatitude-1) * j;
			double pos[] = {radius* sin(phi)*sin(theta), radius*cos(phi), radius*cos(theta)*sin(phi)};
			for(unsigned int k=0; k < 3; k++)
				vertexCoord[i*nbLatitude + j][k] = pos[k];
		}
	}

	return vertexCoord;
}

unsigned int* Sphere::initOrder(unsigned int nbLongitude, unsigned int nbLatitude)
{
	unsigned int* order = (unsigned int*)malloc(nbLongitude*(nbLatitude)*sizeof(unsigned int)*6);
	for(unsigned int i=0; i < nbLongitude; i++)
	{
		for(unsigned int j=0; j < nbLatitude-1; j++)
		{
			unsigned int o[] = {i*(nbLatitude) + j, (i+1)*(nbLatitude) + j+1, (i+1)*(nbLatitude)+j,
								i*(nbLatitude) + j, i*(nbLatitude) + j+1, (i+1)*(nbLatitude) + j+1
						        
			};

			for(unsigned int k=0; k < 6; k++)
				order[(nbLatitude-1)*i*6 + j*6 + k] = o[k]%(nbLongitude*nbLatitude);
		}
	}

	return order;
}
