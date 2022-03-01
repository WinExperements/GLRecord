#include "CustomDisplay.h"
#include<android/log.h>
void CustomDisplay::initialize(ANativeWindow *window, JNIEnv *jniEnv) {
    surf = window;
    env = jniEnv;
    setupGL();
}
void CustomDisplay::setupGL() {
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisplay == nullptr) {
        throwErr("Failed to get display");
    }
    int ver[2];
    if (!eglInitialize(eglDisplay,ver,ver)) {
        throwErr("Failed to initialize egl");
    }
    int attr[] = {EGL_RED_SIZE,8,EGL_GREEN_SIZE,8,EGL_BLUE_SIZE,8,EGL_ALPHA_SIZE,8,EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,0x3142,1,EGL_NONE};
    EGLConfig conf[1];
    int numConfg[1];
    eglChooseConfig(eglDisplay,attr,conf,1,numConfg);
    checkGLError("eglChoseConfig");
    int attrList[] = {EGL_CONTEXT_CLIENT_VERSION,2,EGL_NONE};
    eglContext = eglCreateContext(eglDisplay,conf[0],EGL_NO_CONTEXT,attrList);
    checkGLError("eglCreateContext");
    int surfParams[] = {EGL_NONE};
    eglSurface = eglCreateWindowSurface(eglDisplay,conf[0],surf,surfParams);
    checkGLError("eglCreateWindowSurface");
}
void CustomDisplay::makeCurrent() {
    eglMakeCurrent(eglDisplay,eglSurface,eglSurface,eglContext);
    checkGLError("eglMakeCurrent");
}
void CustomDisplay::checkGLError(const char *errMSG) {
    int err;
    if ((err = eglGetError()) != EGL_SUCCESS) {
        __android_log_print(ANDROID_LOG_ERROR,"CustomDisplay","EGL error at %s: %d",errMSG,err);
        jclass errclass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(errclass,"EGL error");
    }
}
void CustomDisplay::swapBuffers() {
    eglSwapBuffers(eglDisplay,eglSurface);
    checkGLError("eglSwapBuffers");
}
void CustomDisplay::throwErr(const char *msg) {
    jclass cl = env->FindClass("java/lang/RuntimeException");
    env->ThrowNew(cl,msg);
}
CustomDisplay::CustomDisplay() {
    return;
}
void CustomDisplay::release() {
    if (eglDisplay != EGL_NO_DISPLAY) {
        eglMakeCurrent(eglDisplay,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
        eglDestroySurface(eglDisplay,eglSurface);
        eglDestroyContext(eglDisplay,eglContext);
        eglReleaseThread();
        eglTerminate(eglDisplay);
    }
    ANativeWindow_release(surf);
    eglDisplay = EGL_NO_DISPLAY;
    eglSurface = EGL_NO_SURFACE;
    eglContext = EGL_NO_CONTEXT;
    surf = nullptr;
}