package com.gaulois94.Graphics;
import com.gaulois94.JniMadeOf;

public class Bitmap extends JniMadeOf
{
	public Bitmap(long ptr)
	{
		super(ptr);
	}

	public Bitmap(android.graphics.Bitmap bmp)
	{
		this(createBitmap(bmp));
	}

	public void invertPixels()
	{
		invertPixelsBitmap(m_ptr);
	}

	private static native long createBitmap(android.graphics.Bitmap bitmap);
	native void invertPixelsBitmap(long ptr);

	static
	{
		System.loadLibrary("graphicsEngine");
	} 
}
