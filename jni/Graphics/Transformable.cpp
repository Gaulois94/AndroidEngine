#include "Transformable.h"

Transformable::Transformable() : m_mvpMatrix(1.0f), m_rotate(1.0f), m_scale(1.0f), m_position(1.0f), m_theta(0.0f), m_phi(0.0f)
{
}

void Transformable::move(const glm::vec3 &v)
{
	m_position = glm::translate(m_position, v);
	setMVPMatrix();
}

void Transformable::setPosition(const glm::vec3 &v, bool useScale)
{
	if(useScale == false)
		m_position = glm::translate(glm::mat4(1.0f), v/getScale());
	else
		m_position = glm::translate(glm::mat4(1.0f), v);
	setMVPMatrix();
}

void Transformable::rotate(float angle, const glm::vec3 &v)
{
	m_rotate = glm::rotate(m_rotate, angle, v);
	setMVPMatrix();
}

void Transformable::setRotate(float angle, const glm::vec3 &v)
{
	m_rotate = glm::rotate(glm::mat4(1.0f), angle, v);
	setMVPMatrix();
}

void Transformable::scale(const glm::vec3 &v)
{
	m_scale = glm::scale(m_scale, v);
	setMVPMatrix();
}

void Transformable::setScale(const glm::vec3 &v)
{
	m_scale = glm::scale(glm::mat4(1.0f), v);
	setMVPMatrix();
}

void Transformable::setSphericCoordinate(float r, float theta, float phi)
{
	float x = r * sin(theta) * sin(phi);
	float y = r * cos(theta);
	float z = r * sin(theta) * cos(phi);

	m_theta = fmod(theta, PI);
	if(fmod(fmod(theta, PI), 2) < 2 * PI)
		m_phi = fmod(phi, (2*PI));
	else
		m_phi = -fmod(phi, (2*PI));

	setPosition(glm::vec3(x, y, z));
}

void Transformable::rotatePhi(float phi)
{
	setSphericCoordinate(getRadius(), m_theta, phi+m_phi);
}

void Transformable::rotateTheta(float theta)
{
	setSphericCoordinate(getRadius(), m_theta + theta, m_phi);
}

glm::vec3 Transformable::getScale() const
{
	return glm::vec3(m_scale[0][0], m_scale[1][1], m_scale[2][2]);
}

glm::vec3 Transformable::getPosition(bool useScale) const
{
	glm::vec3 v = glm::vec3(m_position[0][3], m_position[1][3], m_position[2][3]);
	if(!useScale)
		v = v/getScale();
	return v;
}

glm::mat4 Transformable::getMatrix() const
{
	return m_mvpMatrix;
}

SphericCoord Transformable::getSphericCoord() const
{
	SphericCoord s;
	s.r = getRadius();
	s.theta = m_theta;
	s.phi = m_phi;

	return s;
}

float Transformable::getRadius() const
{
	return getPosition().length();
}

EulerRotation Transformable::getEulerRotation() const
{
	EulerRotation e;
	e.roll  = atan2(m_rotate[2][0], m_rotate[2][1]);
	e.pitch = acos(m_rotate[2][2]);
	e.yaw   = -atan2(m_rotate[0][2], m_rotate[1][3]);

	return e;
}

void Transformable::setMVPMatrix()
{	m_mvpMatrix = m_scale * m_rotate;
	m_mvpMatrix = m_mvpMatrix * m_position;
}
