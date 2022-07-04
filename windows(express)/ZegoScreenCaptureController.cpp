#include "ZegoScreenCaptureController.h"
#include "ZegoScreenCaptureSettings.h"
#include "ZegoScreenCaptureDemo.h"

// screen capture SDK API
#include "zego-screencapture.h"

//ZegoExpressSDK  2021/1/12  longjuncai���
#include "ZegoExpressSDK.h"
#include "ZegoExpressInterface.h"
#include "CustomVideoCapture.h"
using namespace ZEGO::EXPRESS;

#include <QApplication>
#include <QDebug>
#include <QImage>
#include <QPixmap>

// �� Zego ����̨����� appid �� appsign
unsigned int g_rtmp_appid = /*appID*/;
static const char* g_rtmp_signkey = /*appsign*/;

ZegoScreenCaptureController::ZegoScreenCaptureController(QObject *parent)
	: QObject(parent), m_settings(new ZegoScreenCaptureSettings(this))
{
	m_userId = QStringLiteral("7890");

	init();

	// ���ԣ������߳�ͬ��
	connect(this, &ZegoScreenCaptureController::captureStateChanged_p,
		this, &ZegoScreenCaptureController::onCaptureStateChanged_p, Qt::QueuedConnection);
	connect(this, &ZegoScreenCaptureController::publishStateChanged_p, 
		this, &ZegoScreenCaptureController::onPublishStateChanged_p, Qt::QueuedConnection);

	// event handle
	connect(eventHandler.get(), &ZegoEventHandler::publishStateChanged_p, this, &ZegoScreenCaptureController::onPublishStateChanged_p, Qt::QueuedConnection);
	// write log
	connect(eventHandler.get(), &ZegoEventHandler::WriteLog_p, m_settings, &ZegoScreenCaptureSettings::WriteLog, Qt::QueuedConnection);
	// other
	connect(eventHandler.get(), &ZegoEventHandler::updatePlayState_p, m_settings, &ZegoScreenCaptureSettings::UpdateState, Qt::QueuedConnection);
	connect(eventHandler.get(), &ZegoEventHandler::setPublishStreamUrl_p, m_settings, &ZegoScreenCaptureSettings::SetPublishUrl, Qt::QueuedConnection);
}

ZegoScreenCaptureController::~ZegoScreenCaptureController()
{
	static bool isUninited = false;
	if(!isUninited)
	{ 
		isUninited = true;
		uninit();
	}
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
	//������־Ŀ¼
	ZegoEngineConfig config;
	ZegoLogConfig logConfig;
	config.logConfig = &logConfig;
	//auto logconfig = std::make_shared<ZegoLogConfig*>(config.logConfig);
	const char* logpath = logDir;
	config.logConfig->logPath = std::string(logpath);
	ZegoExpressSDK::setEngineConfig(config);

	//��������
	ZegoEngineProfile profile;
	profile.appID = g_rtmp_appid;
	profile.appSign = g_rtmp_signkey;
	profile.scenario = ZEGO_SCENARIO_GENERAL;
	auto engine  = ZegoExpressSDK::createEngine(profile, nullptr);
	Q_ASSERT(engine != nullptr);

	//�����Զ�����Ƶ�ɼ�����
	mCustomVideoCapture = std::shared_ptr<CustomVideoCapturer>(new CustomVideoCapturer);
	ZegoCustomVideoCaptureConfig customVideoCaptureConfig;
	customVideoCaptureConfig.bufferType = ZEGO_VIDEO_BUFFER_TYPE_RAW_DATA;

	//�����Զ�����Ƶ�ɼ�
	engine->enableCustomVideoCapture(true, &customVideoCaptureConfig);
	engine->setCustomVideoCaptureHandler(mCustomVideoCapture);

	//�����¼��ص�-����֪ͨ����ִ��״̬
	//eventHandler = std::shared_ptr<IZegoEventHandler> (this);
	eventHandler = std::make_shared<ZegoEventHandler>();
	
	engine->setEventHandler(eventHandler);

	//�����û���Ϣ
	ZegoUser user(m_userId.toStdString(), m_userId.toStdString());

	//��¼����
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
	//����Express�ĵǳ���ʽ

	//Loginout &  Destroy Engine
	{
		//��ȡ����engine
		auto engine = ZegoExpressSDK::getEngine();
		if (engine) {
			eventHandler = nullptr;
			engine->setEventHandler(nullptr);
			engine->enableCustomVideoCapture(false, nullptr);
			engine->setCustomVideoCaptureHandler(nullptr);
			engine->logoutRoom(m_userId.toStdString());
			ZegoExpressSDK::destroyEngine(engine);
		}
	}
}

void ZegoScreenCaptureController::onPublishStateChanged_p(int state)
{
	m_settings->updatePublishState(state == 2 ?
		ZegoScreenCaptureSettings::Publishing : ZegoScreenCaptureSettings::UnPublish);

}

