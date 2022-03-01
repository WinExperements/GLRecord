package com.gametab.glrecord.glrecord.apps;

import android.opengl.GLES20;

import com.gametab.glrecord.glrecord.GLApp;

public class CubeApp implements GLApp {
    @Override
    public void init() {

    }

    @Override
    public void resize(int w, int h) {

    }

    @Override
    public void render() {
        GLES20.glClearColor(255.0f,0.0f,0.0f,1.0f);
    }
}
