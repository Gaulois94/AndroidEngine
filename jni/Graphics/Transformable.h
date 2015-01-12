#ifndef DEF_TRANSFORMABLE
#define DEF_TRANSFORMABLE

#define PI 3.14159 
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <cmath>
#include "JniMadeOf.h"

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

class Transformable : JniMadeOf
{
	public:
		Transformable();

		virtual void move(const glm::vec3 &v);
		virtual void setPosition(const glm::vec3 &v);
		virtual void rotate(float angle, const glm::vec3 &v);
		virtual void setRotate(float angle, const glm::vec3 &v);
		virtual void scale(const glm::vec3 &v);
		virtual void setScale(const glm::vec3 &v);

		virtual void setSphericCoordinate(float r, float theta, float phi);
		virtual void rotatePhi(float phi);
		virtual void rotateTheta(float theta);

		glm::vec3 getPosition() const;
		glm::mat4 getMatrix() const;
		SphericCoord getSphericCoord() const;
		float getRadius() const;
		EulerRotation getEulerRotation() const;
	protected:
		void setMVPMatrix();

		glm::mat4 m_mvpMatrix;
		glm::mat4 m_rotate;
		glm::mat4 m_scale;
		glm::mat4 m_position;
		float     m_theta;
		float     m_phi;
};

#endif
