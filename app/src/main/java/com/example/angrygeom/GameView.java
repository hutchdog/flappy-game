package com.example.angrygeom;

import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.annotation.NonNull;

public class GameView extends SurfaceView implements SurfaceHolder.Callback {
    static {
        System.loadLibrary("game");
    }

    private boolean m_nativeStarted = false;

    public GameView(Context context) {
        super(context);
        getHolder().addCallback(this);
    }

    public GameView(Context context, AttributeSet attributeSet) {
        super(context, attributeSet);
        getHolder().addCallback(this);
    }

    public void init() {

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
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        if (m_nativeStarted) {
            applicationDraw();
        }
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder surfaceHolder) {
        if (surfaceHolder.getSurface().isValid()) {
            applicationInit(getContext().getApplicationContext(), surfaceHolder.getSurface());
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

    public native void applicationInit(Context context, Surface surface);

    public native void applicationPause();

    public native void applicationResume();

    public native void applicationDraw();

}
