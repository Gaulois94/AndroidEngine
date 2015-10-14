package com.gaulois94;

import android.content.Context;
import android.content.res.Resources;

public class JniMadeOf
{
	public    static Resources res;
    public    static Context context;
	protected long m_ptr;

	public JniMadeOf(long ptr)
	{
		m_ptr = ptr;
		setJobject(this);
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

	public void setJobject(JniMadeOf j)
	{
		setJobjectJniMadeOf(j, m_ptr);
	}

	public static void setContext(Context c)
	{
		context = c;
		res = context.getResources();
	}

	protected native void destroyJniMadeOf(long ptr);
	protected native void setJobjectJniMadeOf(JniMadeOf j, long ptr);

	static
	{
		System.loadLibrary("engine");
	}
}
