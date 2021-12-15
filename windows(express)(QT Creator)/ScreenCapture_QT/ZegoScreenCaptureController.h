#pragma once

#include <QObject>
#include <QRect>
#include <QVector>
#include "zego-screencapture-defines.h"
#include "ZegoExpressEventHandler.h"
#include "CustomVideoCapture.h"
#include "ZegoCaptureView.h"

class ZegoScreenCaptureSettings;
class ZegoExternalCaptureFactory;

class ZegoScreenCaptureController :
	public QObject,
	public ZEGO::EXPRESS::IZegoEventHandler
{
	Q_OBJECT

public:
	ZegoScreenCaptureController(QObject *parent = Q_NULLPTR);
	~ZegoScreenCaptureController(void);
	ZegoCaptureView	 *m_CaptureView;

	ZegoScreenCaptureSettings* settings(void) const { return m_settings; }

protected:
	void init(void);
	void uninit(void);

	//longjuncai重写IZegoEventHandler的推流状态消息回调函数->onPublisherStateUpdate
	void onPublisherStateUpdate(const std::string& streamID, ZEGO::EXPRESS::ZegoPublisherState state, int errorCode, const std::string& extendedData);
	//longjuncai重写IZegoEventHandler的质量消息回调函数->onPublisherQualityUpdate
	void onPublisherQualityUpdate(const std::string& streamID, const ZEGO::EXPRESS::ZegoPublishStreamQuality& quality);

	void onPlayerStateUpdate(const std::string& streamID, ZegoPlayerState state, int errorCode, const std::string& extendedData);

	// screen capture callback
	static void OnCaptureError(enum ZegoScreenCaptureCaptureError error, void *user_data);
	static void OnCapturedWindowMoved(void *handle, int left, int top, int width, int height, void *user_data);
	//修改采用Express的方式
	static void OnCapturedFrameAvailable(const char *data, uint32_t length, const struct ZegoScreenCaptureVideoCaptureFormat *video_frame_format, uint64_t reference_time, uint32_t reference_time_scale, void *user_data);

	static void OnCaptureWindowChange(ZegoScreenCaptureWindowStatus status_code, ZegoWindowHandle handle, ZegoScreenCaptureRect rect, void *user_data);
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
	//add
	void onUiPlayStreamRequested(int curState);

private:
	void initExpress(void);
	void initScreenCapture(void);
	void bindSettings(void);

	Q_SIGNAL void captureStateChanged_p(int state);
	Q_SLOT void onCaptureStateChanged_p(int state);
	Q_SIGNAL void publishStateChanged_p(int state);
	Q_SLOT void onPublishStateChanged_p(int state);

	ZegoScreenCaptureSettings* m_settings = nullptr;
	QString m_userId;
	//SDK推流启动回调
	std::shared_ptr<CustomVideoCapturer> mCustomVideoCapture;
	//SDK状态等信息回调
	std::shared_ptr<IZegoEventHandler> eventHandler;  
};
