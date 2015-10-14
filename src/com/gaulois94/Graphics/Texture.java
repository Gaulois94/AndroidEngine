package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Graphics.Bitmap;
import com.gaulois94.Graphics.Color;
import com.gaulois94.Graphics.Rectangle2f;
import com.gaulois94.Graphics.Vector2i;
import com.gaulois94.Graphics.Vector2f;

public class Texture extends JniMadeOf
{
	public Texture(long ptr)
	{
		super(ptr);
	}

	public Texture(int width, int height)
	{
		this(initTexture(width, height));
	}

	public Texture(byte[] pixels, int width, int height, Boolean alpha)
	{
		this(loadFromPixelsTexture(pixels, width, height, alpha));
	}

	public Texture(Bitmap bmp)
	{
		this(loadFromBitmapTexture(bmp.getPtr()));
	}

	public Texture(String path)
	{
		this(loadFromFileTexture(path));
	}

	public void setMaskColor(Color color)
	{
		setMaskColorTexture(m_ptr, color.getFloatArray());
	}

	public Color getMaskColor()
	{
		return Color.fromArray(getMaskColortTexture(m_ptr));
	}

	public Vector2f pixelsToTextureCoord(Vector2f p)
	{
		float[] v = pixelsToTextureCoordTexture(m_ptr, new float[]{p.x, p.y});
		return new Vector2f(v[0], v[1]);
	}	

	public Rectangle2f getRect(Vector2i pos, Vector2i size)
	{
		float[] r = getRectTexture(m_ptr, new int[]{pos.x, pos.y}, new int[]{size.x, size.y});
		return new Rectangle2f(r[0], r[1], r[2], r[3]);
	}

	public Rectangle2f getRect(Rectangle2i rect)
	{
		float[] r = getRectTexture(m_ptr, new int[]{rect.x, rect.y, rect.width, rect.height});
		return new Rectangle2f(r[0], r[1], r[2], r[3]);
	}

	public int getHeight()
	{
		return getHeightTexture(m_ptr);
	}

	public int getWidth()
	{
		return getWidthTexture(m_ptr);
	}

	public long getID()
	{
		return getIDTexture(m_ptr);
	}

	private static native long initTexture(int width, int height);
	private static native long loadFromPixelsTexture(byte[] array, int width, int height, Boolean alpha);
	private static native long loadFromBitmapTexture(long bmp);
	private static native long loadFromFileTexture(String path);
	private native void setMaskColorTexture(long texture, float[] color);
	private native long getIDTexture(long texture);
	private native int getWidthTexture(long texture);
	private native int getHeightTexture(long texture);
	private native float[] getMaskColortTexture(long texture);
	private native float[] getRectTexture(long texture, float[] pos, float[] size);
	private native float[] getRectTexture(long texture, float[] rect);
	private native float[] pixelsToTextureCoordTexture(long texture, float[] pos);
}
