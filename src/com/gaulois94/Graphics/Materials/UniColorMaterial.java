package com.gaulois94.Graphics.Materials;

import com.gaulois94.Graphics.Materials.Material;
import com.gaulois94.Graphics.Color;

public class UniColorMaterial extends Material
{
	public UniColorMaterial(Color color)
	{
		super(createUniColorMaterial(color.getFloatArray()));
	}

	public void setColor(Color color)
	{
		setColorUniColorMaterial(m_ptr, color.getFloatArray());
	}

	public Color getColor()
	{
		float[] c = getColorUniColorMaterial(m_ptr);
		return Color.fromArray(c);
	}

	private static native long createUniColorMaterial(float[] color);
	private native void setColorUniColorMaterial(long ptr, float[] color);
	private native float[] getColorUniColorMaterial(long ptr);
}
