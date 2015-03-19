#ifndef DEF_MATERIAL_INCLUDE
#define DEF_MATERIAL_INCLUDE

#include <GLES2/gl2.h>
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "JniMadeOf.h"

class Material : public JniMadeOf
{
	public:
		Material(const Shader *shader);
		~Material();
		void enableShader();
		void bindTexture(const Texture* texture);
		virtual void init(Renderer* renderer);
		void unbindTexture();
		void disableShader();
		const Shader* getShader() const;
		void deleteVbos();
	protected:
		const Shader* m_shader;
		const Texture* m_texture;
		GLuint m_vboID;
		bool m_isUsingShader;
};

#endif
