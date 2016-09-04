#ifndef DEF_MATERIAL_INCLUDE
#define DEF_MATERIAL_INCLUDE

#include <GLES2/gl2.h>
#include "Shader.h"
#include "Texture.h"
#include "Render.h"
#include "JniMadeOf.h"

/** \brief basic material class.*/
class Material : public JniMadeOf
{
	public:
		/** \brief Material contructor.
		 * \param shader this shader which the material will be bind on*/
		Material(const Shader *shader);

		~Material();

		/** \brief enable the shader then the material. Disable the material with disableShader after you have finish to draw your Drawable (or anything) associated with this material*/
		virtual void enableShader();

		/** \brief bind a texture with this material
		 * \param texture the Texture which will be bind with this material.*/
		void bindTexture(const Texture* texture);

		/** \brief init the material. This function is necessary for sending the good parameters at the shader
		 * \param render the render where this material will be used on
		 * \param mvp the transformation matrix associated with this call*/
		virtual void init(Render& render, const glm::mat4& mvp);

		/** \brief unbind the possible texture with this texture.*/
		void unbindTexture();

		/** \brief disable the shader thus the material (should be call after this material is used)*/
		virtual void disableShader();

		/** \brief get the shader used by this material
		 * \return the shader.*/
		const Shader* getShader() const;

		/** \brief delete the possible vbo used by this material.*/
		void deleteVbos();

		/** \brief set the opacity. Value inferior to 0 is understand as no opacity handler*/
		void setOpacity(float opac);
	protected:
		const Shader* m_shader;
		const Texture* m_texture;
		GLuint m_vboID;
		bool m_isUsingShader;
		static float maskColor[4];
		float m_opacity=-1.0f;
};

#endif
