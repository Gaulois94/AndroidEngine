#ifndef DEF_LIGHTMANAGER_INCLUDE
#define DEF_LIGHTMANAGER_INCLUDE

#include <vector>
#include "Light.h"

class LightManager
{
	public:
		LightManager();
		void addLight(const Light* light);
	private:
		float* m_ambienColor;
};

#endif
