package com.gametab.glrecord.glrecord.framework.capture;

import android.app.Service;
import android.content.Intent;
import android.media.MediaRecorder;
import android.os.IBinder;
import android.util.Log;

import com.gametab.glrecord.glrecord.CustomDisplay;
import com.gametab.glrecord.glrecord.Flinger;

import java.io.IOException;

public class CaptureService extends Service {
    private Flinger fl;
    private MediaRecorder recorder;
    private int displayID;
    public CaptureService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (intent.hasExtra("command")) {
            switch (intent.getStringExtra("command")) {
                case "start":
                    fl = Flinger.getInstance();
                    recorder = new MediaRecorder();
                    recorder.setVideoSource(MediaRecorder.VideoSource.SURFACE);
                    recorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
                    recorder.setOutputFile("/storage/emulated/0/recorden.mp4");
                    recorder.setVideoSize(480,960);
                    recorder.setVideoEncoder(MediaRecorder.VideoEncoder.MPEG_4_SP);
                    recorder.setVideoEncodingBitRate(10000000);
                    recorder.setVideoFrameRate(60);
                    try {
                        recorder.prepare();
                    } catch (IOException e) {
                        throw new RuntimeException("Failed to prepare recorder: " + e.toString());
                    }
                    displayID = fl.addDisplay(recorder.getSurface());
                    recorder.start();
                    break;
                case "stop":
                    recorder.stop();
                    recorder.release();
                    fl.removeDisplay(displayID);
                    Log.i("SurfaceThread","Stoped!");
                    break;
            }
        }
        return START_STICKY;
    }
}