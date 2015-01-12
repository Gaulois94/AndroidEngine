precision mediump float;
varying vec3 varyNormal;
varying vec3 varyN;
varying vec3 varyCameraPos;

uniform vec3 uAmbientColor;
uniform vec3 uDiffuseColor;
uniform vec3 uSpecularColor;
uniform float uTransparent;
uniform float uSpecularHighlight;

void main()
{
	highp vec3 L  = normalize(vec3(0.0, 2.0, 2.0)); /*Light Position*/
	highp vec3 N  = normalize(varyNormal);
	highp vec3 V  = normalize(varyN);
	highp vec3 directionLight  = normalize(L-V);
	highp vec3 directionCamera = normalize(varyCameraPos-V);
	highp float intensity = 1.3;

	highp float df = max(0.0, dot(N, directionLight));
	highp float sf = 0.0;
	if(df > 0.0)
		sf = pow(max(0.0, dot(directionCamera, reflect(-directionLight, N))), uSpecularHighlight/100.0);
	highp float distance = length(L-V);
	highp vec3 Ip  = (uAmbientColor * uDiffuseColor + uDiffuseColor * df + uSpecularColor * sf)/pow(distance, 2.0)*intensity;;

	gl_FragColor = vec4(Ip, uTransparent);
};
