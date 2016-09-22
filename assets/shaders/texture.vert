attribute vec3 vPosition;
attribute vec2 vTextureCoord;
uniform mat4 uMVP;
uniform mat4 uModelMoatrix;

varying vec2 vary_textureCoord;
varying vec4 varyModelPosition;

void main()
{
	gl_Position = uMVP * vec4(vPosition, 1.0);
	vary_textureCoord = vTextureCoord;
	varyModelPosition = uModelMoatrix * vec4(vPosition, 1.0);
};
