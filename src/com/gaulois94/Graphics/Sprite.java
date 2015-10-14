package com.gaulois94.Graphics;

import com.gaulois94.Graphics.Drawable;
import com.gaulois94.Graphics.Texture;
import com.gaulois94.Graphics.Materials.Material;
import com.gaulois94.Updatable;

import android.graphics.RectF;

public class Sprite extends Drawable
{
	public Sprite(UPdatable parent, Material material, Texture texture)
	{
		super(createSprite(parent.getPtr(), material.getPtr(), texture.getPtr()));
	}

	public Texture getTexture()
	{
		return getTextureSprite(m_ptr);
	}

	public RectF getSubTextureRect()
	{
		float[] rect = getSubTextureRectSprite(m_ptr);
		return new RectF(rect[0], rect[1] + rect[3], rect[0] + rect[2], rect[1]);
	}

	public void setTexture(Texture texture, int resetSubTextureRect)
	{
		setTextureSprite(m_ptr, texture.getPtr(), resetSubTextureRect);
	}

	public void setTexture(Texture texture)
	{
		setTextureSprite(m_ptr, texture.getPtr(), 1);
	}

	public void setSubTextureRect(RectF rect)
	{
		float[] r = new float[]{rect.bottom, rect.left, rect.top - rect.bottom, rect.right - rect.left};
		setSubTextureRectSprite(m_ptr, r);
	}

	public static native long createSprite(long parent, long material, long texturePtr);
	public native jobject getTextureSprite(long ptr);
	public native float[] getSubTextureRectSprite(long ptr);
	public native void setTextureSprite(long ptr, long texturePtr, int resetSubTextureRect);
	public native void setSubTextureRectSprite(long ptr, float[] rectCoords);
}
