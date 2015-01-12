#include "nativeDrawable.h"

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Drawable_addShaderDrawable(JNIEnv *jenv, jclass jcls, jstring key, jlong shader)
{
    const char *k = jenv->GetStringUTFChars(key, 0);
	Drawable::shaders.add(std::string(k), (Shader*) shader);
	jenv->ReleaseStringUTFChars(key, k);
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Drawable_getShaderDrawable(JNIEnv *jenv, jclass jcls, jstring key)
{
    const char *k = jenv->GetStringUTFChars(key, 0);
	Shader* shader = Drawable::shaders.get(std::string(k));
	jenv->ReleaseStringUTFChars(key, k);

	return (jlong)shader;
}

JNIEXPORT jstring JNICALL Java_com_gaulois94_Graphics_Drawable_getKeyShaderDrawable(JNIEnv *jenv, jclass jcls, jlong shader)
{
	std::string key = Drawable::shaders.get((Shader*) shader);
	jstring result  = jenv->NewStringUTF(key.c_str());
	return result;
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Drawable_removeShaderFromKeyDrawable(JNIEnv *jenv, jclass jcls, jstring key)
{
    const char *k = jenv->GetStringUTFChars(key, 0);
	int result = Drawable::shaders.remove(std::string(k));
	jenv->ReleaseStringUTFChars(key, k);

	return result;
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Drawable_removeShaderFromShaderDrawable(JNIEnv *jenv, jclass jcls, jlong shader)
{
	Shader* s = (Shader*)shader;
	int result = Drawable::shaders.remove(s);
	return result;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Drawable_cleanShadersDrawable(JNIEnv *jenv, jclass jcls)
{
	Drawable::shaders.clean();
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Drawable_getNumberOfShadersDrawable(JNIEnv *jenv, jclass jcls)
{
	return Drawable::shaders.getSize();
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Drawable_existShaderFromKeyDrawable(JNIEnv *jenv, jclass jcls, jstring key)
{
    const char *k = jenv->GetStringUTFChars(key, 0);
	int result = Drawable::shaders.exist(std::string(k));
	jenv->ReleaseStringUTFChars(key, k);

	return result;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Drawable_loadShadersDrawable(JNIEnv *jenv, jclass jcls, jobject context)
{
	std::string files[]          = {"basic", "colorshader", "obj", "text", "texture"};
	int size                     = 5;

	for(int i = 0; i < size; i++)
	{
		std::map<std::string, int> attribs;
		if(files[i] == "basic")
		{
			std::string attribsKey[] = {"vPosition"};
			for(int k=0; k < 1; k++)
				attribs.insert(std::pair<std::string, int>(attribsKey[k], k));
		}

		else if(files[i] == "colorshader")
		{
			std::string attribsKey[] = {"vPosition", "vColor"};
			for(int k=0; k < 2; k++)
				attribs.insert(std::pair<std::string, int>(attribsKey[k], k));
		}

		else if(files[i] == "obj")
		{
			std::string attribsKey[] = {"vPosition", "vNormal"};
			for(int k=0; k < 2; k++)
				attribs.insert(std::pair<std::string, int>(attribsKey[k], k));
		}

		else if(files[i] == "texture")
		{
			std::string attribsKey[] = {"vPosition", "vTextureCoord"};
			for(int k=0; k < 2; k++)
				attribs.insert(std::pair<std::string, int>(attribsKey[k], k));
		}

		else if(files[i] == "text")
		{
			std::string attribsKey[] = {"vPosition", "vTextureCoord"};
			for(int k=0; k < 2; k++)
				attribs.insert(std::pair<std::string, int>(attribsKey[k], k));
		}

		std::string pathfString = "shaders/" + files[i] + ".frag";
		std::string pathvString = "shaders/" + files[i] + ".vert";

		File vertexFile        = File(jenv, context, pathvString.c_str(), "r");
		File fragFile          = File(jenv, context, pathfString.c_str(), "r");

		Drawable::shaders.add(files[i], Shader::loadFromFiles(vertexFile, fragFile, attribs));
	}
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Drawable_drawDrawable(JNIEnv *jenv, jobject jobj, jlong ptr, jlong renderer)
{
	Drawable* drawable = (Drawable*)ptr;
	drawable->draw((Renderer*)renderer);
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Drawable_canDrawDrawable(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Drawable* drawable = (Drawable*) ptr;
	return drawable->canDraw();
}
