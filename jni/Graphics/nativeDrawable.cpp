#include "nativeDrawable.h"

namespace
{
	const char* colorVert = 
					"precision mediump float;"
					"attribute vec3 vPosition;"
					"attribute vec4 vColor;"
					"attribute vec2 vTextureCoord;"

					"uniform mat4 uMVP;"
					"uniform mat4 uCameraMVP;"
					"uniform mat4 uModelMatrix;"

					"varying vec4 varyColor;"
					"varying vec2 varyTextureCoord;"
					"varying vec4 varyModelPosition;"
					"varying vec4 varyPosition;"

					"void main()"
					"{"
						"gl_Position       = uMVP * vec4(vPosition, 1.0);"
						"varyPosition      = gl_Position;"
						"varyModelPosition = uModelMatrix * vec4(vPosition, 1.0);"
						"varyColor         = vColor;"
						"varyTextureCoord  = vTextureCoord;"
					"}";

	const char* colorFrag = 
					"precision mediump float;"
					""
					"struct Clipping"
					"{"
					"	bool  clip;"
					"	float x;"
					"	float y;"
					"	float width;"
					"	float height;"
					"};"
					""
					"uniform vec4 uMaskColor;"
					""
					"uniform sampler2D uTexture;"
					"uniform bool uUseTexture;"
					"uniform bool uUseUniColor;"
					"uniform vec4 uUniColor;"
					""
					"uniform Clipping uLocalClipping;"
					"uniform Clipping uGlobalClipping;"
					""
					"varying vec2 varyTextureCoord;"
					"varying vec4 varyColor;"
					"varying vec4 varyModelPosition;"
					"varying vec4 varyPosition;"
					""
					"void main()"
					"{"
					"	//Do the clipping"
					"	//You have local clipping "
					"	if(uLocalClipping.clip)"
					"	{"
					"		if(varyModelPosition.x < uLocalClipping.x || varyModelPosition.y < uLocalClipping.y "
					"		   || varyModelPosition.x > uLocalClipping.x +uLocalClipping.width || varyModelPosition.y > uLocalClipping.y + uLocalClipping.height)"
					"			discard;"
					"	}"
					""
					"	//And global clipping "
					"	if(uGlobalClipping.clip)"
					"	{"
					"		if(varyPosition.x < uGlobalClipping.x || varyPosition.y < uGlobalClipping.y "
					"		   || varyPosition.x > uGlobalClipping.x +uGlobalClipping.width || varyPosition.y > uGlobalClipping.y + uGlobalClipping.height)"
					"			discard;"
					"	}"
					""
					"	if(uUseUniColor)"
					"		gl_FragColor = uUniColor;"
					"	else"
					"		gl_FragColor = varyColor;"
					""
					"	if(uUseTexture)"
					"	{"
					"		vec4 textColor = texture2D(uTexture, varyTextureCoord);"
					""
					"		if(uMaskColor[3] == 0.0 && textColor[3] == 0.0)"
					"			discard;"
					"		else if(uMaskColor == textColor)"
					"			discard;"
					"	}"
					"}";

	const char* textureVert =
					"precision mediump float;"
					"attribute vec3 vPosition;"
					"attribute vec2 vTextureCoord;"
					"uniform mat4 uMVP;"
					"uniform mat4 uModelMatrix;"
					""
					"varying vec2 vary_textureCoord;"
					"varying vec4 varyModelPosition;"
					"varying vec4 varyPosition;"
					""
					"void main()"
					"{"
					"	gl_Position       = uMVP * vec4(vPosition, 1.0);"
					"	varyPosition      = gl_Position;"
					"	vary_textureCoord = vTextureCoord;"
					"	varyModelPosition = uModelMatrix * vec4(vPosition, 1.0);"
					"}";

