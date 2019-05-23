varying vec4 color;
varying vec2 texCoord;

// Luminance component
uniform sampler2D tex;

// Chroma component
uniform sampler2D chromaTex;

void main(void)
{
	// Constants
	const float yoffset = 16.0 / 255.0;
    const float yexcursion = 219.0 / 255.0;
    const float cboffset = 128.0 / 255.0;
    const float cbexcursion = 224.0 / 255.0;
    const float croffset = 128.0 / 255.0;
    const float crexcursion = 224.0 / 255.0;
    const float kr = 0.299;
    const float kb = 0.114;

    vec4 luma = texture2D(tex, texCoord);
    vec4 chroma = texture2D(chromaTex, texCoord);

    float y = (luma.r - yoffset) / yexcursion;
    float pb = (chroma.r - cboffset) / cbexcursion;
    float pr = (chroma.g - croffset) / crexcursion;

    float r = y + (2.0 * (1.0 - kr) * pr);
    float g = y - ((2.0 * (((1.0 - kb) * kb) / ((1.0 - kb) - kr))) * pb) - ((2.0 * (((1.0 - kr) * kr) / ((1.0 - kb) - kr))) * pr);
    float b = y + (2.0 * (1.0 - kb) * pb);

	gl_FragColor = vec4(r, g, b, 1.0) * color;
}