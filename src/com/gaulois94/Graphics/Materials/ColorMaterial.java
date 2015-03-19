package com.gaulois94.Graphics.Materials;

import com.gaulois94.Graphics.Materials.Material;
import com.gaulois94.Graphics.Color;

public class ColorMaterial extends Material
{
	public ColorMaterial(Color[] color, int nbVertex)
	{
		super(createColorMaterial(Color.getArrayFromColorArray(color), nbVertex));
	}

	public void setColor(Color[] color, int vertex)
	{
		setColorColorMaterial(m_ptr, Color.getArrayFromColorArray(color), vertex);
	}

	public Color[] getColor()
	{
		float[] colors = getColorColorMaterial(m_ptr);
		Color[] result = new Color[colors.length / 4];

		for(int i=0; i < colors.length/4; i++)
		{
			result[i].r = colors[4*i];
			result[i].g = colors[4*i+1];
			result[i].b = colors[4*i+2];
			result[i].a = colors[4*i+3];
		}

		return result;
	}

	public Color getColor(int vertex)
	{
		float[] colors = getColorColorMaterial(m_ptr, vertex);
		return Color.fromArray(colors);
	}

	public int getNbVertex()
	{
		return getNbVertexColorMaterial(m_ptr);
	}

	private static native long createColorMaterial(float[] colors, int nbVertex);
	private native void setColorColorMaterial(long ptr, float[] colors, int nbVertex);
	private native float[] getColorColorMaterial(long ptr);
	private native float[] getColorColorMaterial(long ptr, int vertex);

	private native int getNbVertexColorMaterial(long ptr);
}
