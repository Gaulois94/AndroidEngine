package com.gaulois94.Graphics;

import com.gaulois94.Graphics.Animation;
import com.gaulois94.Graphics.Vector2i;
import com.gaulois94.Updatable;
import com.gaulois94.Graphics.Materials.Material;
import com.gaulois94.Graphics.Texture;

public class PatternAnimation extends Animation
{
	public PatternAnimation(Updatable parent, Material material, Texture texture, Vector2i pos, Vector2i pad, Vector2i size, int nX, int nSprite, int nbFrame)
	{
		super(createPatternAnimation(parent.getPtr(), material.getPtr(), texture.getPtr(),
					                 new int[]{pos.x, pos.y}, new int[]{pad.x, pad.y}, new int[]{size.x, size.y},
									 nX, nSprite, nbFrame));
	}

	private static native long createPatternAnimation(long parent, long material, long texture, int[] pos, int[] pad, int[] size, int nX, int nSprite, int nbFrame);
}
