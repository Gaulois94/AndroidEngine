#ifndef DEF_TRANSFORMABLE
#define DEF_TRANSFORMABLE

#define PI 3.14159 
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include "logger.h"
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
		virtual void setPosition(const glm::vec3 &v, bool useScale=false);
		virtual void rotate(float angle, const glm::vec3 &v);
		virtual void setRotate(float angle, const glm::vec3 &v);
		virtual void scale(const glm::vec3 &v);
		virtual void setScale(const glm::vec3 &v);

		virtual void setSphericCoordinate(float r, float theta, float phi);
		virtual void rotatePhi(float phi);
		virtual void rotateTheta(float theta);

		virtual glm::vec3 getPosition(bool useScale=false) const;
		virtual glm::vec3 getScale() const;
		virtual glm::mat4 getMatrix() const;
		virtual SphericCoord getSphericCoord() const;
		virtual float getRadius() const;
		virtual EulerRotation getEulerRotation() const;
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
