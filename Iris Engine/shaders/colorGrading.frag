varying vec4 color;
varying vec2 texCoord;

// The texture of the image we want to apply color grading to
uniform sampler2D tex;

// The color LUT tables
uniform sampler2D colorLUTfrom;
uniform sampler2D colorLUTto;

// A value from 0 to 1 where 0 is the beginning of the transition and 1 the end
uniform float transitionStep;

// Parameters
uniform bool blendLUTs;

#define MAXCOLOR 15.0
#define COLORS 16.0
#define WIDTH 256.0
#define HEIGHT 16.0

void applyColorGrading(
	in vec2 lutPos_l,
	in vec2 lutPos_h,
	in float cell_fract,
	in sampler2D colorLUT,
	out vec4 gradedColor
)
{
	vec4 gradedColor_l = texture2D(colorLUT, lutPos_l);
	vec4 gradedColor_h = texture2D(colorLUT, lutPos_h);
	gradedColor = mix(gradedColor_l, gradedColor_h, cell_fract);
}

void main(void)
{
	vec4 px = texture2D(tex, texCoord);

	float cell = px.b * MAXCOLOR;
	float cell_l = floor(cell);
	float cell_h = ceil(cell);
	float cell_fract = fract(cell);

	float half_px_x = 0.5 / WIDTH;
	float half_px_y = 0.5 / HEIGHT;

	float offsetX = half_px_x + px.r / COLORS * (MAXCOLOR / COLORS);
	float offsetY = half_px_y + px.g * (MAXCOLOR / COLORS);

	vec2 lutPos_l = vec2(cell_l / COLORS + offsetX, offsetY);
	vec2 lutPos_h = vec2(cell_h / COLORS + offsetX, offsetY);

	vec4 gradedColor;

	if (transitionStep > 0.0)
	{
		// We are in the middle of a transition
		if (blendLUTs)
		{
			// Blend the two color LUTs
			vec4 gradedColorFrom, gradedColorTo;
			applyColorGrading(lutPos_l, lutPos_h, cell_fract, colorLUTfrom, gradedColorFrom);
			applyColorGrading(lutPos_l, lutPos_h, cell_fract, colorLUTto, gradedColorTo);

			gradedColor = mix(gradedColorFrom, gradedColorTo, transitionStep);
		}
		else
		{
			// Blend color LUT with original color
			vec4 gradedColorFrom;
			applyColorGrading(lutPos_l, lutPos_h, cell_fract, colorLUTfrom, gradedColorFrom);

			gradedColor = mix(px, gradedColorFrom, transitionStep);
		}
	}
	else
	{
		applyColorGrading(lutPos_l, lutPos_h, cell_fract, colorLUTfrom, gradedColor);
	}

	gl_FragColor = vec4(gradedColor.rgb, px.a) * color;
}