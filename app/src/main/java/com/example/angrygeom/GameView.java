package com.example.angrygeom;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class GameView extends GLSurfaceView  {
    OpenGLRenderer m_openGLRenderer;

    public GameView(Context context) {
        super(context);

        m_openGLRenderer = new OpenGLRenderer();
        setEGLContextClientVersion(2);
        setRenderer(m_openGLRenderer);
    }
}
