package com.gaulois94.Graphics;

import android.app.Activity;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.SurfaceHolder;
import android.util.Log;
import android.graphics.Canvas;
import android.graphics.PixelFormat;
import android.opengl.GLES20;

public class Renderer extends SurfaceView implements SurfaceHolder.Callback, Runnable, JniMadeOf
{
	private Thread m_thread;
	private Boolean m_open;
	private Boolean m_isInit;
	private Boolean m_reInit;

    public Renderer(Activity activity)
    {
		super(activity);
		m_open      = false;
		m_isInit    = false;
		m_reInit    = false;
		m_ptr  = createRenderer();
		m_thread    = null;

		getHolder().addCallback(this);
    }

	public void surfaceChanged(SurfaceHolder holder, int format, int w, int h)
	{
		m_isInit = false;
		m_reInit = true;
	}

	public void surfaceCreated(SurfaceHolder holder)
	{
	}

	public void surfaceDestroyed(SurfaceHolder holder)
	{
		m_isInit = false;
	}

	public void run()
	{
		while(m_open)
		{
			if(m_reInit)
			{
				destroySurfaceRenderer(m_ptr);
				getHolder().setFormat(PixelFormat.RGBA_8888);
				initRenderer(m_ptr, getHolder().getSurface());

				m_reInit = false;
				m_isInit = true;
			}

			if(m_isInit)
			{
				draw();
			}
		}
	}

	public void draw()
	{
		clear();
		display();
	}

	public void clear()
	{
		clearRenderer(m_ptr);
	}

	public void display()
	{
		displayRenderer(m_ptr);
	}

	public void resume()
	{
		m_open = true;
		m_thread = new Thread(this);
		m_thread.start();
	}

	public void pause()
	{
		m_open = false;
	}

	public void destroy()
	{
		destroyRenderer(m_ptr);
	}

	private native long createRenderer();
	private native void initRenderer(long renderer, Surface surface);
	private native void destroySurfaceRenderer(long renderer);
	private native void destroyRenderer(long renderer);
	private native void clearRenderer(long renderer);
	private native void displayRenderer(long renderer);
	private native Boolean hasDisplayRenderer(long renderer);

	static
	{
		System.loadLibrary("graphicsEngine");
	} 
}
