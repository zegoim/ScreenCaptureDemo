#include "ZegoScreenCaptureController.h"
#include "ZegoScreenCaptureSettings.h"
#include "ZegoExternalCaptureFactory.h"

// screen capture SDK API
#include "zego-screencapture.h"
// LiveRoom SDK API
#include "LiveRoom.h"
#include "RoomDefines.h"
//#include "ZegoAVApi-advanced.h"

#include <QApplication>
#include <QDebug>


static unsigned int g_rtmp_appid = 1;
static unsigned char g_rtmp_signkey[] =
{
	0x91, 0x93, 0xcc, 0x66, 0x2a, 0x1c, 0x0e, 0xc1,
	0x35, 0xec, 0x71, 0xfb, 0x07, 0x19, 0x4b, 0x38,
	0x41, 0xd4, 0xad, 0x83, 0x78, 0xf2, 0x59, 0x90,
	0xe0, 0xa4, 0x0c, 0x7f, 0xf4, 0x28, 0x41, 0xf7
};


ZegoScreenCaptureController::ZegoScreenCaptureController(QObject *parent)
	: QObject(parent), m_settings(new ZegoScreenCaptureSettings(this))
{
	m_userId = QStringLiteral("%1").arg(qrand() % 10000000);

	init();

	// 忽略，用于线程同步
	connect(this, &ZegoScreenCaptureController::captureStateChanged_p,
		this, &ZegoScreenCaptureController::onCaptureStateChanged_p, Qt::QueuedConnection);
	connect(this, &ZegoScreenCaptureController::publishStateChanged_p, 
		this, &ZegoScreenCaptureController::onPublishStateChanged_p, Qt::QueuedConnection);
}

ZegoScreenCaptureController::~ZegoScreenCaptureController()
{
	uninit();
}

void ZegoScreenCaptureController::init(void)
{
	initAV();
	initScreenCapture();
	bindSettings();
}

void ZegoScreenCaptureController::initAV(void)
{
	auto logDir = qApp->applicationDirPath().toUtf8();
	bool bRet = false;
	// 在InitSDK前须确定使用外部采集模式，由SDK外提供视频数据源，这里的视频数据即桌面画面，默认为MainChannel
	m_externalCaptureFactory = new ZegoExternalCaptureFactory(this);
	ZEGO::LIVEROOM::SetVideoCaptureFactory(m_externalCaptureFactory);
	bRet = ZEGO::LIVEROOM::SetLogDir(logDir);
	ZEGO::LIVEROOM::SetUseTestEnv(true);
	bRet = ZEGO::LIVEROOM::InitSDK(g_rtmp_appid, g_rtmp_signkey, 32);
	bRet = ZEGO::LIVEROOM::SetLivePublisherCallback(this);
	bRet = ZEGO::LIVEROOM::SetUser(m_userId.toUtf8(), m_userId.toUtf8());
	bRet = ZEGO::LIVEROOM::LoginRoom(m_userId.toUtf8(), ZEGO::COMMON::ZegoRoomRole::Anchor, m_userId.toUtf8());
	
}

void ZegoScreenCaptureController::initScreenCapture(void)
{
	auto logDir = qApp->applicationDirPath().toUtf8();

	zego_screencapture_set_log_level(kZegoLogLevelDebug, logDir);
	zego_screencapture_reg_capture_error_notify((zego_screencapture_capture_error_notify_func)OnCaptureError, this);
	zego_screencapture_reg_captured_window_moved_notify((zego_screencapture_captured_window_moved_notify_func)OnCapturedWindowMoved, this);
	zego_screencapture_reg_captured_frame_available_notify((zego_screencapture_captured_frame_available_notify_func)OnCapturedFrameAvailable, this);
	zego_screencapture_reg_captured_window_status_change_notify((zego_screencapture_captured_window_status_change_notify_func)OnCaptureWindowChange, this);
	zego_screencapture_init();

	int x(0), y(0), w(0), h(0);
	zego_screencapture_get_virtual_desktop_rect(&x, &y, &w, &h);
	//zego_screencapture_set_capture_video_pixel_format(kZegoPixelFormatI420);
	zego_screencapture_set_capture_video_pixel_format(kZegoPixelFormatBGRA32);
	m_settings->setDesktopBoundingRect(QRect(x, y, w, h));
}

