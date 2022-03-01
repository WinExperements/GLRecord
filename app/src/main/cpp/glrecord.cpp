#include <jni.h>
#include <vector>
#include "CustomDisplay.h"
#include "Flinger.h"
#include "apps/Cube.h"
using namespace std;
Flinger fl;
void javaApp_init(flingerApp_t me) {
    JNIEnv *env = me.env;
    jclass cl = env->GetObjectClass(me.thiz);
    jmethodID methodID = env->GetMethodID(cl,"init","V");
    if (methodID == nullptr) {
        return;
    }
    env->CallVoidMethod(me.thiz,methodID);
}
void javaApp_resize(flingerApp_t me,int w,int h) {
    JNIEnv *env = me.env;
    jclass cl = env->GetObjectClass(me.thiz);
    jmethodID methodID = env->GetMethodID(cl,"resize","(I,I)V");
    if (methodID == nullptr) {
        return;
    }
    env->CallVoidMethod(me.thiz,methodID,w,h);
}
void javaApp_render(flingerApp_t me) {
    JNIEnv *env = me.env;
    jclass cl = env->GetObjectClass(me.thiz);
    jmethodID methodID = env->GetMethodID(cl,"render","V");
    if (methodID == nullptr) {
        return;
    }
    env->CallVoidMethod(me.thiz,methodID);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_gametab_glrecord_glrecord_CustomDisplay_nativeInit(JNIEnv *env, jobject thiz,
                                                            jobject surf) {
    if (fl.initialized()) {
        return fl.addDisplay(env,ANativeWindow_fromSurface(env,surf));
    } else {
        fl.initialize();
        return fl.addDisplay(env,ANativeWindow_fromSurface(env,surf));
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_gametab_glrecord_glrecord_CustomDisplay_nativeMakeCurrent(JNIEnv *env, jobject thiz,
                                                                   jint id) {
    fl.getDisplay(id).makeCurrent();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_gametab_glrecord_glrecord_CustomDisplay_nativeSwapBuffers(JNIEnv *env, jobject thiz,
                                                                   jint id) {
   fl.getDisplay(id).swapBuffers();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_gametab_glrecord_glrecord_CustomDisplay_nativeRelease(JNIEnv *env, jobject thiz, jint id) {
    fl.removeDisplay(id);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_gametab_glrecord_glrecord_Flinger_flingerInit(JNIEnv *env, jobject thiz) {
    fl.initialize();
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_gametab_glrecord_glrecord_Flinger_flingerAddDisplay(JNIEnv *env, jobject thiz,
                                                             jobject surf) {
    return fl.addDisplay(env,ANativeWindow_fromSurface(env,surf));
}
extern "C"
JNIEXPORT void JNICALL
Java_com_gametab_glrecord_glrecord_Flinger_flingerDeInit(JNIEnv *env, jobject thiz) {
    fl.deInit(env);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_gametab_glrecord_glrecord_Flinger_flingerThreadMain(JNIEnv *env, jobject thiz) {
    fl.threadMain(env);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_gametab_glrecord_glrecord_Flinger_flingerRemoveDisplay(JNIEnv *env, jobject thiz,
                                                                jint id) {
  //  fl.getDisplay(id).release();
    fl.removeDisplay(id);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_gametab_glrecord_glrecord_Flinger_flingerStop(JNIEnv *env, jobject thiz) {
    fl.stop();
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_gametab_glrecord_glrecord_Flinger_flingerAddApp(JNIEnv *env, jobject thiz, jobject app) {
    FlingerApp appf;
    appf.env = env;
    appf.thiz = app;
    appf.init = javaApp_init;
    appf.resize = javaApp_resize;
    appf.render = javaApp_render;
    return fl.addApp(appf);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_gametab_glrecord_glrecord_Flinger_flingerRemoveApp(JNIEnv *env, jobject thiz, jint id) {
    fl.removeApp(id);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_gametab_glrecord_glrecord_Flinger_flingerAddApps(JNIEnv *env, jobject thiz) {
    fl.addApp(cube_create());
}