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

import android.util.DisplayMetrics;
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

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;

public class Renderer extends Render implements SurfaceHolder.Callback, Runnable, SensorEventListener
{
protected SurfaceView m_surface;
protected Thread m_thread;
protected Boolean m_open;
protected Boolean m_isCreated;
protected Boolean m_canCreate;
protected boolean m_suspend;
protected Context m_context;

public Renderer(Context context)
{
	super(0);
	m_context     = context;
	m_canCreate   = false;
	m_open        = false;
	m_thread      = null;
	m_isCreated   = false;
	m_suspend     = false;

	m_surface     = new SurfaceView(context)
	{
		@Override
		public boolean onTouchEvent(MotionEvent e)
		{
			return touchEvent(e);
		}
	};
	m_surface.getHolder().addCallback(this);
	m_surface.getHolder().setFormat(PixelFormat.RGBA_8888);
}

public void surfaceChanged(SurfaceHolder holder, int format, int w, int h)
{
	GLES20.glViewport(0, 0, w, h);
	setViewportRenderer(m_ptr, w, h);
	onChanged(m_surface.getHolder().getSurfaceFrame());
}

public void surfaceCreated(SurfaceHolder holder)
{
	if(holder.getSurface() != null && holder.getSurface().isValid() && holder.getSurfaceFrame().bottom != 0 && holder.getSurfaceFrame().right != 0)
	{
		if(m_isCreated == false)
			m_canCreate = true;
	}
}

//Need to be override if ndk is used
public long createPtr(long parent)
{
	return createRenderer(parent);
}

public void surfaceDestroyed(SurfaceHolder holder)
{
	m_isCreated = false;
	onDestroyed();
}

public void onCreated()
{
}

public void onChanged(Rect rect)
{
}

public void onDestroyed()
{
	destroySurfaceRenderer(m_ptr);
}

public void run()
{
	JniMadeOf.setContext(m_context);
	setPtr(createPtr(0));
	while(m_open)
	{
		//Suspend if needed (on event)
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

		if(m_canCreate)
		{
			initSurfaceRenderer(m_ptr, m_surface.getHolder().getSurface());
			initRenderer(m_ptr);
			onCreated();
			m_isCreated = true;
			m_canCreate = false;
		}

		if(m_isCreated)
			draw();
		}
	}

	public synchronized boolean keyUpEvent(int keyCode)
	{
		return keyUpEventRenderer(m_ptr, keyCode);
	}

	public synchronized boolean keyDownEvent(int keyCode)
	{
		return keyDownEventRenderer(m_ptr, keyCode);
	}

	public synchronized boolean touchEvent(MotionEvent e)
	{
		m_suspend = true;
		int width  = m_surface.getWidth();
		int height = m_surface.getHeight();

		for(int i=0; i < e.getPointerCount(); i++)
		{
			try
			{
				int pID = e.getPointerId(i);

				float x = 2*e.getX(pID) / width - 1;
				//Y are mirrored
				float y = -2*e.getY(pID) / height + 1;

				switch(e.getAction())
				{
					case MotionEvent.ACTION_DOWN:
						onDownTouchRenderer(m_ptr, pID, x, y);
						break;

					case MotionEvent.ACTION_UP:
						onUpTouchRenderer(m_ptr, pID, x, y);
						break;

					case MotionEvent.ACTION_MOVE:
						onMoveTouchRenderer(m_ptr, pID, x, y);
						break;
				}
			}
			catch(IllegalArgumentException exc)
			{}
		}
		m_suspend=false;
		notifyAll();

		return true;
	}

	public synchronized void onSensorChanged(SensorEvent e)
	{
		if(m_ptr == 0)
			return;
		m_suspend = true;
		switch(e.sensor.getType())
		{
			case Sensor.TYPE_ACCELEROMETER:
				accelerometerRenderer(m_ptr, e.values[0], e.values[1], e.values[2]);
				break;
		}
		m_suspend=false;
		notifyAll();
	}

	public void onAccuracyChanged(Sensor e, int accuracy)
	{}

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

	protected native long createRenderer(long parent);
	protected native void initSurfaceRenderer(long renderer, Surface surface);
	protected native void initRenderer(long renderer);
	protected native void destroySurfaceRenderer(long renderer);
	protected native void destroyRenderer(long renderer);
	protected native void clearRenderer(long renderer);
	protected native void displayRenderer(long renderer);
	protected native Boolean hasDisplayRenderer(long renderer);

	protected native void onDownTouchRenderer(long ptr, int pID, float x, float y);
	protected native void onMoveTouchRenderer(long ptr, int pID, float x, float y);
	protected native void onUpTouchRenderer(long ptr, int pID, float x, float y);
	protected native void accelerometerRenderer(long ptr, float x, float y, float z);

	protected native void setViewportRenderer(long ptr, int w, int h);
	protected native boolean keyUpEventRenderer(long ptr, int keyCode);
	protected native boolean keyDownEventRenderer(long ptr, int keyCode);

	static
	{
		System.loadLibrary("engine");
	}
}
