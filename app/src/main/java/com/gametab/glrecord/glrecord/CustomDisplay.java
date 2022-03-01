package com.gametab.glrecord.glrecord;

import android.view.Surface;

public class CustomDisplay {
    static {
        System.loadLibrary("engine");
    }
    private int id;
    public CustomDisplay(Surface surf) {
        id = nativeInit(surf);
    }
    public void makeCurrent() {
        nativeMakeCurrent(id);
    }
    public void swapBuffers() {
        nativeSwapBuffers(id);
    }
    public void release() {
        nativeRelease(id);
    }
    public int getNativeID() {
        return id;
    }
    private native int nativeInit(Surface surf);
    private native void nativeMakeCurrent(int id);
    private native void nativeSwapBuffers(int id);
    private native void nativeRelease(int id);
}
