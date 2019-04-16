#pragma once

#include "WaitCommand.h"

/// <summary>
/// Waits until a video has finished playing
/// </summary>
/// <seealso cref="WaitCommand" />
class WaitForVideo : public WaitCommand
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="WaitForVideo"/> class.
	/// </summary>
	/// <param name="video">The video.</param>
	WaitForVideo(class VideoObject* video);
	
	/// <summary>
	/// Check if the video has finished playing.
	/// </summary>
	/// <returns>
	///   <c>true</c> if the video has finished playing; otherwise, <c>false</c>
	/// </returns>
	bool ready() override;

private:
	class VideoObject* video;
};