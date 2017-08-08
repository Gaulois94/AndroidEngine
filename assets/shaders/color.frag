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

uniform Clipping uLocalClipping;
uniform Clipping uGlobalClipping;

varying vec2 varyTextureCoord;
varying vec4 varyColor;
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
	

	if(uUseUniColor)
		gl_FragColor   = uUniColor;
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
}
