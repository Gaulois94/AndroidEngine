package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Graphics.Transformable;
import com.gaulois94.Graphics.Renderer;
import com.gaulois94.Graphics.Shader;
import com.gaulois94.Graphics.Materials.Material;

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

	public void staticToCamera(Boolean s)
	{
		staticToCameraDrawable(m_ptr, s ? 1:0);
	}
	
	public Boolean isStaticToCamera()
	{
		return isStaticToCameraDrawable(m_ptr) != 0;
	}

	public void setMaterial(Material material)
	{
		setMaterialDrawable(m_ptr, material.getPtr());
	}

	public Material getMaterial()
	{
		return new Material(getMaterialDrawable(m_ptr));
	}

	public boolean getTransToChildren()
	{
		return getTransToChildrenDrawable(m_ptr);
	}

	public void setTransToChildren(boolean trans)
	{
		setTransToChildrenDrawable(m_ptr, trans);
	}

	//Functions for managing shaders
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

	public    static native void   cleanShaders();
	public    static native int    getNumberOfShaders();
	protected static native void   addShaderDrawable(String key, long shaderPtr);
	protected static native long   getShaderDrawable(String key);
	protected static native String getKeyShaderDrawable(long shader);
	protected static native int    removeShaderFromKeyDrawable(String key);
	protected static native int    removeShaderFromShaderDrawable(long shader);
	protected static native int    existShaderFromKeyDrawable(String key);
	protected static native void   loadShadersDrawable(Context context);

	protected native void drawDrawable(long ptr, long rendererPtr);

	protected native void    staticToCameraDrawable(long ptr, int s);
	protected native int     isStaticToCameraDrawable(long ptr);
	protected native long    getMaterialDrawable(long ptr);
	protected native void    setMaterialDrawable(long ptr, long materialPtr);
	protected native void    setTransToChildrenDrawable(long ptr, boolean trans);
	protected native boolean getTransToChildrenDrawable(long ptr);
}
