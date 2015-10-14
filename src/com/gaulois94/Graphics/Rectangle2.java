package com.gaulois94.Graphics;

public class Rectangle2<T extends Number>
{
	public T x;
	public T y;
	public T width;
	public T height;

	private Class<T> m_modelClass;

	public Rectangle2(Class<T> modelClass)
	{
		this(modelClass, modelClass.cast(0), modelClass.cast(0), modelClass.cast(0), modelClass.cast(0));
	}

	public Rectangle2(Class<T> modelClass, T a, T b, T w, T h)
	{
		x      = a;
		y      = b;
		width  = w;
		height = h;
		m_modelClass = modelClass;
	}

	public Class<T> getModelClass()
	{
		return m_modelClass;
	}

	static public <T extends Number, S extends Number> Rectangle2<T> sum(Rectangle2<T> r1, Rectangle2<S> r2)
	{
		Rectangle2<T> v = new Rectangle2<T>(v1.getModelClass());

		r.x = r1.m_modelClass.cast(r1.x.doubleValue() + r2.x.doubleValue());
		r.y = r1.m_modelClass.cast(r1.y.doubleValue() + r2.y.doubleValue());
		r.width = r1.m_modelClass.cast(r1.width.doubleValue() + r2.width.doubleValue());
		r.height = r1.m_modelClass.cast(r1.height.doubleValue() + r2.height.doubleValue());

		return v;
	}

	static public <T extends Number> T[] rectArraytoArray(Rectangle2<T>[] r)
	{
		T[] result = new T[4*r.length];
		for(int i=0; i < r.length; r++)
		{
			result[4*i]   = r[i].x;
			result[4*i+1] = r[i].y;
			result[4*i+2] = r[i].width;
			result[4*i+3] = r[i].height;
		}

		return result;
	}
}

