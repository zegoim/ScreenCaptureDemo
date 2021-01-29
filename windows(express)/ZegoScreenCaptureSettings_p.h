#pragma once

#include <QObject>
#include <QRect>
#include <QVector>
#include <QVariantMap>
#include <QSharedPointer>

class QAction;
class QStringListModel;

class ZegoScreenCaptureSettings;
class ZegoScreenCaptureDemo;

using Action = QSharedPointer<QAction>;
using StringListModel = QSharedPointer<QStringListModel>;

class ZegoScreenCaptureSettingsPrivate : public QObject
{
	Q_OBJECT
	Q_DECLARE_PUBLIC(ZegoScreenCaptureSettings)

public:
	ZegoScreenCaptureSettingsPrivate(ZegoScreenCaptureSettings *parent);
	~ZegoScreenCaptureSettingsPrivate(void);

	Action targetSelectAction(void) const { return m_targetSelectAction; }
	Action refreshScreenAction(void) const { return m_refreshScreenAction; }
	Action refreshWindowAction(void) const { return m_refreshWindowAction; }
	Action generateRandomRectAction(void) const { return m_generateRandomRectAction; }
	Action rectSilderAction(void) const { return m_rectSliderAction; }
	QRect boundingRectangle(void) const { return m_boundingRect;  }

	StringListModel screenNameListModel(void) const { return m_screenNameListModel; }
	Action screenSelectAction(void) const { return m_screenSelectAction; }
	StringListModel windowTitleListModel(void) const { return m_windowTitleListModel; }
	Action windowSelectAction(void) const { return m_windowSelectAction; }

	StringListModel resolutionModel(void) const { return m_resolutionListModel; }
	Action resolutionSelectAction(void) const { return m_resolutionSelectAction; }
	void bitrateRange(int& min, int& max) const;
	int bitrateStep(void) const;
	Action bitrateAction(void) const { return m_bitrateSliderAction; }
	void framerateRange(int& min, int& max) const;
	int framerateStep(void) const;
	Action framerateAction(void) const { return m_framerateSliderAction; }

	Action cursorSwitchAction(void) const { return m_cursorSwitchAction; }
	Action clickAnimationSwitchAction(void) const { return m_clickAnimationAction; }

	Action captureAction(void) const { return m_captureAction; }
	Action publishAction(void) const { return m_publishAction; }
	Action addExcludedWindowAction(void) const { return m_addExcludedWindowAction; }
	Action removeExcludedWindowAction(void) const { return m_removeExcludedWindowAction; }
	Action openThumbnailViewAction(void) const { return m_openThumbnailViewAction; }

	//Ôö¼Ó
	Action PlayAction(void) const { return m_PlayAction; }

	Q_SIGNAL void screenIndexChanged_p(int index);
	Q_SIGNAL void windowIndexChanged_p(int index);
	Q_SIGNAL void resolutionIndexChanged_p(int index);
	Q_SIGNAL void boundingRectangleChanged_p(QRect rect);
	Q_SIGNAL void rectangleChanged_p(QRect rect);
	Q_SIGNAL void appendLog_p(const QString& log);
	Q_SIGNAL void setCaptureImage_p(const QPixmap& pixmap);
	Q_SIGNAL void streamUrlChanged_p(const QString& rtmp, const QString& hls);
	Q_SIGNAL void windowCaptureChanged_p(qint64 id);

protected:
	Action m_targetSelectAction;
	int m_target = 0;

	Action m_refreshScreenAction;
	Action m_refreshWindowAction;
	Action m_generateRandomRectAction;
	Action m_rectSliderAction;
	QRect m_boundingRect;

	QVector<QVariantMap> m_screenList;
	StringListModel m_screenNameListModel;
	Action m_screenSelectAction;
	QString m_curScreenName;

	QVector<QVariantMap> m_windowList;
	StringListModel m_windowTitleListModel;
	Action m_windowSelectAction;
	qint64 m_curWindowId = 0;

	QVector<QSize> m_resolutionList;
	StringListModel m_resolutionListModel;
	Action m_resolutionSelectAction;
	QSize m_curResolution;

	Action m_bitrateSliderAction;
	Action m_framerateSliderAction;
	
	Action m_cursorSwitchAction;
	Action m_clickAnimationAction;

	Action m_captureAction;
	int m_captureState = 0;

	Action m_publishAction;
	int m_publishState = 0;

	Action m_PlayAction;
	int m_playState = 0;


	Action m_addExcludedWindowAction;
	Action m_removeExcludedWindowAction;
	Action m_openThumbnailViewAction;

private:
	ZegoScreenCaptureSettings* q_ptr = nullptr;
};

