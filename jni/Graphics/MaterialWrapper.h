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

/** \brief Create a list of material from a material file.*/
class MaterialWrapper
{
	public:
		/** \brief Create all the material contained on the file.
		 * \param file The file where materials are serialized*/
		MaterialWrapper(File& file);
		~MaterialWrapper();

		/** \brief get the material stored in the list.
		 * \param name the material key name
		 * \return the material associated with the key. If the key doesn't exist, returns null.*/
		ObjMaterial* getMaterial(const std::string& name);
	private:
		ResourcesManager<ObjMaterial*> m_mtl;
};

#endif
