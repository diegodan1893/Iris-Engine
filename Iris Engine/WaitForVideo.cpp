#include "WaitForVideo.h"
#include "VideoObject.h"

WaitForVideo::WaitForVideo(VideoObject* video)
	:video(video)
{
}

bool WaitForVideo::ready()
{
	return !video->isPlaying();
}
