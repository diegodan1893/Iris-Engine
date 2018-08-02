#pragma once

enum class TransitionType
{
	NONE,

	// In and out transitions
	FADE,

	// Object A to object B transitions
	DISSOLVE,

	// Object A to object B using an image as mask
	IMAGE_DISSOLVE
};