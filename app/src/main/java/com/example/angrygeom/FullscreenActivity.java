package com.example.angrygeom;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class FullscreenActivity extends AppCompatActivity {

    private GameView m_gameView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.hide();
        }

        setContentView(R.layout.activity_fullscreen);
        m_gameView = findViewById(R.id.gameView);
        m_gameView.init();
    }

    @Override
    protected void onPostCreate(Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);
    }

    @Override
    protected void onPause() {
        super.onPause();
        m_gameView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        m_gameView.onResume();
    }

}