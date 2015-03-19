#ifndef DEF_MATERIALWRAPPER_INCLUDE
#define DEF_MATERIALWRAPPER_INCLUDE

#include "ResourcesManager.h"
#include "Materials/ObjMaterial.h"
#include "File.h"
#include "utils.h"
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class MaterialWrapper
{
	public:
		MaterialWrapper(File& file);
		~MaterialWrapper();

		ObjMaterial* getMaterial(const std::string& name);
	private:
		ResourcesManager<ObjMaterial*> m_mtl;
};

#endif
