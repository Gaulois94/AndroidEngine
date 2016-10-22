#include "Keyboard.h"

void Keyboard::showKeyboard(bool show)
{
	//Get the InputMethodManager
	//
	//InputMethodManager imm = (InputMethodManager) mContext.getSystemService(Context.INPUT_METHOD_SERVICE);
	JNIEnv* env                       = JniMadeOf::getJEnv();
	jclass immClass                 = env->FindClass("android/view/inputmethod/InputMethodManager");
	jclass ctxClass                 = env->FindClass("android/content/Context");
	jmethodID getSystemService      = env->GetMethodID(ctxClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
	jfieldID INPUT_METHOD_SERVICEID = env->GetStaticFieldID(ctxClass, "INPUT_METHOD_SERVICE", "Ljava/lang/String;");
	jobject INPUT_METHOD_SERVICE    = env->GetStaticObjectField(ctxClass, INPUT_METHOD_SERVICEID);
	jobject imm                     = env->CallObjectMethod(JniMadeOf::context, getSystemService, INPUT_METHOD_SERVICE);

	//Call the correct function following show value
	//imm.toggleSoftInput(InputMethodManager.SHOW_FORCED,0);
	//imm.toggleSoftInput(InputMethodManager.HIDE_IMPLICIT_ONLY,0);
	jmethodID toggleSoftInputID     = env->GetMethodID(immClass, "toggleSoftInput", "(II)V");
	jfieldID SHOWID                 = env->GetStaticFieldID(immClass, (show) ? "SHOW_FORCED" : "HIDE_IMPLICIT_ONLY", "I");
	int SHOW                        = env->GetStaticIntField(immClass, SHOWID);
	env->CallVoidMethod(imm, toggleSoftInputID, SHOW, 0);
}
