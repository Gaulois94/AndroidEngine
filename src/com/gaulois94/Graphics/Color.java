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

	public float[] getFloatArray()
	{
		float[] c = new float[4];
		c[0] = r;
		c[1] = g;
		c[2] = b;
		c[3] = a;

		return c;
	}

	public static float[] getArrayFromColorArray(Color[] colors)
	{
		float[] c = new float[4*colors.length];
		for(int i=0; i < colors.length; i++)
		{
			c[4*i + 0] = colors[i].r;
			c[4*i + 1] = colors[i].g;
			c[4*i + 2] = colors[i].b;
			c[4*i + 3] = colors[i].a;
		}

		return c;
	}

	public static Color fromArray(float[] array)
	{
		return new Color(array[0], array[1], array[2], array[3]);
	}
}
