package com.gaulois94.Graphics.Materials;

import com.gaulois94.Graphics.Renderer;
import com.gaulois94.Graphics.Texture;
import com.gaulois94.Graphics.Shader;
import com.gaulois94.JniMadeOf;

public class Material extends JniMadeOf
{
	public Material(long ptr)
	{
		super(ptr);
	}

	public void enableShader()
	{
		enableShaderMaterial(m_ptr);
	}

	public void init(Renderer renderer)
	{
		initMaterial(m_ptr, renderer.getPtr());
	}

	public void bindTexture(Texture texture)
	{
		bindTextureMaterial(m_ptr, texture.getPtr());
	}

	public void unbindTexture()
	{
		unbindTextureMaterial(m_ptr);
	}

	public void disableShader()
	{
		disableShaderMaterial(m_ptr);
	}

	public Shader getShader()
	{
		return new Shader(getShaderMaterial(m_ptr));
	}

	private native void initMaterial(long ptr, long rendererPtr);
	private native void enableShaderMaterial(long ptr);
	private native void bindTextureMaterial(long ptr, long texture);
	private native void unbindTextureMaterial(long ptr);
	private native void disableShaderMaterial(long ptr);
	private native long getShaderMaterial(long ptr);
}
