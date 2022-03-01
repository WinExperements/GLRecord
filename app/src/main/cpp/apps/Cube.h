#ifndef CUBE_H
#define CUBE_H
#include "../Flinger.h"
void cube_init(FlingerApp me);
void cube_resize(FlingerApp me,int w,int h);
void cube_render(FlingerApp me);
FlingerApp cube_create();
#endif