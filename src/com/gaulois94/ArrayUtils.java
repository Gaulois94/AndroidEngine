package com.gaulois94;

public class ArrayUtils
{
	public static int[] toPrimitive(Integer[] array)
	{
		int[] result = new int[array.length];
		for (int i = 0; i < array.length; i++)
	   	{
			result[i] = array[i].intValue();
		}
		return result;
	}
}
