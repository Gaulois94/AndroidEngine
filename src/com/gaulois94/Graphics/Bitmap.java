package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;

public class Bitmap implements JniMadeOf
{
	private static android.graphics.Bitmap AndroidBitmap = null;

	Bitmap(AndroidBitmap bitmap)
	{
		m_ptr = createBitmap(bitmap);
	}

	static void invertPixels()
	{
		invertPixelsBitmap(m_ptr);
	}

	native long createBitmap(AndroidBitmap bitmap);
}
