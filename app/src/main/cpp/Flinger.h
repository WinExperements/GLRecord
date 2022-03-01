#ifndef FLINGER_H
#define FLINGER_H
#include <jni.h>
#include "CustomDisplay.h"
#include <android/native_window.h>
#include <vector>
using namespace std;
typedef struct flingerApp_t {
    JNIEnv *env; //used for calling a java programs
    jobject thiz; //pointer to a java class
    void (*init)(flingerApp_t me);
    void (*resize)(flingerApp_t me,int w,int h);
    void (*render)(flingerApp_t me);
} FlingerApp;
class Flinger {
private:
    vector<CustomDisplay> displays;
    void throwError(JNIEnv *env,const char *err);
    bool init;
    vector<FlingerApp> apps;
    bool block; //To prevent crash!
    bool stoped;
public:
    void initialize();
    int addDisplay(JNIEnv *env,ANativeWindow *nativeWindow);
    void threadMain(JNIEnv *env);
    void removeDisplay(int id);
    void deInit(JNIEnv *env);
    bool initialized() {return init;}
    CustomDisplay getDisplay(int id);
    void stop();
    int addApp(FlingerApp app);
    void removeApp(int id);
};

#endif