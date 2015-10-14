package com.gaulois94.Graphics;

import com.gaulois94.Graphics.Animation;
import com.gaulois94.Graphics.Vector2i;

public class PatterAnimation extends Animation
{
	public PatternAnimation(Updatable parent, Material material, Texture texture, Vector2i pos, Vector2i pad, Vector2i size, Vector2i n, int nSprite)
	{
		super(createPatternAnimation(parent.getPtr(), material.getPtr(), texture.getPtr(),
					                 new int[]{pos.x, pos.y}, new int[]{pad.x, pad.y}, new int[]{size.x, size.y},
									 new int[]{n.x, n.y}, nSprite));
	}

	private static native long createPattern(long parent, long material, long texture, int[] pos, int[] pad, int[] size, int[] n, nSprite);
}
