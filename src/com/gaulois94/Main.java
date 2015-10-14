package com.gaulois94;

import com.gaulois94.Graphics.Renderer;
import com.gaulois94.EventManager;

import android.app.Activity;
import android.os.Bundle;

import android.view.Surface;
import android.view.SurfaceView;
import android.view.SurfaceHolder;

import android.util.Log;
import android.opengl.GLES20;

public class Main extends Activity
{
	private Renderer m_renderer;

	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		m_renderer = new Renderer(this);
		setContentView(m_renderer.getSurface());
	}

	public void onResume()
	{
		super.onResume();
		m_renderer.resume();
	}

	public void onPause()
	{
		super.onPause();
		m_renderer.pause();
	}

	public void onDestroy()
	{
		super.onDestroy();
		m_renderer.destroy();
	}
}
