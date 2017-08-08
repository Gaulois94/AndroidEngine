precision mediump float;

struct Clipping
{
	bool  clip;
	float x;
	float y;
	float width;
	float height;
};

#define RGBA 0
#define BW   1

varying vec2 vary_textureCoord;

uniform Clipping uLocalClipping;
uniform Clipping uGlobalClipping;
uniform sampler2D uTexture;
uniform float uOpacity;
uniform int uColorMode;
varying vec4 varyModelPosition;
varying vec4 varyPosition;

void main()
{
	//Do the clipping
	//You have local clipping 
	if(uLocalClipping.clip)
	{
		if(varyModelPosition.x < uLocalClipping.x || varyModelPosition.y < uLocalClipping.y 
		   || varyModelPosition.x > uLocalClipping.x +uLocalClipping.width || varyModelPosition.y > uLocalClipping.y + uLocalClipping.height)
			discard;
	}

	//And global clipping 
	if(uGlobalClipping.clip)
	{
		if(varyPosition.x < uGlobalClipping.x || varyPosition.y < uGlobalClipping.y 
		   || varyPosition.x > uGlobalClipping.x +uGlobalClipping.width || varyPosition.y > uGlobalClipping.y + uGlobalClipping.height)
			discard;
	}

	gl_FragColor = texture2D(uTexture, vary_textureCoord);
	if(uOpacity > 0.0)
		gl_FragColor.a = uOpacity;

	if(uColorMode == BW)
	{
		float intensity = 0.21 * gl_FragColor.r + 0.72 * gl_FragColor.g + 0.07 * gl_FragColor.b;
		gl_FragColor = vec4(intensity, intensity, intensity, gl_FragColor.a);
	}
}
