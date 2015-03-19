package com.gaulois94.Graphics;
import com.gaulois94.Graphics.Vector3;

public class Vector3f extends Vector3<Float>
{
	public Vector3f()
	{
		super(Float.class);
	}

	public Vector3f(float a, float b, float c)
	{
		super(Float.class, a, b, c);
	}

	static public float[] getArrayFromVertexArray(Vector3f[] vector)
	{
		float[] v = new float[3*vector.length];
		for(int i=0; i < vector.length; i++)
		{
			v[3*i + 0] = vector[i].x;
			v[3*i + 1] = vector[i].y;
			v[3*i + 2] = vector[i].z;
		}

		return v;
	}
}

