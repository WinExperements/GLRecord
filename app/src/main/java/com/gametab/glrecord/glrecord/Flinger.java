package com.gametab.glrecord.glrecord;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.opengl.GLES20;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.preference.PreferenceManager;

import com.gametab.glrecord.glrecord.apps.CubeApp;
import com.gametab.glrecord.glrecord.framework.capture.CaptureFramework;


public class Flinger implements SurfaceHolder.Callback {
    static {
        System.loadLibrary("engine");
    }
    private final SurfaceView view;
    private final Activity ac;
    private static Flinger instance;
    private CaptureFramework fr;
    private boolean start;
    public Flinger(Activity activity) {
        ac = activity;
        view = new SurfaceView(ac);
        view.getHolder().addCallback(this);
        ac.setContentView(view);
        ac.getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_FULLSCREEN | View.SYSTEM_UI_FLAG_IMMERSIVE | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
        instance = this;
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder surfaceHolder) {
       flingerInit();
       flingerAddDisplay(surfaceHolder.getSurface());
       flingerAddApps();
       startMe();
        fr = new CaptureFramework();
        fr.startRecord();
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder surfaceHolder, int i, int i1, int i2) {

    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder surfaceHolder) {

    }
    private void startMe() {
        start = true;
        new Thread(new Runnable() {
            @Override
            public void run() {
                Log.i("SurfaceThread","Thread in loop");
               while(start) {
                   flingerThreadMain();
               }
               Log.i("SurfaceThread","Stopping! Capture Framework are down!");
               fr.stopRecord();
               Log.i("SurfaceThread","Calling flingerDeInit function!");
                flingerDeInit();
                Log.i("SurfaceThread","Done!");
                ac.finish();
            }
        }).start();
    }
    public void stopFlinger() {
        start = false;
    }
    public static Flinger getInstance() {
        return instance;
    }
    public int addDisplay(Surface v) {
        return flingerAddDisplay(v);
    }
    public void removeDisplay(int id) {
        flingerRemoveDisplay(id);
    }
    public Context getContext() {
        return ac.getApplicationContext();
    }
    public Activity getActivity() {
        return ac;
    }
    public int addApp(GLApp app) {
        return flingerAddApp(app);
    }
    public void removeApp(int id) {
        flingerRemoveApp(id);
    }
    private native void flingerInit();
    private native int flingerAddDisplay(Surface surf);
    public native void flingerDeInit();
    private native void flingerThreadMain();
    private native void flingerRemoveDisplay(int id);
    public native void flingerStop();
    private native int flingerAddApp(GLApp app);
    private native void flingerRemoveApp(int id);
    private native void flingerAddApps();
}
