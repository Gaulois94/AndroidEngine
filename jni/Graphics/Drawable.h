#ifndef DRAWABLE_INCLUDE
#define DRAWABLE_INCLUDE

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "Transformable.h"
#include "Shader.h"
#include "Renderer.h"
#include "ResourcesManager.h"
#include <GLES2/gl2.h>

class Drawable : public Transformable
{
	public:
		Drawable(Shader* shader);
		virtual void draw(Renderer* renderer);
		virtual void onDraw(Renderer* renderer)=0;
		bool canDraw() const;

		static ResourcesManager<Shader*> shaders; 
	protected:
		virtual void initVbos()=0;
		void deleteVbos();
		Shader* m_shader;
		GLuint m_vboID;
		bool m_canDraw;
};

#endif
