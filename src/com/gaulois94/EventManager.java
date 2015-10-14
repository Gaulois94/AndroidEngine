package com.gaulois94;

import com.gaulois94.Graphics.Rectangle2f;
import com.gaulois94.Graphics.Rectangle3f;
import com.gaulois94.TouchCoord;

public class EventManager
{
	static public boolean touchInScreen(Rectangle2f rect2)
	{
		float r = new float[4];
		r[0] = rect2.x;
		r[1] = rect2.y;
		r[2] = rect2.width;
		r[3] = rect2.height;

		return touchInScreenEventManager(r, 2);
	}

	static public boolean touchInScreen(Rectangle3f rect3)
	{
		float r = new float[4];
		r[0] = rect3.x;
		r[1] = rect3.y;
		r[2] = rect3.z;
		r[3] = rect3.width;
		r[4] = rect3.height;
		r[5] = rect3.depth;

		return touchInScreenEventManager(r, 3);
	}

	static public TouchCoord getTouchCoord()
	{
		TouchCoord touchCoord = new TouchCoord();
		getTouchCoordEventManager(touchCoord);
		return touchCoord;
	}

	static private native boolean touchInScreenEventManager(float[] rect, int mode);
	static private native void    getTouchCoordEventManager(TouchCoord tc);
}
