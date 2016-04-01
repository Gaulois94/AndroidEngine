package com.gaulois94.Graphics;

import com.gaulois94.Graphics.Transformable;
import com.gaulois94.Graphics.Rectangle3f;

public class GroupTransformable extends Transformable
{
	public GroupTransformable(long ptr)
	{
		super(ptr);
	}

	public GroupTransformable(Rectangle3f rect)
	{
        super(createGroupTransformable(new float[]{rect.x, rect.y, rect.z, rect.width, rect.height, rect.depth}));
	}

    public void addTransformable(Transformable t)
    {
        addTransformableGroupTransformable(m_ptr, t.getPtr());
    }

    public void setEnableTransformation(boolean e)
    {
        setEnableTransformationGroupTransformable(m_ptr, e);
    }

    public boolean getEnableTransformation()
    {
        return getEnableTransformationGroupTransformable(m_ptr);
    }

	static native long createGroupTransformable(float[] rect);
	static native void setEnableTransformationGroupTransformable(long ptr, boolean e);
	static native boolean getEnableTransformationGroupTransformable(long ptr);
    static native void addTransformableGroupTransformable(long ptr, long tPtr);
}