void ZegoScreenCaptureController::bindSettings(void)
{
	connect(m_settings, &ZegoScreenCaptureSettings::targetChanged,
		this, &ZegoScreenCaptureController::onUiTargetChanged);
	connect(m_settings, &ZegoScreenCaptureSettings::screenRefreshRequested,
		this, &ZegoScreenCaptureController::onUiScreenRefreshRequested);
	connect(m_settings, &ZegoScreenCaptureSettings::screenSelectChanged,
		this, &ZegoScreenCaptureController::onUiScreenSelectChanged);
	connect(m_settings, &ZegoScreenCaptureSettings::windowRefreshRequested,
		this, &ZegoScreenCaptureController::onUiWindowRefreshRequested);
	connect(m_settings, &ZegoScreenCaptureSettings::windowSelectChanged,
		this, &ZegoScreenCaptureController::onUiWindowSelectChanged);
	connect(m_settings, &ZegoScreenCaptureSettings::rectangleChanged,
		this, &ZegoScreenCaptureController::onUiRectangleChanged);
	connect(m_settings, &ZegoScreenCaptureSettings::resolutionSelectChanged,
		this, &ZegoScreenCaptureController::onUiResolutionSelectChanged);
	connect(m_settings, &ZegoScreenCaptureSettings::bitrateChanged,
		this, &ZegoScreenCaptureController::onUiBitrateChanged);
	connect(m_settings, &ZegoScreenCaptureSettings::framerateChanged,
		this, &ZegoScreenCaptureController::onUiFramerateChanged);
	connect(m_settings, &ZegoScreenCaptureSettings::cursorToggled,
		this, &ZegoScreenCaptureController::onUiCursorToggled);
	connect(m_settings, &ZegoScreenCaptureSettings::clickAnimationToggled,
		this, &ZegoScreenCaptureController::onUiClickAnimationToggled);
	connect(m_settings, &ZegoScreenCaptureSettings::captureRequested,
		this, &ZegoScreenCaptureController::onUiCaptureRequested);
	connect(m_settings, &ZegoScreenCaptureSettings::publishRequested,
		this, &ZegoScreenCaptureController::onUiPublishRequested);
	connect(m_settings, &ZegoScreenCaptureSettings::addExcludedWindowRequested,
		this, &ZegoScreenCaptureController::OnUiAddExcludedWindowRequested);
	connect(m_settings, &ZegoScreenCaptureSettings::removeExcludedWindowRequested,
		this, &ZegoScreenCaptureController::OnUiRemoveExcludedWindowRequested);
	connect(m_settings, &ZegoScreenCaptureSettings::thumbnailWindowCapture,
		this, &ZegoScreenCaptureController::OnUiThumbnailWindowCapture);
}

void ZegoScreenCaptureController::uninit(void)
{
	zego_screencapture_uninit();
	ZEGO::LIVEROOM::LogoutRoom();
	ZEGO::LIVEROOM::UnInitSDK();
}

void ZegoScreenCaptureController::OnPublishStateUpdate(int stateCode, const char* pszStreamID, const ZEGO::COMMON::ZegoPublishingStreamInfo& oStreamInfo)
{
	QString rtmpUrl, hlsUrl;
	if (oStreamInfo.uiRtmpURLCount > 0)
	{
		rtmpUrl = oStreamInfo.arrRtmpURLs[0] ? oStreamInfo.arrRtmpURLs[0] : "";
	}
	if (oStreamInfo.uiHlsURLCount > 0)
	{
		hlsUrl = oStreamInfo.arrHlsURLs[0] ? oStreamInfo.arrHlsURLs[0] : "";
	}
	m_settings->setPublishStreamUrl(rtmpUrl, hlsUrl);

	QString desc = QStringLiteral("## 流状态变更 > %1 ##").arg(stateCode);
	m_settings->appendLogString(desc);

	// 回调更新界面要切换线程
	emit publishStateChanged_p((int)stateCode);
}

void ZegoScreenCaptureController::onPublishStateChanged_p(int state)
{
	m_settings->updatePublishState(state == 0 ?
		ZegoScreenCaptureSettings::Publishing : ZegoScreenCaptureSettings::UnPublish);
}

