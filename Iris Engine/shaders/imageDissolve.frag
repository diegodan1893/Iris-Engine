varying vec4 color;
varying vec2 texCoord;

// The texture of the background
uniform sampler2D tex;

// The mask that will be used for the transition
uniform sampler2D maskImage;

// A value from 0 to 1 where 0 is the beginning of the transition and 1 the end
uniform float transitionStep;

void main(void)
{
	vec4 background = texture2D(tex, texCoord);
	float mask = texture2D(maskImage, texCoord).r;

	/**
	 * At transitionStep=0:
	 *
	 *      0 [---------------------] 1   Color of the transition image
	 *  1 [---] 0                         Corresponding alpha at that transitionStep
	 *  b  len  t                         b=bottom, len=length, t=top
	 *
	 *
	 * At transitionStep=0.5:
	 *
	 *      0 [-----------|---------] 1
	 *                1 [---] 0
	 *
	 *
	 * At transitionStep=1:
	 *
	 *      0 [---------------------] 1
	 *                            1 [---] 0
	 */
	float length = 0.3;
	float top = transitionStep + length * transitionStep;
	float bottom = transitionStep - length * (1.0 - transitionStep);
	float resultAlpha;

	resultAlpha = 1.0 - (mask - bottom) / (top - bottom);
	resultAlpha = clamp(resultAlpha, 0.0, 1.0);
	
	gl_FragColor = vec4(background.rgb, resultAlpha);
}