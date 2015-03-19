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
		~Drawable();
		virtual void draw(Renderer* renderer);
		virtual void onDraw(Renderer* renderer, glm::mat4& mvp)=0;
		void staticToCamera(bool s);
		void setCanDraw(bool d);
		void setMaterial(Material* material);
		bool canDraw() const;
		const Material* getMaterial() const;
		bool isStaticToCamera() const;

	protected:
		virtual void deleteVbos();
		Material* m_material;
		GLuint m_vboID;
		bool m_canDraw;
		bool m_staticToCamera;
};

#endif
