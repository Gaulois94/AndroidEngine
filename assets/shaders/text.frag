precision mediump float;
varying vec2 varyTextureCoord;
uniform sampler2D uTexture;
uniform vec4 uColor;

void main()
{
	vec4 textColor = texture2D(uTexture, varyTextureCoord);
	if(textColor[3] == 0.0)
		gl_FragColor = textColor;
	else
		gl_FragColor = vec4(uColor);
};
