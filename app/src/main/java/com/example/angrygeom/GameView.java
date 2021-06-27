package com.example.angrygeom;

import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.SurfaceView;

public class GameView extends SurfaceView {
    static {
        System.loadLibrary("game");
    }

    public GameView(Context context) {
        super(context);
    }

    public GameView(Context context, AttributeSet attributeSet) {
        super(context, attributeSet);
    }

    public void init() {
        applicationInit(getContext(), this);
    }

    public void onPause() {
        applicationPause();
    }

    public void onResume() {
        applicationResume();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        applicationDraw();
    }

    public native void applicationInit(Context context, GameView view);

    public native void applicationPause();

    public native void applicationResume();

    public native void applicationDraw();

}
