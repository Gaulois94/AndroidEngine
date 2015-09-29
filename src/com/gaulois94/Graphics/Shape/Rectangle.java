package com.gaulois94.Graphics.Shape;

import com.gaulois94.Graphics.Shape.TriangleShape;
import com.gaulois94.Graphics.Materials.Material;
import com.gaulois94.Graphics.Vector2f;

class Rectangle extends TriangleShape
{
	public Rectangle(Material mtl, Vector2f size)
	{
		super(createRectangle(mtl.getPtr(), size.x, size.y));
	}

	public static native long createRectangle(long mtlPtr, float x, float y);
}
