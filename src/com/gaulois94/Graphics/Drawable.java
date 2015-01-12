package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Graphics.Transformable;
import com.gaulois94.Graphics.Renderer;
import com.gaulois94.Graphics.Shader;

import android.content.Context;

public abstract class Drawable extends Transformable
{
	public Drawable(long ptr)
	{
		super(ptr);
	}

	public void draw(Renderer renderer)
	{
		drawDrawable(m_ptr, renderer.getPtr());
		onDraw(renderer);
	}

	public void onDraw(Renderer renderer)
	{
		return;
	}

	public Boolean canDraw()
	{
		return canDrawDrawable(m_ptr) != 0;
	}


	//Functions for manage shaders
	public static void addShader(String key, Shader shader)
	{
		addShaderDrawable(key, shader.getPtr());
	}

	public static Shader getShader(String key)
	{
		long ptr = getShaderDrawable(key);
		return new Shader(ptr);
	}

	public static String getKeyShader(Shader shader)
	{
		return getKeyShaderDrawable(shader.getPtr());
	}

	public static Boolean removeShaderFromKey(String key)
	{
		return removeShaderFromKeyDrawable(key) != 0;
	}

	public static Boolean removeShaderFromShader(Shader shader)
	{
		return removeShaderFromShaderDrawable(shader.getPtr()) != 0;
	}

	public static Boolean existShaderFromKey(String key)
	{
		return existShaderFromKeyDrawable(key) != 0;
	}

	public static void loadShaders()
	{
		loadShadersDrawable(JniMadeOf.context);
	}

	public    static native void   cleanShadersDrawable();
	public    static native int    getNumberOfShadersDrawable();
	protected static native void   addShaderDrawable(String key, long shaderPtr);
	protected static native long   getShaderDrawable(String key);
	protected static native String getKeyShaderDrawable(long shader);
	protected static native int    removeShaderFromKeyDrawable(String key);
	protected static native int    removeShaderFromShaderDrawable(long shader);
	protected static native int    existShaderFromKeyDrawable(String key);
	protected static native void   loadShadersDrawable(Context context);

	protected native void drawDrawable(long ptr, long rendererPtr);
	protected native int canDrawDrawable(long ptr);
}
