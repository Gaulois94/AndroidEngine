package com.gaulois94;

import android.content.Context;
import android.content.res.Resources;
import android.content.res.AssetManager;

public class JniMadeOf
{
	public    static Resources res;
    public    static Context context;
	protected long m_ptr;

	public JniMadeOf(long ptr)
	{
		m_ptr = ptr;
		setJobject();
	}

	public long getPtr()
	{
		return m_ptr;
	}

	public void finalize()
	{
		destroyJniMadeOf(m_ptr);
		m_ptr = 0;
	}

	public void setJobject()
	{
		if(m_ptr != 0)
			setJobjectJniMadeOf(m_ptr, this);
	}

	public static void setContext(Context c)
	{
		context = c;
		res = context.getResources();
		initJniMadeOf(c.getAssets(), c, c.getClassLoader());
	}

	protected void setPtr(long ptr)
	{
		m_ptr = ptr;
//		setJobject();
	}

	protected static native void initJniMadeOf(AssetManager asset, Context c, ClassLoader classLoader);
	protected native void destroyJniMadeOf(long ptr);
	protected native void setJobjectJniMadeOf(long ptr, JniMadeOf j);

	static
	{
		System.loadLibrary("engine");
	}
}
