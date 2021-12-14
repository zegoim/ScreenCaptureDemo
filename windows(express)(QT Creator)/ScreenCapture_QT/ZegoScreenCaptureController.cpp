#include "ZegoScreenCaptureController.h"
#include "ZegoScreenCaptureSettings.h"
#include "ZegoScreenCaptureDemo.h"

// screen capture SDK API
#include "zego-screencapture.h"

//ZegoExpressSDK  2021/1/12  longjuncai添加
#include "ZegoExpressSDK.h"
#include "ZegoInternalEngineImpl.hpp"
#include "CustomVideoCapture.h"
using namespace ZEGO::EXPRESS;

#include <QApplication>
#include <QDebug>
#include <QImage>
#include <QPixmap>

//启动Express SDK的Appid和Signkey->可用于RTC服务器
unsigned int g_rtmp_appid = 1;

//适配Express方式

static const char* g_rtmp_signkey = "";

ZegoScreenCaptureController::ZegoScreenCaptureController(QObject *parent)
	: QObject(parent), m_settings(new ZegoScreenCaptureSettings(this))
{
	m_userId = QStringLiteral("7890");

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
	initExpress();
	initScreenCapture();
	bindSettings();
}

void ZegoScreenCaptureController::initExpress(void)
{
	auto logDir = qApp->applicationDirPath().toUtf8();
	bool bRet = false;
	//设置日志目录
	ZegoEngineConfig config;
	ZegoLogConfig logConfig;
	config.logConfig = &logConfig;
	//auto logconfig = std::make_shared<ZegoLogConfig*>(config.logConfig);
	const char* logpath = logDir;
	config.logConfig->logPath = std::string(logpath);
	ZegoExpressSDK::setEngineConfig(config);

	//创建引擎
    auto engine  = ZegoExpressSDK::createEngine(g_rtmp_appid, (const char*)g_rtmp_signkey, true, ZEGO_SCENARIO_GENERAL, nullptr);
	Q_ASSERT(engine != nullptr);

	//设置自定义视频采集对象
	mCustomVideoCapture = std::shared_ptr<CustomVideoCapturer>(new CustomVideoCapturer);
	ZegoCustomVideoCaptureConfig customVideoCaptureConfig;
	customVideoCaptureConfig.bufferType = ZEGO_VIDEO_BUFFER_TYPE_RAW_DATA;

	//设置自定义视频采集
	engine->enableCustomVideoCapture(true, &customVideoCaptureConfig);
	engine->setCustomVideoCaptureHandler(mCustomVideoCapture);

	//设置事件回调-用以通知推流执行状态
	eventHandler = std::shared_ptr<IZegoEventHandler> (this);
	
	engine->setEventHandler(eventHandler);

	//创建用户信息
	ZegoUser user(m_userId.toStdString(), m_userId.toStdString());

	//登录房间
	engine->loginRoom(m_userId.toStdString(), user);

}

void ZegoScreenCaptureController::initScreenCapture(void)
{
	auto logDir = qApp->applicationDirPath().toUtf8();

	zego_screencapture_set_log_level(kZegoLogLevelDebug, logDir);
	zego_screencapture_reg_capture_error_notify((zego_screencapture_capture_error_notify_func)OnCaptureError, this);
	//zego_screencapture_reg_captured_window_moved_notify((zego_screencapture_captured_window_moved_notify_func)OnCapturedWindowMoved, this);
	zego_screencapture_reg_captured_frame_available_notify((zego_screencapture_captured_frame_available_notify_func)OnCapturedFrameAvailable, this);
	zego_screencapture_reg_captured_window_status_change_notify((zego_screencapture_captured_window_status_change_notify_func)OnCaptureWindowChange, this);
	zego_screencapture_init();
	zego_screencapture_set_fps(10);
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
	//add
	connect(m_settings, &ZegoScreenCaptureSettings::PlayStreamRequested,
		this, &ZegoScreenCaptureController::onUiPlayStreamRequested);
}

void ZegoScreenCaptureController::uninit(void)
{
	zego_screencapture_uninit();
	//采用Express的登出方式

	//Loginout &  Destroy Engine
	{
		//获取单例engine
		auto engine = ZegoExpressSDK::getEngine();
		if (engine) {
			engine->logoutRoom(m_userId.toStdString());
			engine->enableCustomVideoCapture(false, nullptr);
			engine->setCustomVideoCaptureHandler(nullptr);
			ZegoExpressSDK::destroyEngine(engine);
		}
	}
}

