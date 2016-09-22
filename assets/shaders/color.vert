attribute vec3 vPosition;
attribute vec4 vColor;
attribute vec2 vTextureCoord;

uniform mat4 uMVP;
uniform mat4 uCameraMVP;
uniform mat4 uModelMatrix;

varying vec4 varyColor;
varying vec2 varyTextureCoord;
varying vec4 varyModelPosition;

void main()
{
	gl_Position       = uMVP * vec4(vPosition, 1.0);
	varyModelPosition = uModelMatrix * vec4(vPosition, 1.0);
	varyColor         = vColor;
	varyTextureCoord  = vTextureCoord;
};
