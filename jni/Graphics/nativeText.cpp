#include "nativeText.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Text_createText(JNIEnv *jenv, jclass jcls, jlong font, jstring text, jfloatArray color)
{
    const char * t = jenv->GetStringUTFChars(text, 0);
	jfloat* c      = jenv->GetFloatArrayElements(color, 0);

	Text* ptr      = new Text((Font*) font, t, Color(c[0], c[1], c[2], c[3]));
	jenv->ReleaseFloatArrayElements(color, c, 0);
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

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Text_setColorText(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray color)
{
	jfloat* c      = jenv->GetFloatArrayElements(color, 0);
	Text* text     = (Text*)ptr;
	text->setColor(Color(c[0], c[1], c[2], c[3]));
	jenv->ReleaseFloatArrayElements(color, c, 0);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Text_setFontText(JNIEnv *jenv, jobject jobj, jlong ptr, jlong font)
{
	Text* text = (Text*)ptr;
	text->setFont((Font*)font);
}
