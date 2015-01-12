package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import android.content.Context;
import java.util.Map;

public class Shader extends JniMadeOf
{
	public Shader(long ptr)
	{
		super(ptr);
	}

	public Shader(int vertexID, int fragID)
	{
		this(loadFromFilesShader(JniMadeOf.context, vertexID, fragID, null, null, null));
	}

	public Shader(int vertexID, int fragID, Map<String, Integer> attribs)
	{
		this(loadFromFilesShader(JniMadeOf.context, vertexID, fragID, attribs, (String[]) attribs.keySet().toArray(), (Integer[]) attribs.values().toArray()));
	}

	public Shader(String vertexCode, String fragCode)
	{
		this(loadFromStringsShader(vertexCode, fragCode, null, null, null));
	}

	public Shader(String vertexCode, String fragCode, Map<String, Integer> attribs)
	{
		this(loadFromStringsShader(vertexCode, fragCode, attribs, (String[]) attribs.keySet().toArray(), (Integer[]) attribs.values().toArray()));
	}

	public int getProgramID()
	{
		return getProgramIDShader(m_ptr);
	}

	public int getVertexID()
	{
		return getVertexIDShader(m_ptr);
	}

	public int getFragID()
	{
		return getFragIDShader(m_ptr);
	}

	private static native long loadFromFilesShader(Context context, int vertexID, int fragID, Map<String, Integer> attribs, String[] keys, Integer[] values);
	private static native long loadFromStringsShader(String vertexCode, String fragCode, Map<String, Integer> attribs, String[] keys, Integer[] values);
	private native int getProgramIDShader(long shader);
	private native int getVertexIDShader(long shader);
	private native int getFragIDShader(long shader);
}