void ZegoScreenCaptureController::OnCapturedFrameAvailable(const char *data, uint32_t length, const struct ZegoScreenCaptureVideoCaptureFormat *video_frame_format, uint64_t reference_time, uint32_t reference_time_scale, void *user_data)
{

	ZegoScreenCaptureController *pThis = (ZegoScreenCaptureController *)user_data;
	if (!pThis)
		return;
	//�鿴��׽���Ľ���
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

		auto engine = ZegoExpressSDK::getEngine();
		//������ѹ��Express SDK����
		if (engine && videoFrame)
		{
			engine->sendCustomVideoCaptureRawData(videoFrame->data.get(), videoFrame->dataLength, videoFrame->param, videoFrame->referenceTimeMillsecond, ZEGO::EXPRESS::ZEGO_PUBLISH_CHANNEL_MAIN);
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(20));

	}

	/****֡����
	std::unique_ptr<unsigned char[]> data;
	unsigned int dataLength = 0;
	ZEGO::EXPRESS::ZegoVideoFrameParam param;
	unsigned long long referenceTimeMillsecond = 0;*/

}


void ZegoScreenCaptureController::OnCapturedWindowMoved(void *handle, int left, int top, int width, int height, void *user_data)
{
	// ���ڲ�׽�Ĵ���λ�ñ仯���ɹ�UI����ʹ�ã���Dmeoû���õ�
}

void ZegoScreenCaptureController::OnCaptureError(enum ZegoScreenCaptureCaptureError error, void *user_data)
{
	ZegoScreenCaptureController *pThis = (ZegoScreenCaptureController *)user_data;
	if (!pThis)
		return;

	// ���沶׽�쳣ֹͣ��������ʾ�����ε���Ŀ�괰�ڱ��ص�
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
	// ���쳣ֹͣ�ɼ���Ϊ��ģ��ֹͣ��׽��ť����
	onUiCaptureRequested(ZegoScreenCaptureSettings::CaptureWorking);
}

void ZegoScreenCaptureController::onUiTargetChanged(int target)
{
	qDebug() << "onUiTargetChanged " << target;

	if (target == ZegoScreenCaptureSettings::Screen)
	{
		// ��ѡ�����������Ļ���򽫵�ǰ���õ���Ļ���ƴ���
		zego_screencapture_set_target_screen(/*m_settings->currentScreen().toUtf8().data()*/0);
	}
	else if (target == ZegoScreenCaptureSettings::Window)
	{
		// ��ѡ�����ĳ�����ڣ��򽫵�ǰ���õĴ��ھ������
		zego_screencapture_set_target_window_mode((ZegoScreenCaptureWindowMode)m_settings->getWinwowMode());
		zego_screencapture_set_target_window((void*)m_settings->currentWindow());
		//zego_screencapture_set_target_window_rect(200, 200, 400, 400);
	}
	else if (target == ZegoScreenCaptureSettings::Rectangle)
	{
		// ��ѡ�����ĳ�������򽫵�ǰ���õ�����������괫��
		QRect rect = m_settings->currentRectangle();
		zego_screencapture_set_target_rect(0,rect.x(), rect.y(), rect.width(), rect.height());
		zego_screencapture_set_target_rect(0, 0, 0, 2880, 1800);
	}
}

void ZegoScreenCaptureController::onUiScreenRefreshRequested(void)
{
	qDebug() << "onUiScreenRefreshRequested";

	// ˢ����Ļ�б�EnumScreenList�õ��б����ݺ�������ߣ�FreeScreenList��֮���
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
		// Ҫ�������Ļ�����仯
		zego_screencapture_set_target_screen(/*name.toUtf8().data()*/0);
	}
}

void ZegoScreenCaptureController::onUiWindowRefreshRequested(void)
{
	qDebug() << "onUiWindowRefreshRequested";

	// ˢ�´����б�EnumWindowList�õ��б����ݺ�������ߣ�FreeWindowList��֮���
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
		// ����Ĵ��ڷ����仯
		zego_screencapture_set_target_window_mode((ZegoScreenCaptureWindowMode)m_settings->getWinwowMode());
		zego_screencapture_set_target_window((void*)id);
	}
}

void ZegoScreenCaptureController::onUiRectangleChanged(QRect geometry)
{
	qDebug() << "onUiRectangleChanged " << geometry;

	if (m_settings->currentTarget() == ZegoScreenCaptureSettings::Rectangle)
	{
		// ��������������仯
		zego_screencapture_set_target_rect(0,geometry.x(), geometry.y(), geometry.width(), geometry.height());
	}
}

void ZegoScreenCaptureController::onUiResolutionSelectChanged(QSize resolution)
{
	qDebug() << "onUiResolutionSelectChanged " << resolution;

	// ������������ֱ��ʣ��������˿����Ļ���ֱ��ʡ�
	// ֱ�������и÷ֱ�����ò�Ҫ�����仯���������Ӱ���������¼��
	auto engine = ZegoExpressSDK::getEngine();

	if (engine == nullptr) return;
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

	// ������������
	//ZEGO::LIVEROOM::SetVideoBitrate(bitrate);
	auto engine = ZegoExpressSDK::getEngine();
	if (engine == nullptr) return;
	ZegoVideoConfig m_videoconfig = engine->getVideoConfig();
	m_videoconfig.bitrate = bitrate / 1024;

	engine->setVideoConfig(m_videoconfig);
}

