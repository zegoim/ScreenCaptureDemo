#ifndef ZEGOCUSTOMVIDEOSOURCECONTEXT_H
#define ZEGOCUSTOMVIDEOSOURCECONTEXT_H

//#include "ZegoCustomVideoSourceBase.h"
//#include "ZegoCustomVideoSourceImage.h"
//#include "ZegoCustomVideoSourceMedia.h"

class ZegoCustomVideoSourceContext
{
public:
    ZegoCustomVideoSourceContext();
    ~ZegoCustomVideoSourceContext();

    void getVideoFrame(std::shared_ptr<ZegoCustomVideoFrame> & videoFrame) ;
    ZegoCustomVideoSourceBase *getVideoSource(ZegoCustomVideoSourceType sourceType);

private:
    std::mutex mVideoSouceMutex;
    ZegoCustomVideoSourceBase *currentVideoSource = nullptr;
};

#endif // ZEGOCUSTOMVIDEOSOURCECONTEXT_H
