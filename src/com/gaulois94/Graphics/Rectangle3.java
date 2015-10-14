package com.gaulois94.Graphics;

public class Rectangle3<T extends Number>
{
	public T x;
	public T y;
	public T z;
	public T width;
	public T height;
	public T depth;

	private Class<T> m_modelClass;

	public Rectangle3(Class<T> modelClass)
	{
		this(modelClass, modelClass.cast(0), modelClass.cast(0), modelClass.cast(0), modelClass.cast(0), modelClass.cast(0), modelClass.cast(0));
	}

	public Rectangle3(Class<T> modelClass, T a, T b, T c, T w, T h, T d)
	{
		x      = a;
		y      = b;
		z      = c;
		width  = w;
		height = h;
		depth  = d;
		m_modelClass = modelClass;
	}

	public Class<T> getModelClass()
	{
		return m_modelClass;
	}

	static public <T extends Number, S extends Number> Rectangle3<T> sum(Rectangle3<T> r1, Rectangle3<S> r2)
	{
		Rectangle3<T> r = new Rectangle3<T>(r1.getModelClass());

		r.x = r1.m_modelClass.cast(r1.x.doubleValue() + r2.x.doubleValue());
		r.y = r1.m_modelClass.cast(r1.y.doubleValue() + r2.y.doubleValue());
		r.width = r1.m_modelClass.cast(r1.width.doubleValue() + r2.width.doubleValue());
		r.height = r1.m_modelClass.cast(r1.height.doubleValue() + r2.height.doubleValue());

		return r;
	}
}

