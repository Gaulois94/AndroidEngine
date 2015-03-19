package com.gaulois94.Graphics.Shape;

import com.gaulois94.Graphics.Shape.TriangleShape;

class Rectangle extends TriangleShape
{
	public Rectangle(Material mtl, Vector2 size)
	{
		super(createRectangle(mtl.getPtr(), size.x, size.y));
	}

	public static native long createRectangle(long mtlPtr, int x, int y);
}
