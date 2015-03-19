package com.gaulois94.Graphics.Shape;

import com.gaulois94.Graphics.Color;
import com.gaulois94.Graphics.Vector3f;
import com.gaulois94.Graphics.Shape.TriangleShape;
import com.gaulois94.Graphics.Materials.Material;

public class Circle extends TriangleShape
{
	public Circle(Material material)
	{
		this(material, 1.0f);
	}

	public Circle(Material material, float radius)
	{
		this(material, radius, 16);
	}

	public Circle(Material material, float radius, int nbEdge)
	{
		super(createCircle(material.getPtr(), radius, nbEdge));
	}

	public void setNbEdge(int nbEdge)
	{
		setNbEdgeCircle(m_ptr, nbEdge);
	}

	public Vector3f getCenter()
	{
		float[] c = getCenterCircle(m_ptr);
		return new Vector3f(c[0], c[1], c[2]);
	}

	public int getNbEdge()
	{
		return getNbEdgeCircle(m_ptr);
	}

	private static native long createCircle(long material, float radius, int nbEdge);
	private native void setNbEdgeCircle(long ptr, int nbEdge);
	private native float[] getCenterCircle(long ptr);
	private native int  getNbEdgeCircle(long ptr);
}
