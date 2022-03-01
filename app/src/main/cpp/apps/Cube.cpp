#include "Cube.h"
#include <GLES2/gl2.h>
#include <android/log.h>
#define TAG "CubeApp"
void cube_init(FlingerApp me) {
    __android_log_print(ANDROID_LOG_INFO,TAG,"cube_init called");
}
void cube_resize(FlingerApp me,int w,int h) {
    __android_log_print(ANDROID_LOG_INFO,TAG,"cube_resize called with parameters: %d, %d",w,h);
}
void cube_render(FlingerApp me) {
    __android_log_print(ANDROID_LOG_INFO,TAG,"init");
    glClearColor(255.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
FlingerApp cube_create() {
    FlingerApp app;
    app.init = cube_init;
    app.resize = cube_resize;
    app.render = cube_render;
    return app;
}