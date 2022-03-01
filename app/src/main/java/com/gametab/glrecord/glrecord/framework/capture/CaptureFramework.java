package com.gametab.glrecord.glrecord.framework.capture;

import android.content.Intent;

import com.gametab.glrecord.glrecord.Flinger;

public class CaptureFramework {
    private Flinger fl;
    public CaptureFramework() {
        fl = Flinger.getInstance();
    }
    public void startRecord() {
        Intent i = new Intent(fl.getContext(),CaptureService.class);
        i.putExtra("command","start");
        fl.getContext().startService(i);
    }
    public void stopRecord() {
        Intent i = new Intent(fl.getContext(),CaptureService.class);
        i.putExtra("command","stop");
        fl.getContext().startService(i);
    }
}
