package com.gaulois94.Graphics;

public class Vector2<T extends Number>
{
	public T x;
	public T y;

	private Class<T> m_modelClass;

	public Vector2(Class<T> modelClass)
	{
		this(modelClass, modelClass.cast(0), modelClass.cast(0));
	}

	public Vector2(Class<T> modelClass, T a, T b)
	{
		x = a;
		y = b;
		m_modelClass = modelClass;
	}

	public Class<T> getModelClass()
	{
		return m_modelClass;
	}

	static public <T extends Number, S extends Number> Vector2<T> sum(Vector2<T> v1, Vector2<S> v2)
	{
		Vector2<T> v = new Vector2<T>(v1.getModelClass());

		v.x = v1.m_modelClass.cast(v1.x.doubleValue() + v2.x.doubleValue());
		v.y = v1.m_modelClass.cast(v1.y.doubleValue() + v2.y.doubleValue());

		return v;
	}
}
