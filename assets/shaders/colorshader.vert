attribute vec3 vPosition;
attribute vec4 vColor;
uniform mat4 uMVP;

varying vec4 vary_color;

void main()
{
	gl_Position = uMVP * vec4(vPosition, 1.0);
	vary_color = vColor;
};
