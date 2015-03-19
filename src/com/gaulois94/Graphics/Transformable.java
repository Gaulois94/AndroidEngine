package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Graphics.Vector3f;
import com.gaulois94.Graphics.EulerRotation;
import com.gaulois94.Graphics.SphericCoordinate;

class Transformable extends JniMadeOf
{
	public Transformable(long ptr)
	{
		super(ptr);
	}

	public Transformable()
	{
		this(createTransformable());
	}

	public void move(Vector3f v)
	{
		float[] m = new float[]{v.x, v.y, v.z};
		moveTransformable(m_ptr, m);
	}

	public void setPosition(Vector3f v)
	{
		setPosition(v, 0);
	}

	public void setPosition(Vector3f v, int useScale)
	{
		float[] p = new float[]{v.x, v.y, v.z};
		setPositionTransformable(m_ptr, p, useScale);
	}

	public void rotate(float angle, Vector3f v)
	{
		float[] r = new float[]{v.x, v.y, v.z};
		rotateTransformable(m_ptr, angle, r);
	}

	public void setRotate(float angle, Vector3f v)
	{
		float[] r = new float[]{v.x, v.y, v.z};
		setRotateTransformable(m_ptr, angle, r);
	}

	public void scale(Vector3f v)
	{
		float[] s = new float[]{v.x, v.y, v.z};
		scaleTransformable(m_ptr, s);
	}

	public void setScale(Vector3f v)
	{
		float[] s = new float[] {v.x, v.y, v.z};
		setScaleTransformable(m_ptr, s);
	}

	public void setSphericCoordinate(float r, float theta, float phi)
	{
		setSphericCoordinateTransformable(m_ptr, r, theta, phi);
	}

	public void rotatePhi(float phi)
	{
		rotatePhiTransformable(m_ptr, phi);
	}

	public void rotateTheta(float theta)
	{
		rotateThetaTransformable(m_ptr, theta);
	}

	public Vector3f getPosition()
	{
		return getPosition(0);
	}

	public Vector3f getPosition(int useScale)
	{
		float[] p = getPositionTransformable(m_ptr, useScale);
		Vector3f v = new Vector3f(p[0], p[1], p[2]);

		return v;
	}

	public SphericCoordinate getSphericCoordinate()
	{
		float[] s = getSphericCoordinateTransformable(m_ptr);
		SphericCoordinate v = new SphericCoordinate(s[0], s[1], s[2]);

		return v;
	}

	public EulerRotation getEulerRotation()
	{
		float[] e = getEulerRotationTransformable(m_ptr);
		EulerRotation v = new EulerRotation(e[0], e[1], e[2]);

		return v;
	}

	protected static native long createTransformable();

	protected native void moveTransformable(long ptr, float[] m);
	protected native void setPositionTransformable(long ptr, float[] p, int setScale);

	protected native void rotateTransformable(long ptr, float angle, float[] r);
	protected native void setRotateTransformable(long ptr, float angle, float[] r);

	protected native void scaleTransformable(long ptr, float[] s);
	protected native void setScaleTransformable(long ptr, float[] s);

	protected native void rotatePhiTransformable(long ptr, float phi);
	protected native void rotateThetaTransformable(long ptr, float theta);

	protected native void setSphericCoordinateTransformable(long ptr, float r, float theta, float phi);

	protected native float[] getPositionTransformable(long ptr, int useScale);
	protected native float[] getSphericCoordinateTransformable(long ptr);
	protected native float[] getEulerRotationTransformable(long ptr);
}