//----重写
void ZegoScreenCaptureController::onPublisherStateUpdate(const std::string& streamID, ZEGO::EXPRESS::ZegoPublisherState state, int errorCode, const std::string& extendedData)
{
	QString desc = QStringLiteral("## 流状态变更 > %1 ##").arg(state);
	m_settings->appendLogString(desc);

	//如果此时推流成功，那么扩展数据会包含RTMP和hls的地址，打印显示出来
	if (!extendedData.empty() && (extendedData != "{}"))
	{
		std::string strRtmpUrl = "rtmp_url_list";
		std::string strHlsUrl = "hls_url_list";

		//rtmp
		uint iPos1 = extendedData.find(strRtmpUrl);
		uint iPos2 = extendedData.find("[",iPos1+1);
		uint iPos3 = extendedData.find("]", iPos2+1);
		if (iPos3 - iPos2 - 3 > 0)
		{
			strRtmpUrl = extendedData.substr(iPos2 + 2, iPos3 - iPos2 - 3);
		}

		//hls
		iPos1 = extendedData.find(strHlsUrl,iPos3);
		iPos2 = extendedData.find("[", iPos3 + 1);
		iPos3 = extendedData.find("]", iPos2 + 1);
		if (iPos3 - iPos2 - 3 > 0)
		{
			strHlsUrl = extendedData.substr(iPos2 + 2, iPos3 - iPos2 - 3);
		}

		m_settings->setPublishStreamUrl(QString(strRtmpUrl.c_str()), QString(strHlsUrl.c_str()));
		
	}
	
	// 回调更新界面要切换线程
	emit publishStateChanged_p((int)state);
}

void ZegoScreenCaptureController::onPublishStateChanged_p(int state)
{
	m_settings->updatePublishState(state == 2 ?
		ZegoScreenCaptureSettings::Publishing : ZegoScreenCaptureSettings::UnPublish);

}

//----重写
void ZegoScreenCaptureController::onPublisherQualityUpdate(const std::string& streamID, const ZEGO::EXPRESS::ZegoPublishStreamQuality& quality)
{
	if (streamID.empty())
		return;

	// 推流质量实时统计
	QString desc = QStringLiteral("#### 实时统计 [%1] 质量: %2 帧率: %3 码率: %4 ####")
		.arg(QString(streamID.c_str())).arg(quality.level).arg(quality.videoSendFPS).arg(quality.videoKBPS);
	m_settings->appendLogString(desc);
}

//重写ZegoEvent的拉流监听
void ZegoScreenCaptureController::onPlayerStateUpdate(const std::string& streamID, ZegoPlayerState state, int errorCode, const std::string& extendedData)
{
	ZegoScreenCaptureSettings::PlayState mystate;
	//更新按钮状态，监听拉流状态
	switch (state)
	{
	case ZEGO::EXPRESS::ZEGO_PLAYER_STATE_NO_PLAY:
		mystate = ZegoScreenCaptureSettings::UnPlay;
		break;
	case ZEGO::EXPRESS::ZEGO_PLAYER_STATE_PLAY_REQUESTING:
		mystate = ZegoScreenCaptureSettings::PlayConnecting;
		break;
	case ZEGO::EXPRESS::ZEGO_PLAYER_STATE_PLAYING:
		mystate = ZegoScreenCaptureSettings::Playing;
		break;
	default:
		break;
	}
	m_settings->updatePlayState(mystate);
	//拉流成功，那么打印成功提示信息
	if (mystate == ZegoScreenCaptureSettings::Playing)
	{
		qDebug() << QString("PlayStream Successful!");
	}
	//输出扩展数据
	qDebug() << QString(extendedData.c_str());
}

