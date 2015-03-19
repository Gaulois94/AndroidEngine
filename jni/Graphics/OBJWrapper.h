#ifndef DEF_OBJWRAPPER_INCLUDE
#define DEF_OBJWRAPPER_INCLUDE

#define GL_GLEXT_PROTOTYPES
#define GLM_FORCE_RADIANS

#include "jni.h"
#include "utils.h"

#include "ResourcesManager.h"
#include "Shape/TriangleShape.h"
#include "Materials/ObjMaterial.h"
#include "Drawable.h"
#include "File.h"
#include "MaterialWrapper.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define COORDS_PER_VERTEX 3

struct OBJDatas
{
	int vertexPositionLength;
	int vertexNormalLength;
	GLuint vboID;
	MaterialWrapper* mtlWrapper;

	std::map<std::string, int> materialSerie;
};

class OBJWrapper : public Drawable
{
	public:
		OBJWrapper(JNIEnv* jenv, jobject context, File& file);
		~OBJWrapper();
		virtual void onDraw(Renderer* renderer, glm::mat4& mvp);
		void setMaterial(Material* mtl); //set the material FOR ALL OBJ's.
	private:
		ResourcesManager<MaterialWrapper*> m_mtlWrapper;
		ResourcesManager<OBJDatas*> m_objDatas;
};

#endif
