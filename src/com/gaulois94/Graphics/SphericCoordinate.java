package com.gaulois94.Graphics;

public class SphericCoordinate
{
	public float radius;
	public float theta;
	public float phi;

	public SphericCoordinate()
	{
		this(0, 0, 0);
	}

	public SphericCoordinate(float r, float t, float p)
	{
		radius = r;
		theta  = t;
		phi    = p;
	}
}
