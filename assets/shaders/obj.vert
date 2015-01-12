attribute vec3 vPosition;
attribute vec3 vNormal;
varying   vec3 varyNormal;
varying   vec3 varyN;
varying   vec3 varyCameraPos;
uniform   mat4 uInverseMVP;

uniform mat4 uMVP;

void main()
{
	gl_Position = uMVP * vec4(vPosition, 1.0);
	varyNormal = vNormal; 
	varyN = vPosition.xyz;

	varyCameraPos = (uInverseMVP[3] / uInverseMVP[3].w).xyz;
};
