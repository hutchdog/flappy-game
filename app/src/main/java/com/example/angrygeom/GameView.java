package com.example.angrygeom;

import android.content.Context;
import android.graphics.Canvas;
import android.opengl.GLSurfaceView;

public class GameView extends GLSurfaceView  {
    static {
        System.loadLibrary("game");
    }

    OpenGLRenderer m_openGLRenderer;

    public GameView(Context context) {
        super(context);

        m_openGLRenderer = new OpenGLRenderer();
        setEGLContextClientVersion(2);
        setRenderer(m_openGLRenderer);

        applicationInit();
    }

    @Override
    public void onPause() {
        super.onPause();
        applicationPause();
    }

    @Override
    public void onResume() {
        super.onResume();
        applicationResume();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        applicationDraw();
    }

    public native void applicationInit();
    public native void applicationPause();
    public native void applicationResume();
    public native void applicationDraw();

}
