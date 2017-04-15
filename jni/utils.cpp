#include "utils.h"

std::vector<std::string> split(const std::string& buffer, char delim)
{
	std::vector<std::string> r;
	std::istringstream iss(buffer);
	std::string s;
	while(getline(iss, s, delim))
		r.push_back(s);
	return r;
}

std::string getTextFromRes(const std::string& id)
{
	std::vector<std::string> ids;
	std::string packageName;

	//Split the id via dots
	std::istringstream iss(id);
	char* token = (char*)malloc(id.size()+1);
	while(iss.getline(token, id.size(), '.'))
		ids.push_back(std::string(token));

	JNIEnv* env = JniMadeOf::getJEnv();

	//Get the package name
	jclass contextClass      = env->GetObjectClass(JniMadeOf::context);
	jmethodID packageNameID  = env->GetMethodID(contextClass, "getPackageName", "()Ljava/lang/String;");
	jmethodID resourceMethod = env->GetMethodID(contextClass, "getResources", "()Landroid/content/res/Resources;");

	jstring jPackageName     = (jstring)(env->CallObjectMethod(JniMadeOf::context, packageNameID));
	const char* packageNameC = env->GetStringUTFChars(jPackageName, 0);
	packageName              = packageNameC;
	std::replace(packageName.begin(), packageName.end(), '.', '/');
	env->ReleaseStringUTFChars(jPackageName, packageNameC);
	
	//Get the resource id (an integer)
    std::string currentClassName = packageName+"/R";
	for(uint32_t i=0; i < ids.size()-1; i++)
        currentClassName += "$" + ids[i];

    jclass rClass    = JniMadeOf::getClass(currentClassName);
    jfieldID fieldID = env->GetStaticFieldID(rClass, ids.rbegin()->c_str(), "I");
    int intID        = env->GetStaticIntField(rClass, fieldID);

    //Get the string resources
	jobject resource      = env->CallObjectMethod(JniMadeOf::context, resourceMethod);
	jclass resourceClass  = env->GetObjectClass(resource);
    jmethodID getStringID = env->GetMethodID(resourceClass, "getString", "(I)Ljava/lang/String;");
    jstring jTextVal      = (jstring)env->CallObjectMethod(resource, getStringID, intID);

	const char* textValC = env->GetStringUTFChars(jTextVal, 0);
    std::string textVal = textValC;
	env->ReleaseStringUTFChars(jTextVal, textValC);

    return textVal;
}
