package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Graphics.Vector3f;
import com.gaulois94.Graphics.EulerRotation;
import com.gaulois94.Graphics.SphericCoordinate;

class Transformable implements JniMadeOf
{
	public Transformable()
	{
		m_ptr = createTransformable();
	}

	public void move(Vector3f v)
	{
		float[] m = new float[]{v.x, v.y, v.z};
		moveTransformable(m_ptr, m);
	}

	public void setPosition(Vector3f v)
	{
		float[] p = new float[]{v.x, v.y, v.z};
		setPositionTransformable(m_ptr, p);
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
		float[] p = getPositionTransformable(m_ptr);
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

	public finalize()
	{
		destroyTransformable(m_ptr);
	}

	native long createTransformable();
	native void destroyTransformable(long ptr);
	native void moveTransformable(long ptr, float[] m);
	native void setPositionTransformable(long ptr, float[] p);
	native void rotateTransformable(long ptr, float angle, float[] r);
	native void setRotateTransformable(long ptr, float angle, float[] r);
	native void scaleTransformable(long ptr, float[] s);
	native void setScaleTransformable(long ptr, float[] s);
	native void rotatePhiTransformable(long ptr, float phi);
	native void rotateThetaTransformable(long ptr, float theta);

	native float[] getPositionTransformable(long ptr);
	native float[] getSphericCoordinateTransformable(long ptr);
	native float[] getEulerRotationTransformable(long ptr);

	static
	{
		System.loadLibrary("graphicsEngine");
	} 
}
