#include "Transformable.h"

Transformable::Transformable(const Rectangle3f& defaultConf) : m_mvpMatrix(1.0f), m_rotate(1.0f), m_scale(1.0f), m_position(1.0f), m_theta(0.0f), m_phi(0.0f)
{
	m_defaultPos = glm::vec3(defaultConf.x, defaultConf.y, defaultConf.z);
	m_defaultSize = glm::vec3(defaultConf.width, defaultConf.height, defaultConf.depth);
}

void Transformable::move(const glm::vec3 &v, bool useScale)
{
	if(useScale == false)
		m_position = glm::translate(m_position, v/getScale());
	else
		m_position = glm::translate(m_position, v);
	onMove(v, useScale);
	setMVPMatrix();
}

void Transformable::onMove(const glm::vec3 &v, bool useScale)
{}

void Transformable::setPosition(const glm::vec3 &v, bool useScale)
{
	if(useScale == false)
		move(getPosition(useScale) - v/getScale());
	else
		move(getPosition(useScale) - v);
}

void Transformable::rotate(float angle, const glm::vec3 &v, const glm::vec3 &origin)
{
	glm::vec3 moveOut = getPosition() - origin;
	m_rotate = glm::translate(m_rotate, moveOut);
	m_rotate = glm::rotate(m_rotate, angle, v);
	m_rotate = glm::translate(m_rotate, -moveOut);
	onRotate(angle, v, origin);
	setMVPMatrix();
}

void Transformable::onRotate(float angle, const glm::vec3 &v, const glm::vec3 &origin)
{}

void Transformable::setRotate(float angle, const glm::vec3 &v, const glm::vec3 &origin)
{
	m_rotate = glm::mat4(1.0f);
	rotate(angle, v, origin);
}

void Transformable::scale(const glm::vec3 &v)
{
	m_scale = glm::scale(m_scale, v);
	onScale(v);
	setMVPMatrix();
}

void Transformable::onScale(const glm::vec3 &v)
{}

void Transformable::setScale(const glm::vec3 &v)
{
	scale(getScale()/v);
}

void Transformable::setDefaultPos(const glm::vec3 &p)
{
	m_defaultPos = p;
}

void Transformable::setDefaultSize(const glm::vec3 &s)
{
	m_defaultSize = s;
}

void Transformable::setDefaultConf(const Rectangle3f &dc)
{
	setDefaultPos(glm::vec3(dc.x, dc.y, dc.z));
	setDefaultSize(glm::vec3(dc.width, dc.height, dc.depth));
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
	if(useScale)
	{
		glm::vec3 v = glm::vec3(m_mvpMatrix[3][0], m_mvpMatrix[3][1], m_mvpMatrix[3][2]);
		return v+m_defaultPos;
	}
	glm::vec3 v = glm::vec3(m_position[3][0], m_position[3][1], m_position[3][2]);
	return v+m_defaultPos;
}

const glm::vec3& Transformable::getDefaultPos() const
{
	return m_defaultPos;
}

const glm::vec3& Transformable::getDefaultSize() const
{
	return m_defaultSize;
}

Rectangle3f Transformable::getDefaultConf() const
{
	return Rectangle3f(m_defaultPos, m_defaultSize);
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
	e.roll  = atan2(m_rotate[0][2], m_rotate[1][2]);
	e.pitch = acos(m_rotate[2][2]);
	e.yaw   = -atan2(m_rotate[2][0], m_rotate[2][1]);

	return e;
}

void Transformable::setMVPMatrix()
{	
	m_mvpMatrix = m_scale * m_position;
	m_mvpMatrix = m_mvpMatrix * m_rotate;
}
