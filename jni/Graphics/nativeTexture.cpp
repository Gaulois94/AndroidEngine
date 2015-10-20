#include "nativeTexture.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_initTexture(JNIEnv* jenv, jclass jcls, jlong width, jlong height)
{
	Texture* texture = new Texture(width, height);
	return (jlong)texture;
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_loadFromPixelsTexture(JNIEnv* jenv, jclass jcls, jbyteArray pixels, jlong width, jlong height, jboolean alpha)
{
	unsigned char* p = (unsigned char*)(jenv->GetByteArrayElements(pixels, 0));
	Texture* texture = new Texture(p, width, height, alpha);
	jenv->ReleaseByteArrayElements(pixels, (jbyte*)p, 0);
	return (jlong)texture;
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_loadFromBitmapTexture(JNIEnv* jenv, jclass jcls, jlong bmp)
{
	Texture* texture = new Texture((Bitmap*) bmp);
	return (jlong)texture;
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_loadFromFileTexture(JNIEnv* jenv, jclass jcls, jstring path)
{
	//Load the android Bitmap
	//Function : Bitmap bmp = BitmapFactory.decodeStream(JniMadeOf::jassetsManager.open(path))
	jclass BitmapFactory   = jenv->FindClass("android/graphics/BitmapFactory");
	jmethodID decodeStream = jenv->GetStaticMethodID(BitmapFactory, "decodeStream", "(Ljava/io/InputStream;)Landroid/graphics/Bitmap;");
	jclass AssetManager    = jenv->FindClass("android/content/res/AssetManager");
	jmethodID open         = jenv->GetMethodID(AssetManager, "open", "(Ljava/lang/String;)Ljava/io/InputStream;");
	jobject jstream        = jenv->CallObjectMethod(JniMadeOf::jassetsManager, open, path);
	jobject jbmp           = jenv->CallStaticObjectMethod(BitmapFactory, decodeStream, jstream);
	
	//Load the texture
	Bitmap*	bmp = (Bitmap*) Java_com_gaulois94_Graphics_Bitmap_createBitmap(jenv, BitmapFactory, jbmp);
	Texture* texture = new Texture(bmp);

	delete bmp;
	return (jlong)texture;	
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Texture_setMaskColorTexture(JNIEnv* jenv, jobject jobj, jlong texture, jfloatArray color)
{
	float* c = jenv->GetFloatArrayElements(color, 0);
	((Texture*)ptr)->setMaskColor(Color(c[0], c[1], c[2], c[3]));
	jenv->ReleaseFloatArrayElements(color, c, 0);
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Texture_pixelsToTextureCoordTexture(JNIEnv* jenv, jobject jobj, jlong texture, jintArray pos)
{
	int* p   = jenv->GetIntArrayElements(pos, 0);
	float[] r = ((Texture*)ptr)->pixelsToTextureCoord(glm::vec2(p[0], p[1]));

	jfloatArray result = jenv->NewFloatArray(2);
	jenv->SetFloatArrayRegion(result, 0, 2, r);
	jenv->ReleaseIntArrayElements(pos, p, 0);

	return result;
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Texture_getRectTexture(JNIEnv* jenv, jobject jobj, jlong texture, jintArray pos, jintArray size)
{
	int* p = jenv->GetIntArrayElements(pos, 0);
	int* s = jenv->GetIntArrayElements(size, 0);

	Rectangle2f rect = ((Texture*)ptr)->getRect(glm::vec2(p[0], p[1]), glm::vec2(s[0], s[1]));
	float r[4] = {rect.x, rect.y, rect.width, rect.height};
	jfloatArray result = jenv->NewFloatArray(4);
	jenv->SetFloatArrayRegion(result, 0, 4, r);

	jenv->ReleaseIntArrayElements(pos, p, 0);
	jenv->ReleaseIntArrayElements(size, s, 0);

	return result;
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Texture_getRectTexture(JNIEnv* jenv, jobject jobj, jlong texture, jintArray rect)
{
	int* r = jenv->GetIntArrayElements(rect, 0);

	Rectangle2i rTexture = ((Texture*)ptr)->getRect(Rectangle2i(r[0], r[1], r[2], r[3]));
	float r2[4] = {rTexture.x, rTexture.y, rTexture.width, rTexture.height};
	jfloatArray result = jenv->NewFloatArray(4);
	jenv->SetFloatArrayRegion(result, 0, 4, r2);

	jenv->ReleaseIntArrayElements(rect, r, 0);

	return result;
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getIDTexture(JNIEnv* jenv, jobject jobj, jlong texture)
{
	Texture* ptr = (Texture*) texture;
	return (jlong) ptr->getID();
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getWidthTexture(JNIEnv* jenv, jobject jobj, jlong texture)
{
	Texture* ptr = (Texture*) texture;
	return ptr->getWidth();
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getHeightTexture(JNIEnv* jenv, jobject jobj, jlong texture)
{
	Texture* ptr = (Texture*) texture;
	return ptr->getHeight();
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getMaskColorTexture(JNIEnv* jenv, jobject jobj, jlong texture)
{
	jfloatArray result = jenv->NewFloatArray(4);
	Color c = ((Texture*)texture)->getMaskColor();
	float c[4] = {c.r, c.g, c.b, c.a};
	jenv->SetFloatArrayRegion(result, 0, 4, c);
	return result;
}
