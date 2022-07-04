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


static unsigned int g_rtmp_appid = /*appid*/;
static unsigned char g_rtmp_signkey[] = /*appsign*/;


ZegoScreenCaptureController::ZegoScreenCaptureController(QObject *parent)
	: QObject(parent), m_settings(new ZegoScreenCaptureSettings(this))
{
	m_userId = QStringLiteral("%1").arg(qrand() % 10000000);

	init();

	// ���ԣ������߳�ͬ��
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
	// ��InitSDKǰ��ȷ��ʹ���ⲿ�ɼ�ģʽ����SDK���ṩ��Ƶ����Դ���������Ƶ���ݼ����滭�棬Ĭ��ΪMainChannel
	m_externalCaptureFactory = new ZegoExternalCaptureFactory(this);
	ZEGO::LIVEROOM::SetVideoCaptureFactory(m_externalCaptureFactory);
	bRet = ZEGO::LIVEROOM::SetLogDir(logDir);
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
	ZEGO::LIVEROOM::StopPublishing();
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

	QString desc = QStringLiteral("## ��״̬��� > %1 ##").arg(stateCode);
	m_settings->appendLogString(desc);

	// �ص����½���Ҫ�л��߳�
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

	// ��������ʵʱͳ��
	QString desc = QStringLiteral("#### ʵʱͳ�� [%1] ����: %2 ֡��: %3 ����: %4 ###")
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

	// ���������SDK�ص������滭�棬ֱ�Ӵ�������ƵSDK����
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
	// ���ڲ�׽�Ĵ���λ�ñ仯���ɹ�UI����ʹ�ã���Dmeoû���õ�
}

void ZegoScreenCaptureController::OnCaptureError(enum ZegoScreenCaptureCaptureError error, void *user_data)
//void ZegoScreenCaptureController::OnCaptureError(int nErrorCode)
{
	ZegoScreenCaptureController *pThis = (ZegoScreenCaptureController *)user_data;
	if (!pThis)
		return;

	// ���沶׽�쳣ֹͣ��������ʾ�����ε���Ŀ�괰�ڱ��ص�
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
	// ���쳣ֹͣ�ɼ���Ϊ��ģ��ֹͣ��׽��ť����
	onUiCaptureRequested(ZegoScreenCaptureSettings::CaptureWorking);
}

void ZegoScreenCaptureController::onUiTargetChanged(int target)
{
	qDebug() << "onUiTargetChanged " << target;

	if (target == ZegoScreenCaptureSettings::Screen)
	{
		// ��ѡ�����������Ļ���򽫵�ǰ���õ���Ļ���ƴ���
		zego_screencapture_set_target_screen(m_settings->currentScreen().toUtf8().data());
	}
	else if (target == ZegoScreenCaptureSettings::Window)
	{
		// ��ѡ�����ĳ�����ڣ��򽫵�ǰ���õĴ��ھ������
		zego_screencapture_set_target_window((void*)m_settings->currentWindow());
	}
	else if (target == ZegoScreenCaptureSettings::Rectangle)
	{
		// ��ѡ�����ĳ�������򽫵�ǰ���õ�����������괫��
		QRect rect = m_settings->currentRectangle();
		zego_screencapture_set_target_rect(0,rect.x(), rect.y(), rect.width(), rect.height());
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
		zego_screencapture_set_target_screen(name.toUtf8().data());
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
	//ZEGO::LIVEROOM::SetVideoCaptureResolution(resolution.width(), resolution.height());

	ZEGO::LIVEROOM::SetVideoEncodeResolution(resolution.width(), resolution.height());
}

void ZegoScreenCaptureController::onUiBitrateChanged(int bitrate)
{
	qDebug() << "onUiBitrateChanged " << bitrate;

	// ������������
	ZEGO::LIVEROOM::SetVideoBitrate(bitrate);
}

void ZegoScreenCaptureController::onUiFramerateChanged(int framerate)
{
	qDebug() << "onUiFramerateChanged " << framerate;

	// �����������Ĳɼ�֡�ʣ���OnCapturedFrameAvailableÿ��ص�����
	zego_screencapture_set_fps(framerate);

	// ͬʱ��������֡��
	ZEGO::LIVEROOM::SetVideoFPS(framerate);

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

	if (curState == ZegoScreenCaptureSettings::UnPublish)
	{
		// �ڿ�ʼ����ǰ��ʼ����������׽����
		if (m_settings->currentCaptureState() == ZegoScreenCaptureSettings::CaptureIdle)
		{
			onUiCaptureRequested(ZegoScreenCaptureSettings::CaptureIdle);
		}

		//m_userId = QStringLiteral("%1").arg(qrand() % 10000000);

		// ��ʼ����������ʹ�ü�������Ϊ��������������ò�Ҫ���������ַ��Լ�URL�ؼ���
		// ������״̬�仯�Լ�����ַ��OnPublishStateUpdate�лص�
		ZEGO::LIVEROOM::StartPublishing(m_userId.toUtf8(), m_userId.toUtf8(),ZEGO::LIVEROOM::ZegoPublishFlag::ZEGO_SINGLE_ANCHOR);
		m_settings->updatePublishState(ZegoScreenCaptureSettings::PublishConnecting);
	}
	else if (curState == ZegoScreenCaptureSettings::PublishConnecting ||
		curState == ZegoScreenCaptureSettings::Publishing)
	{
		// ֹͣ���������Ͽ���ֹͣ
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

	// �ڿ�ʼ����ǰ��ʼ����������׽����
	if (m_settings->currentCaptureState() == ZegoScreenCaptureSettings::CaptureIdle)
	{
		onUiCaptureRequested(ZegoScreenCaptureSettings::CaptureIdle);
	}

	//m_userId = QStringLiteral("%1").arg(qrand() % 10000000);

	// ��ʼ����������ʹ�ü�������Ϊ��������������ò�Ҫ���������ַ��Լ�URL�ؼ���
	// ������״̬�仯�Լ�����ַ��OnPublishStateUpdate�лص�
	ZEGO::LIVEROOM::StartPublishing(m_userId.toUtf8(), m_userId.toUtf8(), ZEGO::LIVEROOM::ZegoPublishFlag::ZEGO_SINGLE_ANCHOR);
	m_settings->updatePublishState(ZegoScreenCaptureSettings::PublishConnecting);
}