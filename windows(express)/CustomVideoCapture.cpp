#include "CustomVideoCapture.h"
#include "QtCore"

bool CustomVideoCapturer::mVideoCaptureRunning = false;

void CustomVideoCapturer::onStart(ZegoPublishChannel channel)
{
	Q_UNUSED(channel)
		if (!mVideoCaptureRunning)
		{
			mVideoCaptureRunning = true;
		}
}

void CustomVideoCapturer::onStop(ZegoPublishChannel channel)
{
	Q_UNUSED(channel)
		if (mVideoCaptureRunning)
		{
			mVideoCaptureRunning = false;
		}
}