void ZegoScreenCaptureController::OnCapturedFrameAvailable(const char *data, uint32_t length, const struct ZegoScreenCaptureVideoCaptureFormat *video_frame_format, uint64_t reference_time, uint32_t reference_time_scale, void *user_data)
{

	ZegoScreenCaptureController *pThis = (ZegoScreenCaptureController *)user_data;
	if (!pThis)
		return;
	//查看捕捉到的界面
    //QImage image((unsigned char*)data, video_frame_format->width, video_frame_format->height, QImage::Format_ARGB32);
    //pThis->m_settings->setCaptureImage(QPixmap::fromImage(image));

	if (CustomVideoCapturer::mVideoCaptureRunning)
	{
		auto videoFrame = std::shared_ptr<ZegoCustomVideoFrame>(new ZegoCustomVideoFrame);
		//auto videoFrame = std::shared_ptr<ZegoVideoEncodedFrameParam>(new ZegoVideoEncodedFrameParam);
		videoFrame->dataLength = length;
		videoFrame->data = std::unique_ptr<unsigned char[]>(new unsigned char[videoFrame->dataLength]);
		memcpy(videoFrame->data.get(), data, videoFrame->dataLength);

		videoFrame->param.format = ZEGO::EXPRESS::ZEGO_VIDEO_FRAME_FORMAT_BGRA32;
		videoFrame->param.width = video_frame_format->width;
		videoFrame->param.height = video_frame_format->height;
		videoFrame->param.strides[0] = video_frame_format->strides[0];
		videoFrame->param.rotation = 0;

		videoFrame->referenceTimeMillsecond = reference_time;

		//将数据压入Express SDK引擎
		if (videoFrame)
		{
			ZegoExpressSDK::getEngine()->sendCustomVideoCaptureRawData(videoFrame->data.get(), videoFrame->dataLength, videoFrame->param, videoFrame->referenceTimeMillsecond, ZEGO::EXPRESS::ZEGO_PUBLISH_CHANNEL_MAIN);
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(20));

	}

	/****帧内容
	std::unique_ptr<unsigned char[]> data;
	unsigned int dataLength = 0;
	ZEGO::EXPRESS::ZegoVideoFrameParam param;
	unsigned long long referenceTimeMillsecond = 0;*/

}


void ZegoScreenCaptureController::OnCapturedWindowMoved(void *handle, int left, int top, int width, int height, void *user_data)
{
	// 正在捕捉的窗口位置变化，可供UI交互使用，本Dmeo没有用到
}

void ZegoScreenCaptureController::OnCaptureError(enum ZegoScreenCaptureCaptureError error, void *user_data)
{
	ZegoScreenCaptureController *pThis = (ZegoScreenCaptureController *)user_data;
	if (!pThis)
		return;

	// 桌面捕捉异常停止，比如显示器被拔掉、目标窗口被关掉
	//emit pThis->captureStateChanged_p(error);
}

void ZegoScreenCaptureController::OnCaptureWindowChange(ZegoScreenCaptureWindowStatus status_code, ZegoWindowHandle handle, ZegoScreenCaptureRect rect, void *user_data)
{
	ZegoScreenCaptureController *pThis = (ZegoScreenCaptureController *)user_data;
	if (!pThis)
		return;
// 	if(status_code== kZegoScreenCaptureWindowNoChange)
// 		pThis->m_settings->appendLogString(QStringLiteral("NoChange"));
// 
	if(status_code == kZegoScreenCaptureWindowCover)
		pThis->m_settings->appendLogString(QStringLiteral("Cover"));
	if (status_code == kZegoScreenCaptureWindowShow)
		pThis->m_settings->appendLogString(QStringLiteral("Show"));
	if(status_code == kZegoScreenCaptureWindowUnCover)
		pThis->m_settings->appendLogString(QStringLiteral("UnCover"));
	if(status_code== kZegoScreenCaptureWindowDestroy)
		pThis->m_settings->appendLogString(QStringLiteral("destroy"));
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
		zego_screencapture_set_target_screen(/*m_settings->currentScreen().toUtf8().data()*/0);
	}
	else if (target == ZegoScreenCaptureSettings::Window)
	{
		// 若选择分享某个窗口，则将当前设置的窗口句柄传入
		zego_screencapture_set_target_window_mode((ZegoScreenCaptureWindowMode)m_settings->getWinwowMode());
		zego_screencapture_set_target_window((void*)m_settings->currentWindow());
		//zego_screencapture_set_target_window_rect(200, 200, 400, 400);
	}
	else if (target == ZegoScreenCaptureSettings::Rectangle)
	{
		// 若选择分享某个区域，则将当前设置的区域矩形坐标传入
		QRect rect = m_settings->currentRectangle();
		zego_screencapture_set_target_rect(0,rect.x(), rect.y(), rect.width(), rect.height());
		zego_screencapture_set_target_rect(0, 0, 0, 2880, 1800);
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
		zego_screencapture_set_target_screen(/*name.toUtf8().data()*/0);
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
		zego_screencapture_set_target_window_mode((ZegoScreenCaptureWindowMode)m_settings->getWinwowMode());
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
	auto engine = ZegoExpressSDK::getEngine();
	ZegoVideoConfig tempvideoconfig = engine->getVideoConfig();
// 	tempvideoconfig.captureWidth = resolution.width();
// 	tempvideoconfig.captureHeight = resolution.height();
	tempvideoconfig.encodeHeight = resolution.height();
	tempvideoconfig.encodeWidth = resolution.width();

	engine->setVideoConfig(tempvideoconfig);
}