void ZegoScreenCaptureController::OnPublishQulityUpdate(const char* pszStreamID, int quality, double videoFPS, double videoKBS)
{
	if (!pszStreamID) 
		return;

	// 推流质量实时统计
	QString desc = QStringLiteral("#### 实时统计 [%1] 质量: %2 帧率: %3 码率: %4 ###")
		.arg(QString(pszStreamID)).arg(quality).arg(videoFPS).arg(videoKBS);
	m_settings->appendLogString(desc);
}
#include <time.h>
void ZegoScreenCaptureController::OnCapturedFrameAvailable(const char *data, uint32_t length, const struct ZegoScreenCaptureVideoCaptureFormat *video_frame_format, uint64_t reference_time, uint32_t reference_time_scale, void *user_data) {
// void ZegoScreenCaptureController::OnCapturedFrameAvailable(const char* data, int length,
// 	const ZEGO::ScreenCapture::VideoCaptureFormat& frame_format,
// 	unsigned long long reference_time, unsigned int reference_time_scale)
// {
	ZegoScreenCaptureController *pThis = (ZegoScreenCaptureController *)user_data;
	if (!pThis)
		return;

	auto externalDevice = pThis->m_externalCaptureFactory->Device();
	if (!externalDevice || !externalDevice->IsCapturing())
		return;

	if (!externalDevice->Client())
		return;

	// 从桌面分享SDK回调的桌面画面，直接传给音视频SDK推流
	AVE::VideoCaptureFormat format;
	format.width = video_frame_format->width;
	format.height = video_frame_format->height;

	if (video_frame_format->video_pixel_format == kZegoPixelFormatI420)
	{
		format.strides[0] = video_frame_format->strides[0];
		format.strides[1] = video_frame_format->strides[1];
		format.strides[2] = video_frame_format->strides[2];
	}
	else
	{
		format.strides[0] = video_frame_format->strides[0];
	}
	
	format.pixel_format = (AVE::VideoPixelFormat)video_frame_format->video_pixel_format;
	format.rotation = video_frame_format->rotation;
	externalDevice->Client()->OnIncomingCapturedData(data, length, format, reference_time, reference_time_scale);
}

void ZegoScreenCaptureController::OnCapturedWindowMoved(void *handle, int left, int top, int width, int height, void *user_data)
//void ZegoScreenCaptureController::OnCapturedWindowMoved(void* winId, int x, int y, int w, int h)
{
	// 正在捕捉的窗口位置变化，可供UI交互使用，本Dmeo没有用到
}

void ZegoScreenCaptureController::OnCaptureError(enum ZegoScreenCaptureCaptureError error, void *user_data)
//void ZegoScreenCaptureController::OnCaptureError(int nErrorCode)
{
	ZegoScreenCaptureController *pThis = (ZegoScreenCaptureController *)user_data;
	if (!pThis)
		return;

	// 桌面捕捉异常停止，比如显示器被拔掉、目标窗口被关掉
	emit pThis->captureStateChanged_p(error);
}

void ZegoScreenCaptureController::OnCaptureWindowChange(ZegoScreenCaptureWindowStatus status_code, ZegoWindowHandle handle, ZegoRect rect, void *user_data)
{
	ZegoScreenCaptureController *pThis = (ZegoScreenCaptureController *)user_data;
	if (!pThis)
		return;
// 	if(status_code== kZegoScreenCaptureWindowNoChange)
// 		pThis->m_settings->appendLogString(QStringLiteral("NoChange"));
// 
// 	if(status_code == kZegoScreenCaptureWindowMove)
// 		pThis->m_settings->appendLogString(QStringLiteral("Move"));
}

void ZegoScreenCaptureController::onCaptureStateChanged_p(int state)
{
	// 因异常停止采集，为简单模拟停止捕捉按钮调用
	onUiCaptureRequested(ZegoScreenCaptureSettings::CaptureWorking);
}

void ZegoScreenCaptureController::onUiTargetChanged(int target)
{
	qDebug() << "onUiTargetChanged " << target;

	if (target == ZegoScreenCaptureSettings::Screen)
	{
		// 若选择分享整个屏幕，则将当前设置的屏幕名称传入
		zego_screencapture_set_target_screen(m_settings->currentScreen().toUtf8().data());
	}
	else if (target == ZegoScreenCaptureSettings::Window)
	{
		// 若选择分享某个窗口，则将当前设置的窗口句柄传入
		zego_screencapture_set_target_window((void*)m_settings->currentWindow());
	}
	else if (target == ZegoScreenCaptureSettings::Rectangle)
	{
		// 若选择分享某个区域，则将当前设置的区域矩形坐标传入
		QRect rect = m_settings->currentRectangle();
		zego_screencapture_set_target_rect(0,rect.x(), rect.y(), rect.width(), rect.height());
	}
}

