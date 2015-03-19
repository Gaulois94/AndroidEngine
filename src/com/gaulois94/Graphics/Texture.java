package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Graphics.Bitmap;

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

	public long getID()
	{
		return getIDTexture(m_ptr);
	}

	private static native long initTexture(int width, int height);
	private static native long loadFromPixelsTexture(byte[] array, int width, int height, Boolean alpha);
	private static native long loadFromBitmapTexture(long bmp);
	private static native long loadFromFileTexture(String path);
	private native long getIDTexture(long texture);
}
