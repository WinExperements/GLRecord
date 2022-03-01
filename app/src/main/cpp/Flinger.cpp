#include "Flinger.h"
#include <GLES2/gl2.h>
#include <android/log.h>
#define TAG "FlingerRender"
void Flinger::initialize() {

}
void Flinger::throwError(JNIEnv* env,const char *err) {
    jclass errClass = env->FindClass("java/lang/RuntimeException");
    env->ThrowNew(errClass,err);
}
int Flinger::addDisplay(JNIEnv *env,ANativeWindow *nativeWindow) {
    if (nativeWindow == nullptr) {
        throwError(env,"Given display is empty (nativeWindow == nullptr)");
        return -1;
    }
    CustomDisplay d;
    d.initialize(nativeWindow,env);
    displays.push_back(d);
    return displays.size()-1;
}

void Flinger::threadMain(JNIEnv *env) {
    if (block) {
        __android_log_print(ANDROID_LOG_INFO,TAG,"Cant process due block flag!");
        return;
    }
   int size = displays.size();
   for (int i = 0; i < size; i++) {
       CustomDisplay d = getDisplay(i);
       d.makeCurrent();
       glClearColor(0.0f,0.0f,0.0f,1.0f);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       for (int a = 0; a < apps.size(); a++) {
           FlingerApp app = apps.at(a);
           if (!d.setup) app.init(app);
           else if (!d.resize) app.resize(app,480,960); else app.render(app);
       }
       if (!d.setup) {
           __android_log_print(ANDROID_LOG_INFO,TAG,"d.setup = true");
           d.setup = true;
       }else if (!d.resize) {
           __android_log_print(ANDROID_LOG_INFO,TAG,"d.resize = true");
           d.resize = true;
       }
       else d.swapBuffers();
       // Update Display here
       displays[i] = d;
   }
}

void Flinger::removeDisplay(int id) {
    if (stoped) {
        __android_log_print(ANDROID_LOG_WARN,TAG,"Process stoped, cant remove display!");
        return;
    }
    if (id < 1 | id > displays.size()) return;
    block = true;
    displays.at(id).release();
    auto dd = displays.begin();
    advance(dd,id);
    displays.erase(dd);
    block = false;
}

void Flinger::deInit(JNIEnv *env) {
    block = true;
    __android_log_print(ANDROID_LOG_INFO,TAG,"Native: Deinit!");
    if (displays.size() == 0) {
        throwError(env,"No displays or already de-initialed!");
        return;
    }
    for (int i = 0; i < displays.size(); i++) {
        CustomDisplay d = displays.at(i);
        removeDisplay(i);
    }
    stoped = true;
    __android_log_print(ANDROID_LOG_INFO,TAG,"De-initialized, now you can close your activity");
}

CustomDisplay Flinger::getDisplay(int id) {
    return displays.at(id);
}

void Flinger::stop() {
    block = true;
}

int Flinger::addApp(FlingerApp app) {
    block = true;
    apps.push_back(app);
    block = false;
    return apps.size()-1;
}

void Flinger::removeApp(int id) {
    block = true;
    auto dd = apps.begin();
    advance(dd,id);
    apps.erase(dd);
    block = false;
}