void ZegoScreenCaptureController::onUiFramerateChanged(int framerate)
{
	qDebug() << "onUiFramerateChanged " << framerate;

	// �����������Ĳɼ�֡�ʣ���OnCapturedFrameAvailableÿ��ص�����
	zego_screencapture_set_fps(30);

	auto engine = ZegoExpressSDK::getEngine();
	if (engine == nullptr) return;
	ZEGO::EXPRESS::ZegoVideoConfig m_videoconfig = engine->getVideoConfig();
	m_videoconfig.fps = framerate;
	engine->setVideoConfig(m_videoconfig);

	// ͬʱ��������֡��
	//ZEGO::LIVEROOM::SetVideoFPS(framerate);

	// ǰ��������֡�ʣ����������֡��
}

void ZegoScreenCaptureController::onUiCursorToggled(bool checked)
{
	qDebug() << "onUiCursorToggled " << checked;

	// �����Ƿ�ͬʱ��׽���
	zego_screencapture_set_cursor_visible(checked);
}

void ZegoScreenCaptureController::onUiClickAnimationToggled(bool checked)
{
	qDebug() << "onUiClickAnimationToggled " << checked;

	// �����Ƿ��ڲ�׽���������ͬʱ��ʾ�������
	zego_screencapture_enable_click_animation(checked);
}

void ZegoScreenCaptureController::onUiCaptureRequested(int curState)
{
	qDebug() << "onUiCaptureRequested " << curState;

	
	if (curState == ZegoScreenCaptureSettings::CaptureIdle)
	{
		// �����ǰδ��ʼ��׽���棬����֮

		zego_screencapture_start_capture();
		zego_screencapture_set_target_window_mode((ZegoScreenCaptureWindowMode)m_settings->getWinwowMode());
		//zego_screencapture_set_target_window_rect(200, 200, 400, 400);
		m_settings->updateCaptureState(ZegoScreenCaptureSettings::CaptureWorking);
	}
	else if (curState == ZegoScreenCaptureSettings::CaptureWorking)
	{
		// �����ǰ���ڲ�׽���滭�棬ֹͣ
		zego_screencapture_stop_capture();
		m_settings->updateCaptureState(ZegoScreenCaptureSettings::CaptureIdle);
	}
}

void ZegoScreenCaptureController::onUiPublishRequested(int curState)
{
	qDebug() << "onUiPublishRequested " << curState;

	//��ȡengine
	auto engine = ZegoExpressSDK::getEngine();
	if (engine == nullptr) return;

	if (curState == ZegoScreenCaptureSettings::UnPublish)
	{
		// �ڿ�ʼ����ǰ��ʼ����������׽����
		if (m_settings->currentCaptureState() == ZegoScreenCaptureSettings::CaptureIdle)
		{
			onUiCaptureRequested(ZegoScreenCaptureSettings::CaptureIdle);
		}

		//��������
		engine->startPublishingStream(m_userId.toStdString(),ZEGO::EXPRESS::ZegoPublishChannel::ZEGO_PUBLISH_CHANNEL_MAIN);

		//��������״̬
		m_settings->updatePublishState(ZegoScreenCaptureSettings::PublishConnecting);

	}
	else if (curState == ZegoScreenCaptureSettings::PublishConnecting ||
		curState == ZegoScreenCaptureSettings::Publishing)
	{
		// ֹͣ���������Ͽ���ֹͣ

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

	// �ڿ�ʼ����ǰ��ʼ����������׽����
	if (m_settings->currentCaptureState() == ZegoScreenCaptureSettings::CaptureIdle)
	{
		onUiCaptureRequested(ZegoScreenCaptureSettings::CaptureIdle);
	}

	//��ȡengine
	auto engine = ZegoExpressSDK::getEngine();
	if (engine == nullptr) return;
	//��������
	engine->startPublishingStream(m_userId.toStdString());
	//��������״̬
	m_settings->updatePublishState(ZegoScreenCaptureSettings::PublishConnecting);
}

void ZegoScreenCaptureController::onUiPlayStreamRequested(int curState)
{
	auto engine = ZegoExpressSDK::getEngine();
	if (engine != nullptr)
	{
		if (curState == ZegoScreenCaptureSettings::PlayState::UnPlay)
		{
			//�ɹ���ȡ���棬��ô��ʼ����
			//QVideoWidget video_play;
			ZegoCanvas zegocanvas = (ZegoView*)(m_CaptureView->winId());
			engine->startPlayingStream(m_userId.toStdString(), &zegocanvas);
			//engine->startPlayingStream(m_userId.toStdString(), nullptr);
			m_settings->updatePlayState(ZegoScreenCaptureSettings::PlayConnecting);
		}
		else if ((curState == ZegoScreenCaptureSettings::PlayConnecting) || (ZegoScreenCaptureSettings::Playing))
		{
			//ֹͣ����
			engine->stopPlayingStream(m_userId.toStdString());
			m_settings->updatePlayState(ZegoScreenCaptureSettings::UnPlay);
		}
		
	}
}
