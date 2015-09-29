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
	private TriangleShape m_triangleShape;
	private Circle m_circle;
	private Sprite m_sprite;
	private Boolean m_isCreated;
	private int m_nbEdge;

    public Renderer(Activity activity)
    {
		super(activity);
		JniMadeOf.setContext(activity);
		m_ptr         = 0;
		m_text        = null;
		m_font        = null;
		m_triangleShape = null;
		m_circle      = null;
		m_sprite      = null;
		m_open        = false;
		m_isInit      = false;
		m_reInit      = false;
		m_thread      = null;
		m_isCreated   = false;
		m_nbEdge      = 3;

		getHolder().addCallback(this);
    }

	public void surfaceChanged(SurfaceHolder holder, int format, int w, int h)
	{
		onChanged(getHolder().getSurfaceFrame());
	}

	public void surfaceCreated(SurfaceHolder holder)
	{
		if(m_isCreated == false)
		{
			m_isCreated = true;
			m_ptr = createRenderer(holder.getSurface());
			Drawable.loadShaders();
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
		Color[] color = new Color[]{new Color(1.0f, 0.0f, 0.0f, 1.0f)};
		Vector3f[] v = new Vector3f[]{new Vector3f(0.0f, 1.0f, 0.0f), new Vector3f(-1.0f, 0.0f, 0.0f), new Vector3f(1.0f, 0.0f, 0.0f), new Vector3f(0.0f, -1.0f, 0.0f), new Vector3f(1.0f, 0.0f, 0.0f), new Vector3f(-1.0f, 0.0f, 0.0f)};
		UniColorMaterial material = new UniColorMaterial(color[0]);

//		m_triangleShape = new TriangleShape(material, v);
//		m_font          = new Font("fonts/dejavusansmono.ttf", 3, 3, 126);
//		m_text          = new Text(m_font, "Text", color[0]);
		m_circle        = new Circle(material, 0.5f, 16);
//		m_sprite        = new Sprite(m_font.getTexture());
//		m_sprite.setScale(new Vector3f(2.0f, 2.0f, 1.0f));
//		m_sprite.setPosition(new Vector3f(-0.5f, -0.5f, 0.0f));
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
		while(m_open)
		{
			if(m_reInit)
			{
				getHolder().setFormat(PixelFormat.RGBA_8888);
				initRenderer(m_ptr, getHolder().getSurface());
		
				m_reInit = false;
				m_isInit = true;
			}

			if(m_isInit)
				draw();
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
		m_ptr = 0;
	}

	public void finalize()
	{
		destroyRenderer(m_ptr);
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
