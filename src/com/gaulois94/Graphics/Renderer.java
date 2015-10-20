package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Graphics.Text;
import com.gaulois94.Graphics.Font;
import com.gaulois94.Graphics.Color;
import com.gaulois94.Graphics.Vector3f;
import com.gaulois94.Graphics.Shape.TriangleShape;
import com.gaulois94.Graphics.Shape.Circle;
import com.gaulois94.Graphics.Sprite;
import com.gaulois94.Graphics.Materials.UniColorMaterial;
import com.gaulois94.Graphics.PatternAnimation;

import android.content.Context;

import android.app.Activity;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.SurfaceHolder;
import android.view.MotionEvent;
import android.util.Log;
import android.graphics.Canvas;
import android.graphics.PixelFormat;
import android.graphics.Rect;
import android.opengl.GLES20;
import android.util.Log;

public class Renderer extends Render implements SurfaceHolder.Callback, Runnable
{
	private SurfaceView m_surface;
	private Thread m_thread;
	private Boolean m_open;
	private Boolean m_isInit;
	private Boolean m_reInit;
	private Boolean m_isCreated;
	private boolean m_suspend;
	private Text m_text;
	private Font m_font;
	private UniColorMaterial m_mtl;

    public Renderer(Context context)
    {
		super(0);
		JniMadeOf.setContext(context);
		m_open        = false;
		m_isInit      = false;
		m_reInit      = false;
		m_thread      = null;
		m_isCreated   = false;
		m_suspend     = false;

		m_surface     = new SurfaceView(context)
	   	{
			@Override
			public boolean onTouchEvent(MotionEvent e)
			{
				touchEvent(e);
				return false;
			}
		};
		m_surface.getHolder().addCallback(this);
    }

	public void surfaceChanged(SurfaceHolder holder, int format, int w, int h)
	{
		onChanged(m_surface.getHolder().getSurfaceFrame());
	}

	public void surfaceCreated(SurfaceHolder holder)
	{
		if(m_isCreated == false)
		{
			m_isCreated = true;
			setPtr(createRenderer(0, holder.getSurface()));
			Drawable.loadShaders();
			initRenderer(m_ptr);
			onCreated();
		}
		m_isInit = false;
		m_reInit = true;
	}

	public void surfaceDestroyed(SurfaceHolder holder)
	{
		m_isInit = false;
		onDestroyed();
	}

	public void onCreated()
	{
		m_mtl  = new UniColorMaterial(new Color(1.0f, 0.0f, 0.0f, 1.0f));
		m_font = new Font("fonts/dejavusansmono.ttf");
		m_text = new Text(this, m_mtl, m_font, "AMj!}y");
	}

	public void onChanged(Rect rect)
	{
		GLES20.glViewport(0, 0, rect.right-rect.left, rect.bottom-rect.top);
	}

	public void onDestroyed()
	{
		destroySurfaceRenderer(m_ptr);
	}

	public void run()
	{
		try
		{
			if(m_suspend)
			{
				synchronized(this)
				{
					while(m_suspend)
						wait();
				}
			}
		}catch(InterruptedException e){}
		while(m_open)
		{
			if(m_reInit)
			{
				m_surface.getHolder().setFormat(PixelFormat.RGBA_8888);
				initSurfaceRenderer(m_ptr, m_surface.getHolder().getSurface());
		
				m_reInit = false;
				m_isInit = true;
			}

			if(m_isInit)
				draw();
		}
	}

	public void touchEvent(MotionEvent e)
	{
		m_suspend = true;
		int width  = m_surface.getWidth();
		int height = m_surface.getHeight();

		float x = 2*e.getX() / width - 1;
		//Y are mirrored
		float y = -2*e.getY() / height + 1;
		Log.e("Main", "X : " + Float.toString(x) + " Y : " + Float.toString(y));

		switch(e.getFlags())
		{
			case MotionEvent.ACTION_DOWN:
				onDownTouchRenderer(m_ptr, x, y);
				break;

			case MotionEvent.ACTION_CANCEL:
				onUpTouchRenderer(m_ptr, x, y);
				break;

			case MotionEvent.ACTION_MOVE:
				onMoveTouchRenderer(m_ptr, x, y);
				break;
		}
		m_suspend=false;
	}

	public void draw()
	{
		clear();
		update(this);
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

	public void finalize()
	{
		destroyRenderer(m_ptr);
	}

	public SurfaceView getSurface()
	{
		return m_surface;
	}

	private native long createRenderer(long parent, Surface surface);
	private native void initSurfaceRenderer(long renderer, Surface surface);
	private native void initRenderer(long renderer);
	private native void destroySurfaceRenderer(long renderer);
	private native void destroyRenderer(long renderer);
	private native void clearRenderer(long renderer);
	private native void displayRenderer(long renderer);
	private native Boolean hasDisplayRenderer(long renderer);

	private native void onDownTouchRenderer(long ptr, float x, float y);
	private native void onMoveTouchRenderer(long ptr, float x, float y);
	private native void onUpTouchRenderer(long ptr, float x, float y);

	static
	{
		System.loadLibrary("engine");
	}
}
