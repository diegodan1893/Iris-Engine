varying vec4 color;
varying vec2 texCoord;

// The texture we are transitioning to
uniform sampler2D tex;

// The texture we are transitioning from
uniform sampler2D previous;

// A value from 0 to 1 where 0 is the beginning of the transition and 1 the end
uniform float transitionStep;

void main(void)
{
	vec4 from = texture2D(previous, texCoord);
	vec4 to = texture2D(tex, texCoord);

	if (from == to || transitionStep >= 1.0)
	{
		// Same color and alpha, do nothing
		gl_FragColor = to;
	}
	else if (from.a == 0.0 && to.a == 0.0)
	{
		// Fix for Intel Graphics cards
		gl_FragColor = vec4(1.0, 0.0, 0.0, 0.0);
	}
	else if (from.a == 1.0 && to.a == 1.0)
	{
		// Both images are completely opaque
		// Draw the new one on top like we do when fading expressions in
		vec3 resultColor = mix(from.rgb, to.rgb, to.a * transitionStep);
		gl_FragColor = vec4(resultColor, 1.0);
	}
	else
	{
		// Linear crossfade between the two images
		from.a *= 1.0 - transitionStep;
		to.a *= transitionStep;

		vec3 fromColor = from.rgb;
		vec3 toColor = to.rgb;

		float resultAlpha = to.a + from.a * (1.0 - to.a);
		vec3 resultColor = (toColor * to.a + fromColor * from.a * (1.0 - to.a)) / resultAlpha;

		gl_FragColor = vec4(resultColor, resultAlpha);
	}
}