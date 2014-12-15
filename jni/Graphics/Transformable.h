#ifndef DEF_TRANSFORMABLE
#define DEF_TRANSFORMABLE

#define PI 3.14159 
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <cmath>

struct SphericCoord
{
	float r;
	float theta;
	float phi;
};

struct EulerRotation
{
	float roll;
	float pitch;
	float yaw;
};

class Transformable
{
	public:
		Transformable();

		void move(const glm::vec3 &v);
		void setPosition(const glm::vec3 &v);
		void rotate(float angle, const glm::vec3 &v);
		void setRotate(float angle, const glm::vec3 &v);
		void scale(const glm::vec3 &v);
		void setScale(const glm::vec3 &v);

		void setSphericCoordinate(float r, float theta, float phi);
		void rotatePhi(float phi);
		void rotateTheta(float theta);

		glm::vec3 getPosition();
		glm::mat4 getMatrix();
		SphericCoord getSphericCoord();
		float getRadius();
		EulerRotation getEulerRotation();
	private:
		void setMVPMatrix();

		glm::mat4 m_mvpMatrix;
		glm::mat4 m_rotate;
		glm::mat4 m_scale;
		glm::mat4 m_position;
		float     m_theta;
		float     m_phi;
};

#endif
