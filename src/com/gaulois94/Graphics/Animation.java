package com.gaulois94.Graphics;

import com.gaulois94.Graphics.Sprite;

public abstract class Animation extends Sprite
{
	public void setSubNSpriteCoords(int n)
	{
		setSubNSpriteCoordsAnimation(m_ptr, n);
	}

	public void setInAnimation(int n, int reset)
	{
		setInAnimationAnimation(m_ptr, n, reset);
	}

	public void setInAnimation(int n)
	{
		setInAnimation(n, -1);
	}

	public boolean inAnimation()
	{
		return inAnimationAnimation(m_ptr);
	}

	protected native void    setInAnimationAnimation(long ptr, int n, int reset);
	protected native boolean inAnimationAnimation(long ptr);
}
