#ifndef  CHANGEMVP_INC
#define  CHANGEMVP_INC

#include "Updatable.h"
#include "Transformable.h"

class ChangeMvp : public Updatable
{
	public:
		ChangeMvp(Updatable* parent, const Transformable& applyTrans, bool staticToCamera=false);
		void updateFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void moveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void updateTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));

		void staticToCamera(bool s);
	private:
		const Transformable& m_trans;
		bool m_staticToCamera;
};

#endif
