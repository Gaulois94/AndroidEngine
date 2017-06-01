#ifndef DEF_CAMERA_INCLUDE
#define DEF_CAMERA_INCLUDE

#include "Transformable.h"
#define GLM_FORCE_RADIANS

/** \brief Camera class.
 * Use to create a camera matrix from which opengl will transform object coordinates. */
class Camera : public Transformable
{
	public:
		/** \brief Create a basic camera, which modifies nothing (unity matrix) 
		 * \param defaultPos the position of the Camera*/
		Camera(const glm::vec3& defaultPos=glm::vec3(0.0f));

		/** \brief Set the camera position and configure the orientation for looking at the target
		 * \param camera the camera position 
		 * \param target the target position*/
		void lookAt(const glm::vec3& camera, const glm::vec3& target);

		/** \brief Get the camera position
		 * \return the camera position */
		virtual glm::vec3 getPosition(bool useScale=true) const;

		virtual void setPosition(const glm::vec3& m, bool useScale=false);

		/** \brief Set the camera position
		 * \param pos the camera position
		 * \param useScale the camera position is multiply by the scale. You can set this parameter to false for nullify the effect of the scale*/
		virtual void move(const glm::vec3& pos, bool useScale=false);

		/** \brief Set the camera orientation
		 * \param orientation The x, y and z angle orientation */
		void setOrientation(const glm::vec3& orientation);
};

#endif