void ZegoScreenCaptureController::onUiScreenRefreshRequested(void)
{
	qDebug() << "onUiScreenRefreshRequested";

	// 刷新屏幕列表，EnumScreenList得到列表数据后深拷贝带走，FreeScreenList与之配对
	unsigned int count(0);
	const struct ZegoScreenCaptureScreenItem* itemList(nullptr);
	itemList = zego_screencapture_enum_screen_list(&count);
	if (!itemList) return;

	QVector<QVariantMap> screenList;
	for (int i= 0; i < count; i++)
	{
		QVariantMap varMap;
		QString screenName = itemList[i].name ? itemList[i].name : "";
		varMap["name"] = screenName;
		varMap["primary"] = itemList[i].is_primary != 0;
		screenList.push_back(varMap);
	}

	m_settings->setScreenList(screenList);
	zego_screencapture_free_screen_list(itemList);
}

void ZegoScreenCaptureController::onUiScreenSelectChanged(const QString& name)
{
	qDebug() << "onUiScreenSelectChanged " << name;

	if (m_settings->currentTarget() == ZegoScreenCaptureSettings::Screen)
	{
		// 要分享的屏幕发生变化
		zego_screencapture_set_target_screen(name.toUtf8().data());
	}
}

void ZegoScreenCaptureController::onUiWindowRefreshRequested(void)
{
	qDebug() << "onUiWindowRefreshRequested";

	// 刷新窗口列表，EnumWindowList得到列表数据后深拷贝带走，FreeWindowList与之配对
	unsigned int count(0);
	const struct ZegoScreenCaptureWindowItem* itemList(nullptr);
	itemList = zego_screencapture_enum_window_list(true, &count);
	if (!itemList) return;

	QVector<QVariantMap> windowList;
	for (int i = 0; i < count; i++)
	{
		QVariantMap varMap;
		QString windowTitle = itemList[i].title ? itemList[i].title : "";
		varMap["title"] = windowTitle;
		varMap["id"] = (qint64)itemList[i].handle;
		windowList.push_back(varMap);
	}

	m_settings->setWindowList(windowList);
	zego_screencapture_free_window_list(itemList);
}

void ZegoScreenCaptureController::onUiWindowSelectChanged(qint64 id)
{
	qDebug() << "onUiWindowSelectChanged " << id;

	if (m_settings->currentTarget() == ZegoScreenCaptureSettings::Window)
	{
		// 分享的窗口发生变化
		zego_screencapture_set_target_window((void*)id);
	}
}

void ZegoScreenCaptureController::onUiRectangleChanged(QRect geometry)
{
	qDebug() << "onUiRectangleChanged " << geometry;

	if (m_settings->currentTarget() == ZegoScreenCaptureSettings::Rectangle)
	{
		// 桌面分享区域发生变化
		zego_screencapture_set_target_rect(0,geometry.x(), geometry.y(), geometry.width(), geometry.height());
	}
}

void ZegoScreenCaptureController::onUiResolutionSelectChanged(QSize resolution)
{
	qDebug() << "onUiResolutionSelectChanged " << resolution;

	// 设置推流编码分辨率，即拉流端看到的画面分辨率。
	// 直播过程中该分辨率最好不要发生变化，否则可能影响服务器的录制
	//ZEGO::LIVEROOM::SetVideoCaptureResolution(resolution.width(), resolution.height());

	ZEGO::LIVEROOM::SetVideoEncodeResolution(resolution.width(), resolution.height());
}

void ZegoScreenCaptureController::onUiBitrateChanged(int bitrate)
{
	qDebug() << "onUiBitrateChanged " << bitrate;

	// 设置推流码率
	ZEGO::LIVEROOM::SetVideoBitrate(bitrate);
}

void ZegoScreenCaptureController::onUiFramerateChanged(int framerate)
{
	qDebug() << "onUiFramerateChanged " << framerate;

	// 设置桌面分享的采集帧率，即OnCapturedFrameAvailable每秒回调次数
	zego_screencapture_set_fps(framerate);

	// 同时设置推流帧率
	ZEGO::LIVEROOM::SetVideoFPS(framerate);

	// 前者是输入帧率，后者是输出帧率
}

