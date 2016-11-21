#ifndef DEF_TRANSFORMABLE
#define DEF_TRANSFORMABLE

#define PI 3.14159 
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <cmath>
#include "logger.h"
#include "JniMadeOf.h"
#include "Rectangle3.h"

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

/** \brief define a default origin position.*/
enum PositionOrigin
{
	TOP_LEFT, TOP_CENTER, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM_CENTER,
	CENTER, CENTER_LEFT, CENTER_RIGHT
};

/** \brief Transformable is the class which manage all the transformation (rotations, translations, scales) of a matrix. It is mainly used for all the drawable and the Camera.
 * Firstly we apply the rotation, then the scale and after the rotation of the object.
 * The onScale, onRotate and onMove do nothing for this class. They are used if you want to do something during a transformation (without recreate move, scale or rotate function)*/
class Transformable : public JniMadeOf
{
	public:
		/** \brief create an unity matrix
		 * \param defaultConf the default size and position of this transformable */
		Transformable(const Rectangle3f& defaultConf=Rectangle3f(0, 0, 0, 0, 0, 0));

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

		/** \brief set the position origin of the transformable (another matrix which set the position of the position matrix)
		 * \param p the new position origin
		 * \param useScale Same as setPosition param*/
		virtual void setPositionOrigin(const glm::vec3 &p, bool useScale=false);

		/** \brief rotate the object
		 * \param angle the angle of the rotation in radian
		 * \param v the axis of the rotation
		 * \param origin the origin of the rotation */
		virtual void rotate(float angle, const glm::vec3 &v, const glm::vec3& origin=glm::vec3(0.0f), bool useScale=false);

		/** \brief Function called during a rotation
		 * \param angle the angle of the rotation in radian
		 * \param v the axis of the rotation
		 * \param origin the origin of the rotation */
		virtual void onRotate(float angle, const glm::vec3 &v, const glm::vec3& origin=glm::vec3(0.0f));

		/** \brief set the rotation of the object
		 * \param angle the angle of the new rotation in radian
		 * \param v the axis of the rotation
		 * \param origin the origin of the rotation */
		virtual void setRotate(float angle, const glm::vec3 &v, const glm::vec3& origin=glm::vec3(0.0f), bool useScale=false);

		/** \brief scale the object
		 * \param v values of the scale (x, y, z)
		 * \param keepPos Cancel the scale set position (true) or not (false)*/
		virtual void scale(const glm::vec3 &v, bool keepPos=true);

		/** \brief function called during a scaling
		 * \param v values of the scale (x, y, z)*/
		virtual void onScale(const glm::vec3 &v);

		/** \brief set the scale the object
		 * \param v values of the scale (x, y, z)
		 * \param keepPos Cancel the scale set position (true) or not (false)*/
		virtual void setScale(const glm::vec3 &v, bool keepPos=true);

		/** \brief set the coordinates of the object with spheric parameters
		 * \param r the radius from the origin to the position
		 * \param theta the angle between the vector (origin, position) and the plan (x, z). The zero is on the plan (y = 0)
		 * \param phi the angle between the plan (x, y) and the vector (origin, position). The zero is on the plan (x=0)*/
		virtual void setSphericCoordinate(float r, float theta, float phi);

		/** \brief set the applyTransformation. This variable is used if you want to transform he object only a few times with the same type of matrix
		 * \param transformable the new Transformable variable*/
		void setApplyTransformation(const Transformable* transformable);

		/** \brief move the object from a rotation in spherical coordinate by phi value
		 * \param phi the rotation of the object */
		virtual void rotatePhi(float phi);

		/** \brief move the object from a rotation in spherical coordinate by theta value
		 * \param theta the rotation of the object */
		virtual void rotateTheta(float theta);

		/** \brief return the position of the object
		 * \param useScale if set to true, the matrix position will be multiplied by the scale
		 * \return the position of the object, considering or not the object scale*/
		virtual glm::vec3 getPosition(bool useScale=true) const;

