package com.example.angrygeom;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

import androidx.annotation.NonNull;

public class GameView extends SurfaceView implements SurfaceHolder.Callback, View.OnTouchListener {
    static {
        System.loadLibrary("game");
    }

    private boolean m_nativeStarted = false;

    private Runnable m_updateTicker = new Runnable() {
        public void run() {
            update();
            postDelayed(m_updateTicker, 16);
        }
    };

    public GameView(Context context) {
        super(context);
        getHolder().addCallback(this);
        setOnTouchListener(this);
    }

    public GameView(Context context, AttributeSet attributeSet) {
        super(context, attributeSet);
        getHolder().addCallback(this);
        setOnTouchListener(this);
    }

    public void init() {

    }

    public void update() {
        if (m_nativeStarted) {
            applicationDraw();
        }
    }

    public void onPause() {
        if (m_nativeStarted) {
            applicationPause();
        }
    }

    public void onResume() {
        if (m_nativeStarted) {
            applicationResume();
        }
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder surfaceHolder) {
        if (surfaceHolder.getSurface().isValid()) {
            applicationInit(getContext().getApplicationContext(), surfaceHolder.getSurface());
            post(m_updateTicker);

            m_nativeStarted = true;
        }
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder surfaceHolder, int i, int i1, int i2) {
        if (surfaceHolder.getSurface().isValid()) {

        }
    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder surfaceHolder) {
        if (surfaceHolder.getSurface().isValid()) {

        }
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        applicationOnTouch();
        return true;
    }

    public native void applicationInit(Context context, Surface surface);

    public native void applicationPause();

    public native void applicationResume();

    public native void applicationDraw();

    public native void applicationOnTouch();
}