	const char* textureFrag =
					"precision mediump float;"
					""
					"struct Clipping"
					"{"
					"	bool  clip;"
					"	float x;"
					"	float y;"
					"	float width;"
					"	float height;"
					"};"
					""
					"varying vec2 vary_textureCoord;"
					""
					"uniform Clipping uLocalClipping;"
					"uniform Clipping uGlobalClipping;"
					"uniform sampler2D uTexture;"
					"uniform float uOpacity;"
					"varying vec4 varyModelPosition;"
					"varying vec4 varyPosition;"
					""
					"void main()"
					"{"
					"	//Do the clipping"
					"	//You have local clipping "
					"	if(uLocalClipping.clip)"
					"	{"
					"		discard;"
					"		if(varyModelPosition.x < uLocalClipping.x || varyModelPosition.y < uLocalClipping.y "
					"		   || varyModelPosition.x > uLocalClipping.x +uLocalClipping.width || varyModelPosition.y > uLocalClipping.y + uLocalClipping.height)"
					"			discard;"
					"	}"
					""
					"	//And global clipping "
					"	if(uGlobalClipping.clip)"
					"	{"
					"		if(varyPosition.x < uGlobalClipping.x || varyPosition.y < uGlobalClipping.y "
					"		   || varyPosition.x > uGlobalClipping.x +uGlobalClipping.width || varyPosition.y > uGlobalClipping.y + uGlobalClipping.height)"
					"			discard;"
					"	}"
					""
					"	gl_FragColor = texture2D(uTexture, vary_textureCoord);"
					"	if(uOpacity > 0.0)"
					"		gl_FragColor.a = uOpacity;"
					"}";
	
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Drawable_addShaderDrawable(JNIEnv *jenv, jclass jcls, jstring key, jlong shader)
{
    const char *k = jenv->GetStringUTFChars(key, 0);
	Shader::shaders.add(std::string(k), (Shader*) shader);
	jenv->ReleaseStringUTFChars(key, k);
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Drawable_getShaderDrawable(JNIEnv *jenv, jclass jcls, jstring key)
{
    const char *k = jenv->GetStringUTFChars(key, 0);
	Shader* shader = Shader::shaders.get(std::string(k));
	jenv->ReleaseStringUTFChars(key, k);

	return (jlong)shader;
}

JNIEXPORT jstring JNICALL Java_com_gaulois94_Graphics_Drawable_getKeyShaderDrawable(JNIEnv *jenv, jclass jcls, jlong shader)
{
	std::string key = Shader::shaders.get((Shader*) shader);
	jstring result  = jenv->NewStringUTF(key.c_str());
	return result;
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Drawable_removeShaderFromKeyDrawable(JNIEnv *jenv, jclass jcls, jstring key)
{
    const char *k = jenv->GetStringUTFChars(key, 0);
	int result = Shader::shaders.remove(std::string(k));
	jenv->ReleaseStringUTFChars(key, k);

	return result;
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Drawable_removeShaderFromShaderDrawable(JNIEnv *jenv, jclass jcls, jlong shader)
{
	Shader* s = (Shader*)shader;
	int result = Shader::shaders.remove(s);
	return result;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Drawable_cleanShaders(JNIEnv *jenv, jclass jcls)
{
	Shader::shaders.clean();
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Drawable_getNumberOfShaders(JNIEnv *jenv, jclass jcls)
{
	return Shader::shaders.getSize();
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Drawable_existShaderFromKeyDrawable(JNIEnv *jenv, jclass jcls, jstring key)
{
    const char *k = jenv->GetStringUTFChars(key, 0);
	int result = Shader::shaders.exist(std::string(k));
	jenv->ReleaseStringUTFChars(key, k);

	return result;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Drawable_loadShadersDrawable(JNIEnv *jenv, jclass jcls, jobject context)
{
	std::string files[]          = {"basic", "color", "obj", "texture"};
	int size                     = 4;

	for(int i = 0; i < size; i++)
	{
		LOG_ERROR("LOADING SHADER NUMBER %d", i);
		std::string pathfString = "shaders/" + files[i] + ".frag";
		std::string pathvString = "shaders/" + files[i] + ".vert";

		File vertexFile        = File(jenv, context, pathvString.c_str(), "r");
		File fragFile          = File(jenv, context, pathfString.c_str(), "r");
		
		Shader::shaders.add(files[i], Shader::loadFromFiles(vertexFile, fragFile));
		  
		/*  
		if(files[i] == "color")
		{
			Shader::shaders.add(files[i], Shader::loadFromStrings(colorVert, colorFrag));
		}
		else if(files[i] == "texture")
		{
			Shader::shaders.add(files[i], Shader::loadFromStrings(textureVert, textureFrag));
		}
		*/
		
	}
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Drawable_drawDrawable(JNIEnv *jenv, jobject jobj, jlong ptr, jlong render, jfloatArray transformation)
{
	Drawable* drawable = (Drawable*)ptr;
	jfloat* ft = jenv->GetFloatArrayElements(transformation, 0);
	glm::mat4 t = glm::make_mat4(ft);
	drawable->draw(*(Render*)render, t);
	jenv->ReleaseFloatArrayElements(transformation, ft, 0);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Drawable_onDrawDrawable(JNIEnv *jenv, jobject jobj, jlong ptr, jlong render, jfloatArray transformation)
{
	Drawable* drawable = (Drawable*)ptr;
	jfloat* ft = jenv->GetFloatArrayElements(transformation, 0);
	glm::mat4 t = glm::make_mat4(ft);
	drawable->onDraw(*(Render*)render, t);
	jenv->ReleaseFloatArrayElements(transformation, ft, 0);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Drawable_onMoveDrawable(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray move, bool useScale)
{
	Drawable* drawable = (Drawable*)ptr;
	jfloat* m = jenv->GetFloatArrayElements(move, 0);
	drawable->onMove(glm::vec3(m[0], m[1], m[2]), useScale);
	jenv->ReleaseFloatArrayElements(move, m, 0);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_onRotateDrawable(JNIEnv *jenv, jobject jobj, jlong ptr, jfloat angle, jfloatArray axis, jfloatArray origin)
{
	Drawable* drawable = (Drawable*)ptr;
	jfloat* a = jenv->GetFloatArrayElements(axis, 0);
	jfloat* o = jenv->GetFloatArrayElements(origin, 0);
	drawable->onRotate(angle, glm::vec3(a[0], a[1], a[2]), glm::vec3(o[0], o[1], o[2]));
	jenv->ReleaseFloatArrayElements(axis, a, 0);
	jenv->ReleaseFloatArrayElements(origin, o, 0);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_onScaleDrawable(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray scale)
{
	Drawable* drawable = (Drawable*)ptr;
	jfloat* s = jenv->GetFloatArrayElements(scale, 0);
	drawable->onScale(glm::vec3(s[0], s[1], s[2]));
	jenv->ReleaseFloatArrayElements(scale, s, 0);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_staticToCameraDrawable(JNIEnv *jenv, jclass jcls, jlong ptr, jint s)
{
	Drawable* drawable = (Drawable*) ptr;
	drawable->staticToCamera(s);	
}

JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_isStaticToCameraDrawable(JNIEnv *jenv, jclass jcls, jlong ptr)
{
	Drawable* drawable = (Drawable*) ptr;
	return drawable->isStaticToCamera();
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_setMaterialDrawable(JNIEnv *jenv, jclass jcls, jlong ptr, jlong materialPtr)
{
	Drawable* drawable = (Drawable*) ptr;
	drawable->setMaterial((Material*)materialPtr);
}

JNIEXPORT jlong   JNICALL Java_com_gaulois94_Graphics_Drawable_getMaterialDrawable(JNIEnv *jenv, jclass jcls, jlong ptr)
{
	Drawable* drawable = (Drawable*) ptr;
	return (long)(drawable->getMaterial());
}
