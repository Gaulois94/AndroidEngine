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

/** \brief the datas of one OBJ object */
struct OBJDatas
{
	int vertexPositionLength; /** <The length of the position vector.*/
	int vertexNormalLength;/** <The length of the normal vector.*/
	GLuint vboID;/** <The vertex buffer object where the vertex positions and normals are stored*/
	MaterialWrapper* mtlWrapper;/** <The material wrapper associated with this OBJ */

	std::map<std::string, int> materialSerie;/** <How many vertex the material associated with the key string must be actived*/
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
