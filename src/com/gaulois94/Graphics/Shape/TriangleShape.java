package com.gaulois94.Graphics.Shape;

import com.gaulois94.Graphics.Drawable;
import com.gaulois94.Graphics.Color;
import com.gaulois94.Graphics.Vector3f;
import com.gaulois94.Graphics.Materials.Material;
import android.opengl.GLES20;
import android.util.Log;

public class TriangleShape extends Drawable
{
	public TriangleShape(long ptr)
	{
		super(ptr);
	}
	
	//colors may be NULL, uniColor = 0, mode = GL_TRIANGLES by default
	public TriangleShape(Material material, Vector3f[] vertexCoords)
	{
		this(initPtr(material, vertexCoords, GLES20.GL_TRIANGLES));
	}

	public TriangleShape(Material material, Vector3f[] vertexCoords, int mode)
	{
		this(initPtr(material, vertexCoords, mode));
	}

	public void setVertex(Vector3f[] vertexCoords)
	{
		setVertexTriangleShape(m_ptr, Vector3f.getArrayFromVertexArray(vertexCoords));
	}

	public Vector3f getPositionVertex(int vertex)
	{
		float[] v = getPositionVertexTriangleShape(m_ptr, vertex);
		return new Vector3f(v[0], v[1], v[2]);
	}

	private static long initPtr(Material material, Vector3f[] vertexCoords, int mode)
	{
		float[] v = Vector3f.getArrayFromVertexArray(vertexCoords);

		return createTriangleShape(material.getPtr(), v, vertexCoords.length, mode);
	}

	private static native long createTriangleShape(long ptr, float[] vertexCoords, int nbVertex, int mode);
	private native void setVertexTriangleShape(long ptr, float[] vertexCoords);

	private native float[] getPositionVertexTriangleShape(long ptr, int vertex);
}
