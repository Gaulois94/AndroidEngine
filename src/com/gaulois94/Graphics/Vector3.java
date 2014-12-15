package com.gaulois94.Graphics;

public class Vector3<T extends Number>
{
	public T x;
	public T y;
	public T z;

	private Class<T> m_modelClass;

	public Vector3(Class<T> modelClass)
	{
		T v = modelClass(0);
		this(modelClass, v, v, v);
	}

	public Vector3(Class<T> modelClass, T a, T b, T c)
	{
		x = a;
		y = b;
		z = c;
		m_modelClass = modelClass;
	}

	public Class<T> getModelClass()
	{
		return m_modelClass;
	}

	static public <T extends Number, S extends Number> Vector3<T> sum(Vector3<T> v1, Vector3<S> v2)
	{
		Vector3<T> v = new Vector3<T>(v1.getModelClass());

		v.x = v1.m_modelClass.cast(v1.x.doubleValue() + v2.x.doubleValue());
		v.y = v1.m_modelClass.cast(v1.y.doubleValue() + v2.y.doubleValue());
		v.z = v1.m_modelClass.cast(v1.z.doubleValue() + v2.z.doubleValue());

		return v;
	}
}
