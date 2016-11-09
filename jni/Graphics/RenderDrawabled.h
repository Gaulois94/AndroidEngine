#ifndef  RENDERDRAWABLED_INC
#define  RENDERDRAWABLED_INC

#include "Sprite.h"
#include "RenderTexture.h"
#include "GroupDrawable.h"

class RenderDrawabled : public Updatable
{
	public:
		RenderDrawabled(Updatable* parent, Material* mtl, const Vector2f& pixelsSize);

		void setMaterial(Material* mtl);

		/** \brief get the render texture used for this drawable. The render texture can be modify integrally, use this function to access to the child tree and draw IN the render texture.
		 * \return The RenderTexture used by the RenderDrawabled*/
		RenderTexture& getRenderTexture();

		Sprite& getSprite();
	protected:

		class RenderSprite : public Sprite
		{
			public:
				RenderSprite(Updatable* parent, Material* mtl, RenderTexture& render);
				virtual void updateFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
				void moveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp = glm::mat4(1.0f));
				RenderTexture& m_render;
		};

		RenderTexture m_render;
		RenderDrawabled::RenderSprite  m_sprite;

};

#endif
