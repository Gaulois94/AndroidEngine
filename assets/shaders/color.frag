precision mediump float;

struct Clipping
{
	bool  clip;
	float x;
	float y;
	float width;
	float height;
};

uniform vec4 uMaskColor;

uniform sampler2D uTexture;
uniform bool uUseTexture;
uniform bool uUseUniColor;
uniform vec4 uUniColor;

uniform Clipping uClipping;

varying vec2 varyTextureCoord;
varying vec4 varyColor;
varying vec4 varyModelPosition;

void main()
{
	if(uClipping.clip)
	{
		if(varyModelPosition.x < uClipping.x || varyModelPosition.y < uClipping.y 
		   || varyModelPosition.x > uClipping.x +uClipping.width || varyModelPosition.y > uClipping.y + uClipping.height)
			discard;
	}
	if(uUseUniColor)
		gl_FragColor = uUniColor;
	else
		gl_FragColor = varyColor;

	if(uUseTexture)
	{
		vec4 textColor = texture2D(uTexture, varyTextureCoord);

		if(uMaskColor[3] == 0.0 && textColor[3] == 0.0)
			discard;
		else if(uMaskColor == textColor)
			discard;
	}
};
