#pragma once
//#include "ZegoCustomVideoSourceContext.h"
#include "ZegoExpressSDK.h"
using namespace ZEGO::EXPRESS;

struct ZegoCustomVideoFrame
{
	std::unique_ptr<unsigned char[]> data;
	unsigned int dataLength = 0;
	ZEGO::EXPRESS::ZegoVideoFrameParam param;
	unsigned long long referenceTimeMillsecond = 0;
};

class CustomVideoCapturer : public IZegoCustomVideoCaptureHandler/*, public ZegoCustomVideoSourceContext*/ {

public:
	void onStart(ZegoPublishChannel channel) override;
	void onStop(ZegoPublishChannel channel) override;
	static bool mVideoCaptureRunning;
};