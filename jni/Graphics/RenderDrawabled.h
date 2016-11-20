#ifndef  RENDERDRAWABLED_INC
#define  RENDERDRAWABLED_INC

#include "Sprite.h"
#include "RenderTexture.h"
#include "GroupDrawable.h"
#include "ChangeMvp.h"
#include "Rectangle3.h"

class RenderDrawabled : public Sprite
{
	public:
		RenderDrawabled(Updatable* parent, Material* mtl, const Vector2ui& pixelsSize);

		/** \brief get the render texture used for this drawable. The render texture can be modify integrally. 
		 * \return The RenderTexture used by the RenderDrawabled*/
		RenderTexture& getRenderTexture();

		/** \brief get the Updatable which set the focus value, apply algorithm to pass from the Sprite to a sub render. Use this function to access to the child tree and draw IN the render texture.
		 * \return the Updatable useful for the child tree.*/
		Updatable& getChangeMvp();

		void staticToCamera(bool s);
		Rectangle3f getGlobalRect() const;
	private:
		ChangeMvp m_changeMvp;
		RenderTexture m_render;
		Transformable m_trans;
};

#endif
