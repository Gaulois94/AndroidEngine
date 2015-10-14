package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Updatable;
import com.gaulois94.Graphics.Materials.Material;
import com.gaulois94.Graphics.Drawable;
import com.gaulois94.Graphics.Font;
import com.gaulois94.Graphics.Color;

public class Text extends Drawable
{
	public Text(long ptr)
	{
		super(ptr);
	}

	public Text(Updatable parent, Material material, Font font, String text)
	{
		super(createText(parent.getPtr(), material.getPtr(), font.getPtr(), text));
	}

	public void setFont(Font font)
	{
		setFontText(m_ptr, font.getPtr());
	}

	public void setText(String text)
	{
		setTextText(m_ptr, text);
	}

	public Font getFont()
	{
		return getFontText(m_ptr);
	}

	public String getText()
	{
		return getTextText(m_ptr);
	}	

	private static native long createText(long parent, long material, long font, String text);
	private native void setTextText(long ptr, String text);
	private native void setFontText(long ptr, long font);

	private native Font getFontText(long ptr);
	private native String getTextText(long ptr);
}