		/** \brief Get the origin position of this object
		 * \param useScale if set to true, the matrix position will be multiplied by the scale
		 * \return the position origin of this object*/
		virtual glm::vec3 getPositionOrigin(bool useScale=false) const;

		/** \brief return the size of the transformable with a scale at (1, 1, 1)
		 * \return the size by default of the object*/
		virtual const glm::vec3& getDefaultSize() const;

		/** \brief return the default position of this transformable
		 * \return the default position of the transformable*/
		virtual const glm::vec3& getDefaultPos() const;

		/** \brief get the default configuration of this transformable
		 * \return the default configuration*/
		virtual Rectangle3f getDefaultConf() const;

		/** \brief get the scale of the object
		 * \return value the scale value of the object of the x, y and z coordinates */
		virtual glm::vec3 getScale() const;

		/** \brief get the result matrix of all the transformations (applyTransformation, position, scale, rotation)
		 * \return the result matrix */
		virtual glm::mat4 getMatrix() const;

		/** \brief get the applyTransformation. This variable is used if you want to transform he object only a few times with the same type of matrix
		 * \return the apply transformation*/
		const Transformable* getApplyTransformation() const;

		/** \brief get the spheric coordinates of the object position
		 * \return the object spherical coordinates */
		virtual SphericCoord getSphericCoord() const;

		/** \brief get the distance between the origin (0, 0, 0) and the position of the object
		 * \return the radius of the object */
		virtual float getRadius() const;

		/** \brief get the euler rotation
		 * \return the euler rotation of the object */
		virtual EulerRotation getEulerRotation() const;

		/** \brief get the 3D rectangle on screen given its default configuration and the mvp applied
		 * \param mvp The mvp matrix applied to the Transformable*/
		Rectangle3f mvpToRect(const glm::mat4& mvp) const;

		/** \brief get the 3D rectangle of the transformable given its default position and default size
		 * \param m if you want to apply a transformation before getting the 3D rectangle coordinates*/
		Rectangle3f getRect(const glm::mat4& m=glm::mat4(1.0f)) const;

		/** \brief set the default configuration of the object : default position and default size
		 * \param dc the new defaultConf*/
		virtual void setDefaultConf(const Rectangle3f& dc);

		/** \brief add a position origin to the one defined by setPositionOrigin. Default : BOTTOM_LEFT 
		 * \param p the default origin position*/
		void setDefaultPositionOrigin(PositionOrigin p);

		PositionOrigin getDefaultPositionOrigin() const;


		/** \brief This function is used for setting the size of the transformable. Used for complicated Drawable that doesn't want to scale bruptely the object entirely.
		 * \param v the new size to apply. Basically, the size will be divised by the default size of the object. Remember that the Object is generally scaled. Use keepPos for keeping the transformable on the correct position*/
		virtual void setResquestSize(const glm::vec3& v, bool keepPos=true);
	protected:
		/** \brief create the new matrix result from the position, the scale and the rotation. */
		void setMVPMatrix();

		//These functions are privates because it is irelevant to the nature of the drawable, and not by the user wishes
		/** \brief set the default size of the object (the size when the scale is (1, 1, 1))
		 * \param s the new default size*/
		virtual void setDefaultSize(const glm::vec3& s);

		/** \brief set the default position of the object
		 * \param p the new default position*/
		virtual void setDefaultPos(const glm::vec3& p);

		glm::mat4 computeDefaultPositionOrigin();

		glm::mat4 m_mvpMatrix;
		glm::mat4 m_rotate;
		glm::mat4 m_scale;
		glm::mat4 m_position;
		glm::mat4 m_positionOrigin;
		Transformable const* m_applyTransformation;

		glm::vec3 m_defaultSize;
		glm::vec3 m_defaultPos;

		float     m_theta;
		float     m_phi;
		PositionOrigin m_defaultPosOrigin=BOTTOM_LEFT;
};

#endif
