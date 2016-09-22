precision mediump float;

struct Clipping
{
	bool  clip;
	float x;
	float y;
	float width;
	float height;
};

varying vec2 vary_textureCoord;

uniform Clipping uClipping;
uniform sampler2D uTexture;
uniform float uOpacity;
varying vec4 varyModelPosition;

void main()
{
	if(uClipping.clip)
	{
		if(varyModelPosition.x < uClipping.x || varyModelPosition.y < uClipping.y 
		   || varyModelPosition.x > uClipping.x +uClipping.width || varyModelPosition.y > uClipping.y + uClipping.height)
			discard;
	}

	gl_FragColor = texture2D(uTexture, vary_textureCoord);
	if(uOpacity > 0.0)
		gl_FragColor.a = uOpacity;
};
