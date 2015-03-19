#include "nativeText.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Text_createText(JNIEnv *jenv, jclass jcls, jint material, jlong font, jstring text)
{
    const char * t = jenv->GetStringUTFChars(text, 0);

	Text* ptr      = new Text((Material*)material, (Font*) font, t);
	jenv->ReleaseStringUTFChars(text, t);
	return (long) ptr;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Text_setTextText(JNIEnv *jenv, jobject jobj, jlong ptr, jstring text)
{
    const char * t = jenv->GetStringUTFChars(text, 0);
	Text* textPtr = (Text*) ptr;
	textPtr->setText(t);
	jenv->ReleaseStringUTFChars(text, t);	
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Text_setFontText(JNIEnv *jenv, jobject jobj, jlong ptr, jlong font)
{
	Text* text = (Text*)ptr;
	text->setFont((Font*)font);
}

JNIEXPORT long JNICALL Java_com_gaulois94_Graphics_Text_getFontText(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Text* text = (Text*) ptr;
	return (long) (text->getFont());
}

JNIEXPORT jstring JNICALL Java_com_gaulois94_Graphics_Text_getTextText(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Text* text = (Text*) ptr;
	return jenv->NewStringUTF(text->getText());
}
