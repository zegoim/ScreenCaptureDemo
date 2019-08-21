#pragma once

#include <QObject>
#include <QRect>
#include <QVector>
#include "RoomDefines.h"
#include "LiveRoom-Publisher.h"
#include "LiveRoomCallback.h"
#include "LiveRoomCallback-Publisher.h"
#include "zego-screencapture-defines.h"

class ZegoScreenCaptureSettings;
class ZegoExternalCaptureFactory;

class ZegoScreenCaptureController :
	public QObject,
	public ZEGO::LIVEROOM::ILivePublisherCallback
{
	Q_OBJECT

public:
	ZegoScreenCaptureController(QObject *parent = Q_NULLPTR);
	~ZegoScreenCaptureController(void);

	ZegoScreenCaptureSettings* settings(void) const { return m_settings; }

protected:
	void init(void);
	void uninit(void);

	// av callback
	void OnPublishStateUpdate(int stateCode, const char* pszStreamID, const ZEGO::COMMON::ZegoPublishingStreamInfo& oStreamInfo);
	void OnPublishQulityUpdate(const char* pszStreamID, int quality, double videoFPS, double videoKBS);

	// screen capture callback
// 	void OnCapturedFrameAvailable(const char* data, int length, 
// 		const ZEGO::ScreenCapture::VideoCaptureFormat& frame_format,
// 		unsigned long long reference_time, unsigned int reference_time_scale) override;
// 	void OnCapturedWindowMoved(void* winId, int x, int y, int w, int h) override;
// 	void OnCaptureError(int nErrorCode) override;
	static void OnCaptureError(enum ZegoScreenCaptureCaptureError error, void *user_data);
	static void OnCapturedWindowMoved(void *handle, int left, int top, int width, int height, void *user_data);
	static void OnCapturedFrameAvailable(const char *data, uint32_t length, const struct ZegoScreenCaptureVideoCaptureFormat *video_frame_format, uint64_t reference_time, uint32_t reference_time_scale, void *user_data);
	static void OnCaptureWindowChange(ZegoScreenCaptureWindowStatus status_code, ZegoWindowHandle handle, ZegoRect rect, void *user_data);
protected slots :
	void onUiTargetChanged(int target);
	void onUiScreenRefreshRequested(void);
	void onUiScreenSelectChanged(const QString& name);
	void onUiWindowRefreshRequested(void);
	void onUiWindowSelectChanged(qint64 id);
	void onUiRectangleChanged(QRect geometry);
	void onUiResolutionSelectChanged(QSize resolution);
	void onUiBitrateChanged(int bitrate);
	void onUiFramerateChanged(int framerate);
	void onUiCursorToggled(bool checked);
	void onUiClickAnimationToggled(bool checked);
	void onUiCaptureRequested(int curState);
	void onUiPublishRequested(int curState);
	void OnUiAddExcludedWindowRequested(void);
	void OnUiRemoveExcludedWindowRequested(void);
	void OnUiThumbnailWindowCapture(qint64 id);

private:
	void initAV(void);
	void initScreenCapture(void);
	void bindSettings(void);

	Q_SIGNAL void captureStateChanged_p(int state);
	Q_SLOT void onCaptureStateChanged_p(int state);
	Q_SIGNAL void publishStateChanged_p(int state);
	Q_SLOT void onPublishStateChanged_p(int state);

	ZegoScreenCaptureSettings* m_settings = nullptr;
	ZegoExternalCaptureFactory* m_externalCaptureFactory = nullptr;
	QString m_userId;
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
	// unused av callback
	void OnPlayStateUpdate(const char* pszUserID, const char* pszChannelID, int eState, const char* pszStreamID) {};
	void OnPlayQulityUpdate(const char* pszStreamID, ZEGO::AV::PlayQuality pq) {};
	void OnVideoSizeChanged(const char* pStreamID, int nWidth, int nHeight) {};
	void OnRenderSnapshot(void *pImage, int nChannelIdx) {};
	void OnAuxCallback(unsigned char *pData, int *pDataLen, int *pSampleRate, int *pNumChannels) {};
	void OnAVEngineStop() {};
};
