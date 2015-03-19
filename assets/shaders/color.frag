precision mediump float;

uniform int uUseColor;
uniform vec4 uColor;
uniform vec4 uMaskColor;

uniform sampler2D uTexture;
uniform bool uUseTexture;
varying vec2 varyTextureCoord;

varying vec4 varyColor;

void main()
{
	vec4 color;

	if(uUseColor != 0)
		color = uColor;
	else
		color = varyColor;

	if(uUseTexture)
	{
		vec4 textColor = texture2D(uTexture, varyTextureCoord);

		if(uMaskColor[3] == 0.0 && textColor[3] == 0.0)
			gl_FragColor = textColor;
		else if(uMaskColor == textColor)
			gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
		else
			gl_FragColor = color;
	}

	else
		gl_FragColor = color;
};
