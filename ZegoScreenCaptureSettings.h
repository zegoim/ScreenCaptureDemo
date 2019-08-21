#pragma once

#include <QObject>
#include <QRect>

class ZegoScreenCaptureDemo;
class ZegoScreenCaptureSettingsPrivate;

class ZegoScreenCaptureSettings : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(ZegoScreenCaptureSettings)

public:
	enum Target
	{
		Screen = 1,
		Window,
		Rectangle,
	};

	enum CaptureState
	{
		CaptureIdle,
		CaptureWorking,
	};

	enum PublishState
	{
		UnPublish,
		PublishConnecting,
		Publishing,
	};

public:
	ZegoScreenCaptureSettings(QObject *parent = Q_NULLPTR);
	~ZegoScreenCaptureSettings(void);

	void setScreenList(const QVector<QVariantMap>& screens);
	void setWindowList(const QVector<QVariantMap>& windows);
	void setResolutionList(const QVector<QSize>& resolutions, QSize prefered);
	void setDesktopBoundingRect(QRect bounding);
	void appendLogString(const QString& log);
	

	Target currentTarget(void) const;
	QString currentScreen(void) const;
	qint64 currentWindow(void) const;
	QRect currentRectangle(void) const;
	QSize currentResolution(void) const;

	CaptureState currentCaptureState(void) const;
	void updateCaptureState(CaptureState state);
	PublishState currentPublishState(void) const;
	void updatePublishState(PublishState state);
	void setPublishStreamUrl(const QString& rtmp, const QString& hls);
Q_SLOT void SetCaptureWindow(qint64 id);
Q_SIGNALS:
	void targetChanged(int target);
	void screenRefreshRequested(void);
	void screenSelectChanged(const QString& name);
	void windowRefreshRequested(void);
	void windowSelectChanged(qint64 id);
	void resolutionSelectChanged(QSize resolution);
	void rectangleChanged(QRect geometry);
	void bitrateChanged(int bitrate);
	void framerateChanged(int framerate);
	void cursorToggled(bool checked);
	void clickAnimationToggled(bool checked);
	void captureRequested(int curState);
	void publishRequested(int curState);
	void addExcludedWindowRequested(void);
	void removeExcludedWindowRequested(void);
	void thumbnailWindowCapture(qint64 id);

private:
	friend ZegoScreenCaptureDemo;
	QScopedPointer<ZegoScreenCaptureSettingsPrivate> d_ptr;
};