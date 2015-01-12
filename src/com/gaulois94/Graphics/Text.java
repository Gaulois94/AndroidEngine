package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Graphics.Drawable;
import com.gaulois94.Graphics.Font;

public class Text extends Drawable
{
	public Text(long ptr)
	{
		super(ptr);
	}

	public Text(Font font, String text, float[] color)
	{
		super(createText(font.getPtr(), text, color));
	}

	public void setFont(Font font)
	{
		setFontText(m_ptr, font.getPtr());
	}

	public void setText(String text)
	{
		setTextText(m_ptr, text);
	}

	public void setColor(Vector3f color)
	{
		float[] c = {color.x, color.y, color.z};
		setColorText(m_ptr, c);
	}

	private static native long createText(long font, String text, float[] color);
	private native void setTextText(long ptr, String text);
	private native void setColorText(long ptr, float[] color);
	private native void setFontText(long ptr, long font);
}
