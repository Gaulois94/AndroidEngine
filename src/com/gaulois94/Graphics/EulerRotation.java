package com.gaulois94.Graphics;

class EulerRotation
{
	public float roll;
	public float pitch;
	public float yaw;

	public EulerRotation()
	{
		this(0, 0, 0);
	}

	public EulerRotation(float r, float p, float y)
	{
		roll   = r;
		pitch  = p;
		yaw    = y;
	}
}
