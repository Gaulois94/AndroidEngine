#ifndef DRAWABLE_INCLUDE
#define DRAWABLE_INCLUDE

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "Transformable.h"
#include "Shader.h"
#include "Renderer.h"
#include "Materials/Material.h"
#include <GLES2/gl2.h>

class Drawable : public Transformable
{
	public:
		Drawable(Material* material);
		virtual ~Drawable();
		//Transformation is applied BEFORE the camera and the Transformation (from Transformable class) of the Drawable.
		virtual void draw(Renderer* renderer, const glm::mat4& transformation=glm::mat4(1.0));
		virtual void onDraw(Renderer* renderer, glm::mat4& mvp)=0;
		virtual void staticToCamera(bool s);
		virtual void setCanDraw(bool d);
		virtual void setMaterial(Material* material);
		virtual bool canDraw() const;
		virtual const Material* getMaterial() const;
		virtual bool isStaticToCamera() const;
	protected:
		virtual void deleteVbos();
		Material* m_material;
		GLuint m_vboID;
		bool m_canDraw;
		bool m_staticToCamera;
};

#endif
