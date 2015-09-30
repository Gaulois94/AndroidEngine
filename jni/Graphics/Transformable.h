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

/** \brief contains the spheric coordinates */
struct SphericCoord
{
	float r;
	float theta;
	float phi;
};

/** \brief contains the euler coordinates */
struct EulerRotation
{
	float roll;
	float pitch;
	float yaw;
};

/** \brief Transformable is the class which manage all the transformation (rotations, translations, scales) of a matrix. It is mainly used for all the drawable and the Camera.
 * Firstly we apply the rotation, then the scale and after the rotation of the object.
 * The onScale, onRotate and onMove do nothing for this class. They are used if you want to do something during a transformation (without recreate move, scale or rotate function)*/
class Transformable : public Updatable
{
	public:
		/** \brief create an unity matrix */
		Transformable();

		/** \brief translate the transformable
		 * \param v the vector from where the object must be translated
		 * \param useScale tell if the move statement should take care of the actual scale
		 * */
		virtual void move(const glm::vec3 &v, bool useScale=false);

		/** \brief Function called during a translation
		 * \param v the vector or the translation
		 * \param useScale if the translation should take care of the scale*/
		virtual void onMove(const glm::vec3 &v, bool useScale=false);

		/** \brief Set the position of the object
		 * \param v the new position of the object
		 * \param useScale Because of the scale, the position of the object will be multiply by the object scale. That's why, if you don't want this effect, you must set this parameter to false for dividing the position and get the real one (considering the scale) */
		virtual void setPosition(const glm::vec3 &v, bool useScale=false);

		/** \brief rotate the object
		 * \param angle the angle of the rotation
		 * \param v the axis of the rotation
		 * \param origin the origin of the rotation */
		virtual void rotate(float angle, const glm::vec3 &v, const glm::vec3& origin=glm::vec3(0.0f));

		/** \brief Function called during a rotation
		 * \param angle the angle of the rotation
		 * \param v the axis of the rotation
		 * \param origin the origin of the rotation */
		virtual void onRotate(float angle, const glm::vec3 &v, const glm::vec3& origin=glm::vec3(0.0f));

		/** \brief set the rotation of the object
		 * \param angle the angle of the new rotation
		 * \param v the axis of the rotation
		 * \param origin the origin of the rotation */
		virtual void setRotate(float angle, const glm::vec3 &v, const glm::vec3& origin=glm::vec3(0.0f));

		/** \brief scale the object
		 * \param v values of the scale (x, y, z)*/
		virtual void scale(const glm::vec3 &v);

		/** \brief function called during a scaling
		 * \param v values of the scale (x, y, z)*/
		virtual void onScale(const glm::vec3 &v);

		/** \brief set the scale the object
		 * \param v values of the scale (x, y, z)*/
		virtual void setScale(const glm::vec3 &v);

		/** \brief set the coordinates of the object with spheric parameters
		 * \param r the radius from the origin to the position
		 * \param theta the angle between the vector (origin, position) and the plan (x, z). The zero is on the plan (y = 0)
		 * \param phi the angle between the plan (x, y) and the vector (origin, position). The zero is on the plan (x=0)*/
		virtual void setSphericCoordinate(float r, float theta, float phi);

		/** \brief move the object from a rotation in spherical coordinate by phi value
		 * \param phi the rotation of the object */
		virtual void rotatePhi(float phi);

		/** \brief move the object from a rotation in spherical coordinate by theta value
		 * \param theta the rotation of the object */
		virtual void rotateTheta(float theta);

		/** \brief return the position of the object
		 * \param useScale if set to false, the matrix position will be divided by the scale
		 * \return the position of the object, considering or not the object scale*/
		virtual glm::vec3 getPosition(bool useScale=false) const;

		/** \brief get the scale of the object
		 * \return value the scale value of the object of the x, y and z coordinates */
		virtual glm::vec3 getScale() const;

		/** \brief get the result matrix of all the transformation
		 * \return the result matrix */
		virtual glm::mat4 getMatrix() const;

		/** \brief get the spheric coordinates of the object position
		 * \return the object spherical coordinates */
		virtual SphericCoord getSphericCoord() const;

		/** \brief get the distance between the origin (0, 0, 0) and the position of the object
		 * \return the radius of the object */
		virtual float getRadius() const;

		/** \brief get the euler rotation
		 * \return the euler rotation of the object */
		virtual EulerRotation getEulerRotation() const;
	protected:
		/** \brief create the new matrix result from the position, the scale and the rotation. */
		void setMVPMatrix();

		glm::mat4 m_mvpMatrix;
		glm::mat4 m_rotate;
		glm::mat4 m_scale;
		glm::mat4 m_position;
		float     m_theta;
		float     m_phi;
};

#endif
