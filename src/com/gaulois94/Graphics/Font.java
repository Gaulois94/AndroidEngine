package com.gaulois94.test;

import java.lang.Character;
import java.nio.ByteBuffer;
import java.nio.Buffer;
import java.nio.ByteOrder;

import android.util.Log;
import android.opengl.GLES20;

import android.graphics.Bitmap;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.graphics.Paint.FontMetrics;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;
import android.content.Context;
import android.content.res.Resources;
import android.content.res.AssetManager;

import com.gaulois94.test.Texture;
import com.gaulois94.test.Transformable;

public class Font
{
	public static final char CHAR_START         = 32;
	public static final char CHAR_END           = 127;
	public static final char CHAR_UNKNOWN       = 32;
	public static final char CHAR_CR            = 13;
	public static final char CHAR_NL            = 10;
	public static final char CHARACTERS_PER_ROW = 16;

	public static Context context;
	public static Resources res;

	private int[] m_charWidth;
	private int[] m_charHeight;
	private int[] m_charPosX;
	private int[] m_charPosY;

	private int m_maxWidth;
	private int m_maxHeight;
	private int m_padX;
	private int m_padY;
	private Texture m_texture;
	private FontMetrics m_fontMetrics;

	private Font()
	{
		m_charWidth   = new int[CHAR_END-CHAR_START];
		m_charHeight  = new int[CHAR_END-CHAR_START];
		m_charPosX    = new int[CHAR_END-CHAR_START];
		m_charPosY    = new int[CHAR_END-CHAR_START];
		m_maxWidth    = m_maxHeight = 0;
		m_fontMetrics = null;
		m_texture     = null;
	}

	public Texture getTexture()
	{
		return m_texture;
	}

	public float getLineHeight()
	{
		return m_fontMetrics.bottom - m_fontMetrics.top;
	}

	public int[] getPos(char character)
	{
		int characterIndice=0;
		int[] pos = new int[2];
		if(character < CHAR_START || character > CHAR_END)
			characterIndice = CHAR_UNKNOWN - CHAR_START;
		else
			characterIndice = (int) character - CHAR_START;

		pos[0] = m_charPosX[characterIndice];
		pos[1] = m_charPosY[characterIndice] + (int)m_fontMetrics.top; //delete the height up to the baseline

		return pos;
	}

	public int[] getSize(char character)
	{
		int characterIndice=0;
		int[] size = new int[2];
		if(character < CHAR_START || character > CHAR_END)
			characterIndice = CHAR_UNKNOWN - CHAR_START;
		else
			characterIndice = character - CHAR_START;

		size[0] = m_charWidth[characterIndice];
		size[1] = m_charHeight[characterIndice];		

		return size;
	}

	//return the additional space recommended between lines.
	public int getLeading()
	{
		return (int) m_fontMetrics.leading;
	}

	public static Font loadFromFile(String fileName)
	{
		return loadFromFile(fileName, 3, 3, 36);
	}

	public static Font loadFromFile(String fileName, int padX, int padY)
	{
		return loadFromFile(fileName, padX, padY, 36);
	}

	public static Font loadFromFile(String fileName, int padX, int padY, int size)
	{
		//Create a basique font
		Font font   = new Font();
		font.m_padX = padX;
		font.m_padY = padY;
		font.m_maxHeight = 0;
		font.m_maxWidth  = 0;

		//Set the Typeface and the paint.
		Typeface tf = Typeface.createFromAsset(res.getAssets(), fileName);
		Paint paint = new Paint();
		paint.setTypeface(tf);
		paint.setTextSize(size);
		paint.setAntiAlias(true);
		paint.setARGB(0xff, 0xff, 0xff, 0xff); //White color
		FontMetrics fontMetrics = paint.getFontMetrics();
		font.m_fontMetrics = fontMetrics;

		String text        = new String();//text of a row.

		int rowWidth       = 0;
		int posX           = 0;
		int posY           = - (int) fontMetrics.top; // init the Y position for checking with the baseline (top attribute is negative)
		int charHeight     = (int) fontMetrics.bottom - (int) fontMetrics.top;
		char c             = 0;

		for(c=CHAR_START; c < CHAR_END; c++)
		{
			char characterIndice = (char) (c - CHAR_START);
			float[] charWidth = new float[2];
			text += Character.toString(c);

			paint.getTextWidths(Character.toString(c), charWidth);

			//Set the length and the pos of the text for each char
			font.m_charWidth[characterIndice]  = (int) charWidth[0];
			font.m_charHeight[characterIndice] = charHeight;
			font.m_charPosX[characterIndice]   = posX;
			font.m_charPosY[characterIndice]   = posY;

			//Update the current posX and the rowWith
			posX += (int) charWidth[0] + padX;

			//We change line. We have to reinit the variables.
			if((characterIndice + 1)% CHARACTERS_PER_ROW == 0)
			{
				font.m_maxWidth = (font.m_maxWidth < posX) ? posX : font.m_maxWidth; //posX checked with the row width
				rowWidth = 0;

				font.m_maxHeight += charHeight;

				posY += charHeight + font.m_padY;
				posX  = 0;
				text  = "";
			}
		}

		//Update the maxWidth and the maxHeight after the loop if the current row is not finished
		if((CHAR_END - CHAR_START) % CHARACTERS_PER_ROW != 0)
		{
			font.m_maxWidth = (font.m_maxWidth < posX) ? posX : font.m_maxWidth;
			font.m_maxHeight += charHeight;
		}

		font.m_maxHeight += (int) fontMetrics.bottom; //Add the end of an height for a complete Texture height

		//Create the bitmap and the canvas for printing the characters
	    Bitmap bmp = Bitmap.createBitmap(font.m_maxWidth, font.m_maxHeight, Bitmap.Config.ARGB_8888);
		Canvas canvas = new Canvas();
		canvas.setBitmap(bmp);
		canvas.drawARGB(0x00, 0x00, 0x00, 0x00); //fill the bitmap with a transparent color.

		//print each character in his position
		for(c=CHAR_START; c < CHAR_END; c++)
		{
			char characterIndice = (char) (c - CHAR_START);
			canvas.drawText(Character.toString(c), font.m_charPosX[characterIndice], font.m_charPosY[characterIndice], paint);
		}

		//Make the texture
		ByteBuffer buffer = ByteBuffer.allocateDirect(bmp.getByteCount());
		buffer.order(ByteOrder.nativeOrder());
		bmp.copyPixelsToBuffer(buffer);
		buffer.position(0);
		Texture.invertPixels(buffer, bmp.getWidth(), bmp.getHeight());
		buffer.position(0);
		font.m_texture = Texture.loadFromPixels(buffer, bmp.getWidth(), bmp.getHeight(), true);
		bmp.recycle();

		return font;
	}

	public static void setContext(Context c)
	{
		context = c;
		res = context.getResources();
	}
}
