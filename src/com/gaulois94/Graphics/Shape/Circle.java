package com.gaulois94.Graphics.Shape;

import com.gaulois94.Graphics.Color;
import com.gaulois94.Graphics.Shape.TriangleShape;

public class Circle extends TriangleShape
{
	public Circle(Color color)
	{
		this(color, 16);
	}

	public Circle(Color color, int nbEdge)
	{
		super(createCircle(color.getFloatArray(), nbEdge));
	}

	public void setNbEdge(int nbEdge)
	{
		setNbEdgeCircle(m_ptr, nbEdge);
	}

	public int getNbEdge()
	{
		return getNbEdgeCircle(m_ptr);
	}

	private static native long createCircle(float[] colors, int nbEdge);
	private native void setNbEdgeCircle(long ptr, int nbEdge);
	private native int  getNbEdgeCircle(long ptr);
}
