precision mediump float;

uniform vec4 uMaskColor;

uniform sampler2D uTexture;
uniform bool uUseTexture;
varying vec2 varyTextureCoord;
varying vec4 varyColor;

void main()
{
	if(uUseTexture)
	{
		vec4 textColor = texture2D(uTexture, varyTextureCoord);

		if(uMaskColor[3] == 0.0 && textColor[3] == 0.0)
			discard;
		else if(uMaskColor == textColor)
			discard;
		else
			gl_FragColor = varyColor;
	}

	else
		gl_FragColor = varyColor;
};
