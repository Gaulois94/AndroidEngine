package com.gaulois94.Graphics;

import com.gaulois94.ArrayUtils;

import com.gaulois94.Graphics.Animation;
import com.gaulois94.Updatable;
import com.gaulois94.Graphics.Texture;
import com.gaulois94.Graphics.Materials.Material;
import com.gaulois94.Graphics.Rectangle2i;

public class SelectAnimation extends Animation
{
	public SelectAnimation(Updatable parent, Material material, Texture texture, Rectangle2i[] rect, int nbFrame)
	{
		super(createSelectAnimation(parent.getPtr(), material.getPtr(), texture.getPtr(), ArrayUtils.toPrimitive(Rectangle2.<Integer>rectArraytoArray(rect)), nbFrame));
	}

	private static native long createSelectAnimation(long parent, long material, long texture, int[] rect, int nbFrame);
}
