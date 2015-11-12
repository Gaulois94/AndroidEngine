package com.gaulois94;

import com.gaulois94.JniMadeOf;
import com.gaulois94.Graphics.Render;
import com.gaulois94.Graphics.Render;

public class Updatable extends JniMadeOf
{
	public Updatable(long ptr)
	{
		super(ptr);
	}

	public Updatable(Updatable parent)
	{
		this(createUpdatable(parent.getPtr()));
	}

	public Updatable()
	{
		this(createUpdatable(0));
	}

	public void updateFocus(int pID, Render render)
	{
		updateFocusUpdatable(m_ptr, pID, render.getPtr());
	}

	public void onFocus(int pID, Render render)
	{
		onFocusUpdatable(m_ptr, pID, render.getPtr());
	}

	public void update(Render render)
	{
		updateUpdatable(m_ptr, render.getPtr());
	}

	public void onUpdate(Render render)
	{
		onUpdateUpdatable(m_ptr, render.getPtr());
	}

	public void addChild(Updatable child)
	{
		addChildUpdatable(m_ptr, child.getPtr(), -1);
	}

	public void addChild(Updatable child, int pos)
	{
		addChildUpdatable(m_ptr, child.getPtr(), pos);
	}

	public void setParent(Updatable parent)
	{
		setParentUpdatable(m_ptr, parent.getPtr(), -1);
	}

	public void setParent(Updatable parent, int pos)
	{
		setParentUpdatable(m_ptr, parent.getPtr(), pos);
	}

	public boolean removeChild(Updatable child)
	{
		return removeChildUpdatable(m_ptr, child.getPtr());
	}

	public boolean removeChild(Updatable child, int pos)
	{
		return removeChildPosUpdatable(m_ptr, pos);
	}

	public boolean isChild(Updatable child)
	{
		return isChildUpdatable(m_ptr, child.getPtr());
	}

	public Updatable getParent()
	{
		return getParentUpdatable(m_ptr);
	}

	protected static native long      createUpdatable(long parent);
	protected native void      updateFocusUpdatable(long ptr, int pID, long render);
	protected native void      onFocusUpdatable(long ptr, int pID, long render);
	protected native void      updateUpdatable(long ptr, long render);
	protected native void      onUpdateUpdatable(long ptr, long render);
	protected native void      addChildUpdatable(long ptr, long child, int pos);
	protected native void      setParentUpdatable(long ptr, long parent, int pos);
	protected native boolean   removeChildUpdatable(long ptr, long child);
	protected native boolean   removeChildPosUpdatable(long ptr, int pos);
	protected native boolean   isChildUpdatable(long ptr, long child);
	protected native Updatable getParentUpdatable(long ptr);
}
