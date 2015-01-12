#ifndef DEF_CAMERA_INCLUDE
#define DEF_CAMERA_INCLUDE

#include "Transformable.h"
#define GLM_FORCE_RADIANS

class Camera : public Transformable
{
	public:
		Camera();
		glm::vec3 getLateral() const;
		void lookAt(const glm::vec3& camera, const glm::vec3& target);
		virtual glm::vec3 getPosition() const;
		virtual void setPosition(const glm::vec3& pos);
		void setOrientation(const glm::vec3& orientation);
};

#endif
