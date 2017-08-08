precision mediump float;

attribute vec3 vPosition;
attribute vec2 vTextureCoord;
uniform mat4 uMVP;
uniform mat4 uModelMatrix;

varying vec2 vary_textureCoord;
varying vec4 varyModelPosition;
varying vec4 varyPosition;

void main()
{
	gl_Position       = uMVP * vec4(vPosition, 1.0);
	varyPosition      = gl_Position;
	vary_textureCoord = vTextureCoord;
	varyModelPosition = vec4(vPosition, 1.0);
}
