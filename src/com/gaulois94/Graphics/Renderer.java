package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Graphics.Text;
import com.gaulois94.Graphics.Font;

import android.app.Activity;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.SurfaceHolder;
import android.util.Log;
import android.graphics.Canvas;
import android.graphics.PixelFormat;
import android.graphics.Rect;
import android.opengl.GLES20;
import android.util.Log;

public class Renderer extends SurfaceView implements SurfaceHolder.Callback, Runnable
{
	private Thread m_thread;
	private Boolean m_open;
	private Boolean m_isInit;
	private Boolean m_reInit;
	private long m_ptr;
	private Text m_text;
	private Font m_font;

    public Renderer(Activity activity)
    {
		super(activity);
		JniMadeOf.setContext(activity);
		m_ptr         = 0;
		m_text        = null;
		m_font        = null;
		m_open        = false;
		m_isInit      = false;
		m_reInit      = false;
		m_thread      = null;

		getHolder().addCallback(this);
    }

	public void surfaceChanged(SurfaceHolder holder, int format, int w, int h)
	{
		destroySurfaceRenderer(m_ptr);
		m_isInit = false;
		m_reInit = true;
	}

	public void surfaceCreated(SurfaceHolder holder)
	{
		m_ptr = createRenderer(holder.getSurface());
		Drawable.loadShaders();
		onCreated();
	}

	public void surfaceDestroyed(SurfaceHolder holder)
	{
		destroyRenderer(m_ptr);
		m_ptr = 0;
		m_isInit = false;
		onDestroyed();
	}

	public void onCreated()
	{
		m_font = new Font("fonts/dejavusansmono.ttf");
		float[] color = {1.0f, 0.0f, 0.0f, 1.0f};
		m_text = new Text(m_font, "test", color);
	}

	public void onChanged(Rect rect)
	{
	}

	public void onDestroyed()
	{
	}

	public void run()
	{
		while(m_open)
		{
			if(m_reInit)
			{
				getHolder().setFormat(PixelFormat.RGBA_8888);
				initRenderer(m_ptr, getHolder().getSurface());
		
				m_reInit = false;
				m_isInit = true;
				onChanged(getHolder().getSurfaceFrame());
			}

			if(m_isInit)
				draw();
		}
	}

	public void draw()
	{
		clear();
		m_text.draw(this);
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
		m_ptr = 0;
	}

	public long getPtr()
	{
		return m_ptr;
	}

	private static native long createRenderer(Surface surface);
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
