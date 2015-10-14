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

/** \brief OBJWrapper class. This class read an .obj file and extract all the information about the obj 3d object (vertex, normal), associate them with their own material (via MaterialWrapper)*/
class OBJWrapper : public Drawable
{
	public:
		/** \brief Basic constructor of OBJWrapper
		 * \param parent its parent
		 * \param jenv the java environment, used for reading the android file.
		 * \param context the android context, used for reading the android file
		 * \param file the file to being parsed*/
		OBJWrapper(Updatable* parent, JNIEnv* jenv, jobject context, File& file);
		~OBJWrapper();
		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
	private:
		ResourcesManager<MaterialWrapper*> m_mtlWrapper;
		ResourcesManager<OBJDatas*> m_objDatas;
};

#endif
