#include "nativeFont.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Font_loadFromFileFont(JNIEnv* jenv, jclass jcls, jobject bmp, jintArray width, jintArray height, jintArray posX, jintArray posY, int maxWidth, int maxHeight, int padX, int padY, jobject fontMetrics)
{
	Bitmap* bitmap = (Bitmap*) Java_com_gaulois94_Graphics_Bitmap_createBitmap(jenv, jcls, bmp);
	Texture* texture   = (Texture*) Java_com_gaulois94_Graphics_Texture_loadFromBitmapTexture(jenv, jcls, (jlong)bitmap);

	delete bitmap;
	int* charWidth     = (int*)jenv->GetIntArrayElements(width, 0);
	int* charHeight    = (int*)jenv->GetIntArrayElements(height, 0);
	LOG_ERROR("char Height %d", charHeight[10]);
	
	int* charPosX      = (int*)jenv->GetIntArrayElements(posX, 0);
	int* charPosY      = (int*)jenv->GetIntArrayElements(posY, 0);

	jclass fmClass     = jenv->GetObjectClass(fontMetrics);
	jfieldID bottomID  = jenv->GetFieldID(fmClass, "bottom", "F");
	jfieldID topID     = jenv->GetFieldID(fmClass, "top", "F");
	jfieldID ascentID  = jenv->GetFieldID(fmClass, "ascent", "F");
	jfieldID descentID = jenv->GetFieldID(fmClass, "descent", "F");
	jfieldID leadingID = jenv->GetFieldID(fmClass, "leading", "F");

	struct FontMetrics fm;
	fm.bottom          = jenv->GetFloatField(fontMetrics, bottomID);
	fm.top             = jenv->GetFloatField(fontMetrics, topID);
	fm.ascent          = jenv->GetFloatField(fontMetrics, ascentID);
	fm.descent         = jenv->GetFloatField(fontMetrics, descentID);
	fm.leading         = jenv->GetFloatField(fontMetrics, leadingID);
	fm.fontMetrics     = fontMetrics;

	Font* font = new Font(texture, charWidth, charHeight, charPosX, charPosY, maxWidth, maxHeight, padX, padY, fm);
	jenv->ReleaseIntArrayElements(width, charWidth, 0);
	jenv->ReleaseIntArrayElements(height, charHeight, 0);
	jenv->ReleaseIntArrayElements(posX, charPosX, 0);
	jenv->ReleaseIntArrayElements(posY, charPosY, 0);

	return (long)font;
}

JNIEXPORT jfloat JNICALL Java_com_gaulois94_Graphics_Font_getLineHeightFont(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	return ((Font*)ptr)->getLineHeight();
}

JNIEXPORT jintArray JNICALL Java_com_gaulois94_Graphics_Font_getPosFont(JNIEnv* jenv, jobject jobj, jlong ptr, jchar character)
{
	Font* font        = (Font*)ptr;
	jintArray result;

	result            = jenv->NewIntArray(2);
	glm::vec2 pos     = font->getPosition(character);
	int p[2]          = {(int)pos.x, (int)pos.y};
	jenv->SetIntArrayRegion(result, 0, 2, p);

	return result;
}

JNIEXPORT jintArray JNICALL Java_com_gaulois94_Graphics_Font_getSizeFont(JNIEnv* jenv, jobject jobj, jlong ptr, jchar character)
{
	Font* font        = (Font*)ptr;
	jintArray result;

	result            = jenv->NewIntArray(2);
	glm::vec2 size    = font->getSize(character);
	int s[2]          = {(int)size.x, (int)size.y};
	jenv->SetIntArrayRegion(result, 0, 2, s);

	return result;
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Font_getLeadingFont(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	Font* font = (Font*) ptr;
	return font->getFontMetrics().leading;
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Font_getTextureFont(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	return (jlong) (((Font*)ptr)->getTexture());
}
