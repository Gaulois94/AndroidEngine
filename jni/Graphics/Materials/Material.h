#ifndef DEF_MATERIAL_INCLUDE
#define DEF_MATERIAL_INCLUDE

#include <GLES2/gl2.h>
#include <glm/gtc/type_ptr.hpp>
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
		 * \param mvp the transformation matrix associated with this call
		 * \param mvp the transformation matrix for the object itself*/
		virtual void init(Render& render, const glm::mat4& mvp, const glm::mat4& modelMatrix);

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

		/** \brief set the local clipping of the material. The local clipping is a clipping based on the model coordinates system
		 * \param clip the new local clipping */
		void setClipping(const Rectangle2f& clip);

		/** \brief enable the local clipping.
		 * \param enable If the local clipping should be taking in account */
		void enableClipping(bool enable);

		bool getEnableClipping() const {return m_enableClipping;}

		const Rectangle2f& getClipping() const {return m_clip;}

		/** \brief set the global clipping. Global clipping is the clipping based on the view coordinates (screen coordinates)
		 * \param clip The new global clipping*/
		static void setGlobalClipping(const Rectangle2f& clip);

		/** \brief enable the global clipping.
		 * \param enable If the global clipping should be taking in account */
		static void enableGlobalClipping(bool enable);

		/** \brief get the global clipping
		 * \return the global clipping*/
		static const Rectangle2f& getGlobalClipping();

		/** \brief get whether or not the global clipping is enabled
		 * \return the local clipping*/
		static bool getGlobalEnableClipping();
	protected:
		virtual void getAttributs();
		const Shader* m_shader;
		const Texture* m_texture;
		GLuint m_vboID;
		bool m_isUsingShader;
		static float maskColor[4];
		float m_opacity=-1.0f;

		bool m_enableClipping = false;
		Rectangle2f m_clip;

		static Rectangle2f globalClipping;
		static bool globalEnableClipping;

		//Shader attributs
		GLint m_uMaskColor;
		GLint m_uUseTexture;
		GLint m_uTextureHandle;
		GLint m_uOpacityHandle;
		GLint m_uModelMatrix;
		GLint m_uLocalClippingClip;
		GLint m_uGlobalClippingClip;
		GLint m_uLocalClippingX;
		GLint m_uLocalClippingY;
		GLint m_uLocalClippingWidth;
		GLint m_uLocalClippingHeight;

		GLint m_uGlobalClippingX;
		GLint m_uGlobalClippingY;
		GLint m_uGlobalClippingWidth;
		GLint m_uGlobalClippingHeight;
};

#endif
