package com.gaulois94.Graphics;

import com.gaulois94.Updatable;
import com.gaulois94.Graphics.Drawable;
import android.opengl.Matrix;

public abstract class Render extends Updatable
{
	public void draw(Drawable drawable, float[] transMat)
	{
		drawRender(m_ptr, drawable.getPtr(), transMat);
	}

	public void draw(Drawable drawable)
	{
		float[] m = new float[16];
		Matrix.setIdentityM(m, 0);
		drawRender(m_ptr, drawable.getPtr(), m);
	}

	public void display()
	{
		displayRender(m_ptr);
	}

	public void initDraw()
	{
		initDrawRender(m_ptr);
	}

	public void stopDraw()
	{
		stopDrawRender(m_ptr);
	}

	public void clear()
	{
		clearRender(m_ptr);
	}

	public Camera getCamera()
	{
		return getCameraRender(m_ptr);
	}

	public Color getAmbientColor()
	{
		return Color.fromArray(getAmbientColorRender(m_ptr));
	}

	public Rectangle3f getRectOnScreen(Transformable transformable)
	{
		float[] rect = getRectOnScreenRender(m_ptr, transformable.getPtr());
		return new Rectangle3f(rect[0], rect[1], rect[2], rect[3], rect[4], rect[5]);
	}

	public Vector2f getPositionOnScreen(Vector2f pos)
	{
		float[] p = getPositionOnScreenRender(m_ptr, new float[]{pos.x, pos.y});
		return new Vector2f(p[0], p[1]);
	}

	protected native void drawRender(long ptr, long drawable, float[] trans);
	protected native void displayRender(long ptr);
	protected native void initDrawRender(long ptr);
	protected native void stopDrawRender(long ptr);
	protected native void clearRender(long ptr);
	protected native Camera getCameraRender(long ptr);
	protected native float[] getAmbientColorRender(long ptr);
	protected native float[] getRectOnScreenRender(long ptr, long transf);
	protected native float[] getPositionOnScreenRender(long ptr, float[] vec);
}
