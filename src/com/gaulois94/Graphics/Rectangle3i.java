package com.gaulois94.Graphics;
import com.gaulois94.Graphics.Rectangle3;

public class Rectangle3i extends Rectangle3<Integer>
{
	public Rectangle3i()
	{
		super(Integer.class);
	}

	public Rectangle3i(int a, int b, int c, int w, int h, int d)
	{
		super(Integer.class, a, b, c, w, h, d);
	}
}
