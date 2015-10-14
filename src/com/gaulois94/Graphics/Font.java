package com.gaulois94.Graphics;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Graphics.Vector2i;
import com.gaulois94.Graphics.Texture;

import java.lang.Character;

import android.util.Log;

import android.graphics.Bitmap;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.graphics.Paint.FontMetrics;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;

import android.content.Context;

public class Font extends JniMadeOf
{
	public static final char CHAR_START         = 32;
	public static final char CHAR_END           = 127;
	public static final char CHAR_UNKNOWN       = 32;
	public static final char CHAR_CR            = 13;
	public static final char CHAR_NL            = 10;
	public static final char CHARACTERS_PER_ROW = 16;

	public Font(long ptr)
	{
		super(ptr);
	}

	public Font(String fileName)
	{
		this(fileName, 3, 3, 36);
	}

	public Font(String fileName, int padX, int padY)
	{
		this(fileName, padX, padY, 36);
	}

	public Font(String fileName, int padX, int padY, int size)
	{
		this(initPtr(fileName, padX, padY, size));
	}

	public Texture getTexture()
	{
		return getTextureFont(m_ptr);
	}

	//return the height of lines for this font
	public float getLineHeight()
	{
		return getLineHeightFont(m_ptr);
	}

	//return the position of a character in pixels on the Texture
	public Vector2i getPos(char character)
	{
		int[] pos = getPosFont(m_ptr, character);
		return new Vector2i(pos[0], pos[1]);
	}

	//return the size of a character in pixels on the Texture
	public Vector2i getSize(char character)
	{
		int[] size = getSizeFont(m_ptr, character);
		return new Vector2i(size[0], size[1]);
	}

	//return the font metrics
	public FontMetrics getFontMetrics()
	{
		return getFontMetricsFont(m_ptr);
	}

	static private long initPtr(String fileName, int padX, int padY, int size)
	{
		//Data's for the font
		int[] charWidth   = new int[CHAR_END-CHAR_START];
		int[] charHeight  = new int[CHAR_END-CHAR_START];
		int[] charPosX    = new int[CHAR_END-CHAR_START];
		int[] charPosY    = new int[CHAR_END-CHAR_START];
		int maxWidth      = 0;
		int maxHeight     = 0;

		//Set the Typeface and the paint.
		Typeface tf = Typeface.createFromAsset(JniMadeOf.res.getAssets(), fileName);
		Paint paint = new Paint();
		paint.setTypeface(tf);
		paint.setTextSize(size);
		paint.setAntiAlias(true);
		paint.setARGB(0xff, 0xff, 0xff, 0xff); //White color

		FontMetrics fontMetrics = paint.getFontMetrics();

		String text        = new String();//text of a row.

		int rowWidth       = 0;
		int posX           = 0;
		int posY           = - (int) fontMetrics.top; // init the Y position for checking with the baseline (top attribute is negative)
		int heightLine     = (int) fontMetrics.bottom - (int) fontMetrics.top;
		char c             = 0;

		//Get all the size and position of characters
		for(c=CHAR_START; c < CHAR_END; c++)
		{
			char characterIndice = (char) (c - CHAR_START);
			float[] widthLine = new float[2];
			text += Character.toString(c);

			paint.getTextWidths(Character.toString(c), widthLine);

			//Set the length and the pos of the text for each char
			charWidth[characterIndice]  = (int) widthLine[0];
			charHeight[characterIndice] = heightLine;
			charPosX[characterIndice]   = posX;
			charPosY[characterIndice]   = posY;

			//Update the current posX and the rowWith
			posX += (int) widthLine[0] + padX;

			//We change line. We have to reinit the variables.
			if((characterIndice + 1) % CHARACTERS_PER_ROW == 0)
			{
				maxWidth = (maxWidth < posX) ? posX : maxWidth; //posX checked with the row width
				rowWidth = 0;
				maxHeight += heightLine;

				posY += heightLine + padY;
				posX  = 0;
				text  = "";
			}
		}

		//Update the maxWidth and the maxHeight after the loop if the current row is not finished
		if((CHAR_END - CHAR_START) % CHARACTERS_PER_ROW != 0)
		{
			maxWidth = (maxWidth < posX) ? posX : maxWidth;
			maxHeight += heightLine;
		}

		maxHeight += (int) fontMetrics.bottom; //Add the end of a line for a complete Texture height

		//Create the bitmap and the canvas for printing the characters
	    Bitmap bmp = Bitmap.createBitmap(maxWidth, maxHeight, Bitmap.Config.ARGB_8888);
		Canvas canvas = new Canvas();
		canvas.setBitmap(bmp);
		canvas.drawARGB(0x00, 0x00, 0x00, 0x00); //fill the bitmap with a transparent color.

		//print each character in his position
		for(c=CHAR_START; c < CHAR_END; c++)
		{
			char characterIndice = (char) (c - CHAR_START);
			canvas.drawText(Character.toString(c), charPosX[characterIndice], charPosY[characterIndice], paint);
		}

		//Make the texture
		long ptr = loadFromFileFont(bmp, charWidth, charHeight, charPosX, charPosY, maxWidth, maxHeight, padX, padY, fontMetrics);

		return ptr;
	}

	private static native long loadFromFileFont(Bitmap bmp, int[] width, int[] height, int[] posX, int[] posY, int maxWidth, int maxHeight, int padX, int padY, FontMetrics fontMetrics);
	private native float       getLineHeightFont(long ptr);
	private native int[]       getPosFont(long ptr, char character);
	private native int[]       getSizeFont(long ptr, char character);
	private native int         getLeadingFont(long ptr);
	private native Texture     getTextureFont(long ptr);
	private native FontMetrics getFontMetricsFont(long ptr);

}