void ZegoScreenCaptureController::onUiCursorToggled(bool checked)
{
	qDebug() << "onUiCursorToggled " << checked;

	// 设置是否同时捕捉光标
	zego_screencapture_set_cursor_visible(checked);
}

void ZegoScreenCaptureController::onUiClickAnimationToggled(bool checked)
{
	qDebug() << "onUiClickAnimationToggled " << checked;

	// 设置是否在捕捉到分享画面的同时显示点击动画
	zego_screencapture_enable_click_animation(checked);
}

void ZegoScreenCaptureController::onUiCaptureRequested(int curState)
{
	qDebug() << "onUiCaptureRequested " << curState;

	
	if (curState == ZegoScreenCaptureSettings::CaptureIdle)
	{
		// 如果当前未开始捕捉桌面，启动之

		zego_screencapture_start_capture();
		m_settings->updateCaptureState(ZegoScreenCaptureSettings::CaptureWorking);
	}
	else if (curState == ZegoScreenCaptureSettings::CaptureWorking)
	{
		// 如果当前正在捕捉桌面画面，停止
		zego_screencapture_stop_capture();
		m_settings->updateCaptureState(ZegoScreenCaptureSettings::CaptureIdle);
	}
}

void ZegoScreenCaptureController::onUiPublishRequested(int curState)
{
	qDebug() << "onUiPublishRequested " << curState;

	if (curState == ZegoScreenCaptureSettings::UnPublish)
	{
		// 在开始推流前开始，先启动捕捉桌面
		if (m_settings->currentCaptureState() == ZegoScreenCaptureSettings::CaptureIdle)
		{
			onUiCaptureRequested(ZegoScreenCaptureSettings::CaptureIdle);
		}

		//m_userId = QStringLiteral("%1").arg(qrand() % 10000000);

		// 开始推流，这里使用计算名作为流名，流名中最好不要含有特殊字符以及URL关键字
		// 推流的状态变化以及流地址见OnPublishStateUpdate中回调
		ZEGO::LIVEROOM::StartPublishing(m_userId.toUtf8(), m_userId.toUtf8(),ZEGO::LIVEROOM::ZegoPublishFlag::ZEGO_SINGLE_ANCHOR);
		m_settings->updatePublishState(ZegoScreenCaptureSettings::PublishConnecting);
	}
	else if (curState == ZegoScreenCaptureSettings::PublishConnecting ||
		curState == ZegoScreenCaptureSettings::Publishing)
	{
		// 停止推流，马上可以停止
		ZEGO::LIVEROOM::StopPublishing();
		m_settings->updatePublishState(ZegoScreenCaptureSettings::UnPublish);
	}
}

void ZegoScreenCaptureController::OnUiAddExcludedWindowRequested()
{
	qDebug() << __FUNCTION__<< " " << true;
	ZegoWindowHandle handle = (ZegoWindowHandle)m_settings->currentWindow();
	zego_screencapture_set_excluded_windows((ZegoWindowHandle*)&handle, 1, true);

}
void ZegoScreenCaptureController::OnUiRemoveExcludedWindowRequested()
{
	qDebug() << __FUNCTION__ << " " << false;
	ZegoWindowHandle handle = (ZegoWindowHandle)m_settings->currentWindow();
	zego_screencapture_set_excluded_windows((ZegoWindowHandle*)&handle, 1, false);
}

void ZegoScreenCaptureController::OnUiThumbnailWindowCapture(qint64 id)
{
	zego_screencapture_set_target_window((void*)id);

	// 在开始推流前开始，先启动捕捉桌面
	if (m_settings->currentCaptureState() == ZegoScreenCaptureSettings::CaptureIdle)
	{
		onUiCaptureRequested(ZegoScreenCaptureSettings::CaptureIdle);
	}

	//m_userId = QStringLiteral("%1").arg(qrand() % 10000000);

	// 开始推流，这里使用计算名作为流名，流名中最好不要含有特殊字符以及URL关键字
	// 推流的状态变化以及流地址见OnPublishStateUpdate中回调
	ZEGO::LIVEROOM::StartPublishing(m_userId.toUtf8(), m_userId.toUtf8(), ZEGO::LIVEROOM::ZegoPublishFlag::ZEGO_SINGLE_ANCHOR);
	m_settings->updatePublishState(ZegoScreenCaptureSettings::PublishConnecting);
}