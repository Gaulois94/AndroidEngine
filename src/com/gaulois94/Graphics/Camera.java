package com.gaulois94.Graphics;

import com.gaulois94.Graphics.Transformable;
import com.gaulois94.Graphics.Vector3f;

public class Camera extends Transformable
{
	public Camera(long ptr)
	{
		super(ptr);
	}

	public Camera()
	{
		this(createCamera());
	}

	public Vector3f getPosition()
	{
		float[] pos = getPositionCamera(m_ptr);
		return new Vector3f(pos[0], pos[1], pos[2]);
	}

	public void setPosition(Vector3f position)
	{
		float[] p = {position.x, position.y, position.z};
		setPositionCamera(m_ptr, p);
	}

	public void setOrientation(Vector3f orientation)
	{
		float[] o = {orientation.x, orientation.y, orientation.z};
		setOrientationCamera(m_ptr, o);
	}

	public void lookAt(Vector3f position, Vector3f target)
	{
		float[] p = {position.x, position.y, position.z};
		float[] t = {target.x, target.y, target.z};
		lookAtCamera(m_ptr, p, t);
	}

	protected static native long createCamera();
	protected native float[] getPositionCamera(long ptr);
	protected native void lookAtCamera(long ptr, float[] position, float[] target);
	protected native void setPositionCamera(long ptr, float[] position);
	protected native void setOrientationCamera(long ptr, float[] orientation);
}
