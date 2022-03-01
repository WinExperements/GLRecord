#ifndef CUSTOMDISPLAY_H
#define CUSTOMDISPLAY_H
#include<android/native_window.h>
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include<jni.h>
class CustomDisplay {
private:
    ANativeWindow* surf;
    EGLDisplay eglDisplay;
    EGLSurface eglSurface;
    EGLContext eglContext;
    JNIEnv *env;
    void setupGL();
    void checkGLError(const char *errMSG);
    void throwErr(const char *msg);
public:
    CustomDisplay();
    void makeCurrent();
    void swapBuffers();
    void initialize(ANativeWindow *window,JNIEnv *jniEnv);
    void release();
    bool setup;
    bool resize;
};
#endif