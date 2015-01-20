package com.gaulois94.Graphics.Shape;

import com.gaulois94.Graphics.Drawable;
import com.gaulois94.Graphics.Color;
import com.gaulois94.Graphics.Vector3f;
import android.opengl.GLES20;

public class TriangleShape extends Drawable
{
	public TriangleShape(long ptr)
	{
		super(ptr);
	}
	
	//colors may be NULL, uniColor = 0, mode = GL_TRIANGLES by default
	public TriangleShape(Vector3f[] vertexCoords, Color[] colors)
	{
		this(initPtr(vertexCoords, colors, 0, GLES20.GL_TRIANGLES));
	}

	public TriangleShape(Vector3f[] vertexCoords, Color[] colors, int useUniColor)
	{
		this(initPtr(vertexCoords, colors, useUniColor, GLES20.GL_TRIANGLES));
	}

	public TriangleShape(Vector3f[] vertexCoords, Color[] colors, int useUniColor, int mode)
	{
		this(initPtr(vertexCoords, colors, useUniColor, mode));
	}

	public void setVertex(Vector3f[] vertexCoords)
	{
		float[] v = new float[3*vertexCoords.length];

		for(int i=0; i < vertexCoords.length; i++)
		{
			v[3*i + 0] = vertexCoords[i].x;
			v[3*i + 1] = vertexCoords[i].y;
			v[3*i + 2] = vertexCoords[i].z;
		}

		setVertexTriangleShape(m_ptr, v);
	}

	public void setColors(Color[] colors)
	{
		float[] c = new float[4*colors.length];
		for(int i=0; i < colors.length; i++)
		{
			c[4*i + 0] = colors[i].r;
			c[4*i + 1] = colors[i].g;
			c[4*i + 2] = colors[i].b;
			c[4*i + 3] = colors[i].a;
		}

		setColorsTriangleShape(m_ptr, c);
	}

	public void setUniColor(Color uniColor)
	{
		float[] c = new float[4];

		c[0] = uniColor.r;
		c[1] = uniColor.g;
		c[2] = uniColor.b;
		c[3] = uniColor.a;

		setUniColorTriangleShape(m_ptr, c);
	}

	public void useUniColor(int use)
	{
		useUniColorTriangleShape(m_ptr, use);
	}

	public int isUsingUniColor()
	{
		return isUsingUniColorTriangleShape(m_ptr);
	}

	public Color getUniColor()
	{
		float[] c = getUniColorTriangleShape(m_ptr);
		return new Color(c[0], c[1], c[2], c[3]);
	}

	public Color getColor(int vertex)
	{
		float[] c = getColorTriangleShape(m_ptr, vertex);
		return new Color(c[0], c[1], c[2], c[3]);
	}

	public Vector3f getPosition(int vertex)
	{
		float[] v = getPositionTriangleShape(m_ptr, vertex);
		return new Vector3f(v[0], v[1], v[2]);
	}

	private static long initPtr(Vector3f[] vertexCoords, Color[] colors, int useUniColor, int mode)
	{
		float[] v = new float[3*vertexCoords.length];

		for(int i=0; i < vertexCoords.length; i++)
		{
			v[3*i + 0] = vertexCoords[i].x;
			v[3*i + 1] = vertexCoords[i].y;
			v[3*i + 2] = vertexCoords[i].z;
		}

		float[] c=null;

		int colorLength = 1;
		if(useUniColor == 0)
			colorLength = colors.length;

		if(colors != null)
		{
			c = new float[4*colorLength];
		}

		for(int i=0; i < colorLength; i++)
		{
			c[4*i + 0] = colors[i].r;
			c[4*i + 1] = colors[i].g;
			c[4*i + 2] = colors[i].b;
			c[4*i + 3] = colors[i].a;
		}

		return createTriangleShape(v, c, vertexCoords.length, useUniColor, mode);
	}

	private static native long createTriangleShape(float[] vertexCoords, float[] colors, int nbVertex, int useUniColor, int mode);
	private native void setVertexTriangleShape(long ptr, float[] vertexCoords);
	private native void setColorsTriangleShape(long ptr, float[] colors);
	private native void setUniColorTriangleShape(long ptr, float[] color);
	private native void useUniColorTriangleShape(long ptr, int uniColor);

	private native int     isUsingUniColorTriangleShape(long ptr);
	private native float[] getUniColorTriangleShape(long ptr);
	private native float[] getColorTriangleShape(long ptr, int vertex);
	private native float[] getPositionTriangleShape(long ptr, int vertex);
}
