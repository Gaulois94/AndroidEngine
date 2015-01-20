package com.gaulois94.Graphics;

public class Color
{
	public float r;
	public float g;
	public float b;
	public float a;

	public Color(float red, float green, float blue, float alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	
	public Color(Color copy)
	{
		this(copy.r, copy.g, copy.b, copy.a);
	}
}
