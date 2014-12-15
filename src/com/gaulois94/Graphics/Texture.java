package com.gaulois94.Graphics;

import com.gaulois94.Graphics.Bitmap;

class Texture extends JniMadeOf
{
	private long m_ptr;

	public static Texture createTexture(int width, int height)
	{
		return Texture(initTexture(width, height));
	}

	public static Texture loadFromPixels(float[] pixels, int width, int height, Boolean alpha)
	{
		return Texture(loadFromPixelsTexture(pixels, width, height, alpha));
	}

	public static Texture loadFromBitmap(Bitmap bmp)
	{
		return Texture(loadFromBitmapTexture(bmp.getPtr()));
	}

	public long getID()
	{
		return getIDTexture(m_ptr);
	}

	public void finalize()
	{
		destroyTexture(m_ptr);
	}

	private Texture(long ptr)
	{
		m_ptr = ptr;
	}

	private native long initTexture(int width, int height);
	private native long loadFromPixelsTexture(float[] array, int width, int height, Boolean alpha);
	private native long loadFromBitmapTexture(long bmp);
	private native long getIDTexture(long texture);
	private native void destroyTexture(long texture);
}