void ZegoScreenCaptureController::onUiBitrateChanged(int bitrate)
{
	qDebug() << "onUiBitrateChanged " << bitrate;

	// 设置推流码率
	//ZEGO::LIVEROOM::SetVideoBitrate(bitrate);
	auto engine = ZegoExpressSDK::getEngine();
	ZegoVideoConfig m_videoconfig = engine->getVideoConfig();
	m_videoconfig.bitrate = bitrate / 1024;

	engine->setVideoConfig(m_videoconfig);
}

void ZegoScreenCaptureController::onUiFramerateChanged(int framerate)
{
	qDebug() << "onUiFramerateChanged " << framerate;

	// 设置桌面分享的采集帧率，即OnCapturedFrameAvailable每秒回调次数
	zego_screencapture_set_fps(30);

	auto engine = ZegoExpressSDK::getEngine();
	ZEGO::EXPRESS::ZegoVideoConfig m_videoconfig = engine->getVideoConfig();
	m_videoconfig.fps = framerate;
	engine->setVideoConfig(m_videoconfig);

	// 同时设置推流帧率
	//ZEGO::LIVEROOM::SetVideoFPS(framerate);

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
		zego_screencapture_set_target_window_mode((ZegoScreenCaptureWindowMode)m_settings->getWinwowMode());
		//zego_screencapture_set_target_window_rect(200, 200, 400, 400);
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

	//获取engine
	auto engine = ZegoExpressSDK::getEngine();
	Q_ASSERT(engine != nullptr);

	if (curState == ZegoScreenCaptureSettings::UnPublish)
	{
		// 在开始推流前开始，先启动捕捉桌面
		if (m_settings->currentCaptureState() == ZegoScreenCaptureSettings::CaptureIdle)
		{
			onUiCaptureRequested(ZegoScreenCaptureSettings::CaptureIdle);
		}

		//启动推流
		engine->startPublishingStream(m_userId.toStdString(),ZEGO::EXPRESS::ZegoPublishChannel::ZEGO_PUBLISH_CHANNEL_MAIN);

		//更新推流状态
		m_settings->updatePublishState(ZegoScreenCaptureSettings::PublishConnecting);

	}
	else if (curState == ZegoScreenCaptureSettings::PublishConnecting ||
		curState == ZegoScreenCaptureSettings::Publishing)
	{
		// 停止推流，马上可以停止

		engine->stopPublishingStream();

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
	zego_screencapture_set_target_window_mode((ZegoScreenCaptureWindowMode)m_settings->getWinwowMode());
	zego_screencapture_set_target_window((void*)id);

	// 在开始推流前开始，先启动捕捉桌面
	if (m_settings->currentCaptureState() == ZegoScreenCaptureSettings::CaptureIdle)
	{
		onUiCaptureRequested(ZegoScreenCaptureSettings::CaptureIdle);
	}

	//获取engine
	auto engine = ZegoExpressSDK::getEngine();
	Q_ASSERT(engine != nullptr);
	//启动推流
	engine->startPublishingStream(m_userId.toStdString());
	//更新推流状态
	m_settings->updatePublishState(ZegoScreenCaptureSettings::PublishConnecting);
}

void ZegoScreenCaptureController::onUiPlayStreamRequested(int curState)
{
	auto engine = ZegoExpressSDK::getEngine();
	if (engine != nullptr)
	{
		if (curState == ZegoScreenCaptureSettings::PlayState::UnPlay)
		{
			//成功获取引擎，那么开始拉流
			//QVideoWidget video_play;
			ZegoCanvas zegocanvas = (ZegoView*)(m_CaptureView->winId());
			engine->startPlayingStream(m_userId.toStdString(), &zegocanvas);
			//engine->startPlayingStream(m_userId.toStdString(), nullptr);
			m_settings->updatePlayState(ZegoScreenCaptureSettings::PlayConnecting);
		}
		else if ((curState == ZegoScreenCaptureSettings::PlayConnecting) || (ZegoScreenCaptureSettings::Playing))
		{
			//停止拉流
			engine->stopPlayingStream(m_userId.toStdString());
			m_settings->updatePlayState(ZegoScreenCaptureSettings::UnPlay);
		}
		
	}
}
