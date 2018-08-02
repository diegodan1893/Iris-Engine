varying vec4 color;
varying vec2 texCoord;

uniform sampler2D tex;

void main(void)
{
	/** /
	vec4 myColor = vec4(1.0, 0.0, 0.0, 1.0);

	vec4 c = myColor * color;
	gl_FragColor = 1.0-texture2D(tex, texCoord) * c;
	//*/

	vec3 negativo = 1.0 - texture2D(tex, texCoord).rgb;
	gl_FragColor = vec4(negativo, texture2D(tex, texCoord).a) * color;
}