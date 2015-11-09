package com.gaulois94;

import com.gaulois94.Graphics.Renderer;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;

import android.util.Log;
import android.hardware.SensorManager;
import android.hardware.Sensor;

public class Main extends Activity
{
	private SensorManager m_sensorManager;
    private Sensor m_accelerometer;
	private Renderer m_renderer;

	public Main()
	{
	}

	public void onCreate(Bundle savedInstanceState)
	{
        m_sensorManager = (SensorManager)getSystemService(Context.SENSOR_SERVICE); 
		m_accelerometer = m_sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		m_renderer = new Renderer(this);
		setContentView(m_renderer.getSurface());
		super.onCreate(savedInstanceState);
	}

	public void onResume()
	{
		super.onResume();
		setContentView(m_renderer.getSurface());
		m_renderer.resume();
		m_sensorManager.registerListener(m_renderer, m_accelerometer, SensorManager.SENSOR_DELAY_NORMAL);
	}

	public void onPause()
	{
		super.onPause();
		m_sensorManager.unregisterListener(m_renderer);
		m_renderer.pause();
	}

	public void onDestroy()
	{
		super.onDestroy();
		m_renderer.destroy();
	}
}
