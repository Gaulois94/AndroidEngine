#include "Transformable.h"

Transformable::Transformable(const Rectangle3f& defaultConf) : m_mvpMatrix(1.0f), m_rotate(1.0f), m_scale(1.0f), m_position(1.0f), m_positionOrigin(1.0f), m_applyTransformation(NULL), m_theta(0.0f), m_phi(0.0f)
{
	m_defaultPos = glm::vec3(defaultConf.x, defaultConf.y, defaultConf.z);
	m_defaultSize = glm::vec3(defaultConf.width, defaultConf.height, defaultConf.depth);
	m_rect = Rectangle3f(m_defaultPos, m_defaultSize);
}

void Transformable::move(const glm::vec3 &v, bool useScale)
{
	if(useScale == false)
		m_position = glm::translate(m_position, v/getScale());
	else
		m_position = glm::translate(m_position, v);
	setMVPMatrix();
	onMove(v, useScale);
}

void Transformable::onMove(const glm::vec3 &v, bool useScale)
{}

void Transformable::setPositionOrigin(const glm::vec3 &p, bool useScale)
{
	if(useScale == false)
		m_positionOrigin = glm::translate(glm::mat4(1.0f), -p/getScale());
	else
		m_positionOrigin = glm::translate(glm::mat4(1.0f), -p);
	setMVPMatrix();
}

void Transformable::setPosition(const glm::vec3 &v, bool useScale)
{
	if(useScale == false)
		move(v/getScale() - getPosition(useScale) + m_defaultPos, true);
	else
		move(v - getPosition(useScale) + m_defaultPos, true);
}

void Transformable::rotate(float angle, const glm::vec3 &v, const glm::vec3 &origin, bool useScale)
{
	glm::vec3 o = getPositionOrigin() + origin;
	if(useScale)
	{
		m_rotate = glm::translate(m_rotate, o);
		m_rotate = glm::rotate(m_rotate, angle, v);
		m_rotate = glm::translate(m_rotate, -o);
	}

	else
	{
		glm::vec3 s = getScale();
		m_rotate = glm::translate(m_rotate, o);
		m_rotate = glm::scale(m_rotate, glm::vec3(1.0f/s.x, 1.0f/s.y, 1.0f/s.z));
		m_rotate = glm::rotate(m_rotate, angle, v);
		m_rotate = glm::scale(m_rotate, s);
		m_rotate = glm::translate(m_rotate, -o);
	}
	setMVPMatrix();
	onRotate(angle, v, origin);
}

void Transformable::onRotate(float angle, const glm::vec3 &v, const glm::vec3 &origin)
{}

void Transformable::setRotate(float angle, const glm::vec3 &v, const glm::vec3 &origin, bool useScale)
{
	m_rotate = glm::mat4(1.0f);
	rotate(angle, v, origin);
}

void Transformable::scale(const glm::vec3 &v)
{
	m_scale = glm::scale(m_scale, v);
	setMVPMatrix();
	onScale(v);
}

void Transformable::onScale(const glm::vec3 &v)
{}

void Transformable::setScale(const glm::vec3 &v)
{
	m_scale = glm::mat4(1.0f);
	scale(v);
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

void Transformable::setApplyTransformation(const Transformable* transformable)
{
	m_applyTransformation = transformable;
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
	glm::vec3 v = glm::vec3(m_position[3][0], m_position[3][1], m_position[3][2]);
	v = v + m_defaultPos;
	if(useScale)
		v = v * getScale();
	return v;
}

glm::vec3 Transformable::getPositionOrigin(bool useScale) const
{
	glm::vec3 v = glm::vec3(-m_positionOrigin[3][0], -m_positionOrigin[3][1], -m_positionOrigin[3][2]);
	if(useScale)
		v = v * getScale();
	return v;
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
	if(m_applyTransformation)
		return (m_applyTransformation->getMatrix()) * m_mvpMatrix;
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

const Transformable* Transformable::getApplyTransformation() const
{
	return m_applyTransformation;
}

EulerRotation Transformable::getEulerRotation() const
{
	EulerRotation e;
	e.roll  = atan2(m_rotate[0][2], m_rotate[1][2]);
	e.pitch = acos(m_rotate[2][2]);
	e.yaw   = -atan2(m_rotate[2][0], m_rotate[2][1]);

	return e;
}

const Rectangle3f& Transformable::getRect() const
{
	return m_rect;
}

Rectangle3f Transformable::getRect(const glm::mat4& m) const
{
	/* Get the proper transformable matrix.*/
	glm::mat4 tMat = getMatrix();
	tMat = m * tMat;

	//Take the object 3D rect from its default configuration
	glm::vec4 v[8] = {
		glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec4(0.0, m_defaultSize[1], 0.0, 1.0), 
		glm::vec4(m_defaultSize[0], 0.0, 0.0, 1.0), glm::vec4(m_defaultSize[0], m_defaultSize[1], 0.0, 1.0), //Front face
		
		glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec4(0.0, m_defaultSize[1], 0.0, 1.0),
	   	glm::vec4(m_defaultSize[0], 0.0, 0.0, 1.0), glm::vec4(m_defaultSize[0], m_defaultSize[1], 0.0, 1.0)}; //Will be the back face


	//Get the back face position
	for(uint32_t i=4; i < 8; i++)
		v[i] = v[i] + glm::vec4(0.0, 0.0, m_defaultSize[2], 0.0);

	for(uint32_t i=0; i < 8; i++)
	{
		//Add the default position
		v[i] = v[i] + glm::vec4(m_defaultPos, 0.0);
		//Then Calculate the transformation to these vec
		v[i] = tMat * v[i];
	}
	
	//Determine the maximum and minimum coord of the v[i] table
	float xMin, yMin, zMin, xMax, zMax, yMax;
	for(uint32_t i=0; i < 8; i++)
	{
		if(i==0)
		{
			xMin = xMax = v[i][0];
			yMin = yMax = v[i][1];
			zMin = zMax = v[i][2];
			continue;
		}

		if(v[i][0] < xMin)
			xMin = v[i][0];
		else if(v[i][0] > xMax)
			xMax = v[i][0];

		if(v[i][1] < yMin)
			yMin = v[i][1];
		else if(v[i][1] > yMax)
			yMax = v[i][1];

		if(v[i][2] < zMin)
			zMin = v[i][2];
		else if(v[i][2] > zMax)
			zMax = v[i][2];
	}

	return Rectangle3f(xMin, yMin, zMin, xMax - xMin, yMax - yMin, zMax - zMin);
}

void Transformable::setMVPMatrix()
{	
    m_mvpMatrix = m_scale * (m_positionOrigin * m_position) * m_rotate;
	m_rect = getRect(glm::mat4(1.0f));
}
