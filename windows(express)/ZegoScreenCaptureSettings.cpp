#include "ZegoScreenCaptureSettings.h"
#include "ZegoScreenCaptureSettings_p.h"

#include <QAction>
#include <QRect>
#include <QStringListModel>

ZegoScreenCaptureSettings::ZegoScreenCaptureSettings(QObject *parent)
	: QObject(parent), d_ptr(new ZegoScreenCaptureSettingsPrivate(this))
{
	connect(this, &ZegoScreenCaptureSettings::writeLog_p, this, &ZegoScreenCaptureSettings::WriteLog, Qt::QueuedConnection);
}

ZegoScreenCaptureSettings::~ZegoScreenCaptureSettings()
{
}

void ZegoScreenCaptureSettings::setScreenList(const QVector<QVariantMap>& screens)
{
	Q_D(ZegoScreenCaptureSettings);

	d->m_screenList = screens;

	QStringList screenList;
	QString primaryScreenName;
	int primaryIndex(0), oldSelIndex(-1);
	for (int i = 0; i < screens.size(); i++)
	{
		auto screen = screens[i];
		auto name = screen["name"].toString();
		screenList.push_back(name);
		if (screen["primary"].toBool())
		{
			primaryScreenName = name;
			primaryIndex = i;
		}

		if (d->m_curScreenName == name)
		{
			oldSelIndex = i;
		}
	}
	d->m_screenNameListModel->setStringList(screenList);

	if (d->m_curScreenName.isEmpty() || oldSelIndex < 0)
	{
		d->m_curScreenName = primaryScreenName ;
		emit d->screenIndexChanged_p(primaryIndex);
	}
	else
	{
		emit d->screenIndexChanged_p(oldSelIndex);
	}
}

void ZegoScreenCaptureSettings::setWindowList(const QVector<QVariantMap>& windows)
{
	Q_D(ZegoScreenCaptureSettings);
	
	d->m_windowList = windows;

	QStringList titleList;
	qint64 preferedWindowId = 0;
	int oldSelIndex(-1);
	for (int i = 0; i < windows.size(); i++)
	{
		auto window = windows[i];
		auto title = window["title"].toString();
		titleList.push_back(title);

		qint64 id = window["id"].toLongLong();
		if (i == 0)
		{
			preferedWindowId = id;
		}
		if (d->m_curWindowId == id)
		{
			oldSelIndex = i;
		}
	}
	d->m_windowTitleListModel->setStringList(titleList);

	if (d->m_curWindowId == 0 || oldSelIndex < 0)
	{
		d->m_curWindowId = preferedWindowId;
		emit d->windowIndexChanged_p(0);
	}
	else
	{
		emit d->windowIndexChanged_p(oldSelIndex);
	}
}

void ZegoScreenCaptureSettings::SetCaptureWindow(qint64 id)
{
	Q_D(ZegoScreenCaptureSettings);

	d->m_curWindowId = id;

	emit d->windowCaptureChanged_p(d->m_curWindowId);
}

void ZegoScreenCaptureSettings::WriteLog(const QString& log)
{
	appendLogString(log);
}

void ZegoScreenCaptureSettings::UpdateState(int state)
{
	updatePublishState((PublishState)state);
}

void ZegoScreenCaptureSettings::SetPublishUrl(const QString& rtmp, const QString& hls)
{
	setPublishStreamUrl(rtmp, hls);
}

void ZegoScreenCaptureSettings::setResolutionList(const QVector<QSize>& resolutions, QSize prefered)
{
	Q_D(ZegoScreenCaptureSettings);

	d->m_resolutionList = resolutions;

	QStringList resolutionStringList;
	int oldSelIndex(-1), preferedIndex(0);
	for (int i = 0; i < resolutions.size(); i++)
	{
		auto resolution = resolutions[i];
		resolutionStringList.push_back(QStringLiteral("%1 * %2").arg(resolution.width()).arg(resolution.height()));

		if (resolution == prefered)
		{
			preferedIndex = i;
		}
		if (d->m_curResolution == resolution)
		{
			oldSelIndex = i;
		}
	}
	d->m_resolutionListModel->setStringList(resolutionStringList);

	if (d->m_curResolution.isNull() || oldSelIndex < 0)
	{
		d->m_curResolution = resolutions[preferedIndex];
		emit d->resolutionIndexChanged_p(preferedIndex);
		emit resolutionSelectChanged(prefered);
	}
	else
	{
		emit d->resolutionIndexChanged_p(oldSelIndex);
	}
}

void ZegoScreenCaptureSettings::setDesktopBoundingRect(QRect bounding)
{
	Q_D(ZegoScreenCaptureSettings);
	if (d->m_boundingRect == bounding)
	{
		return;
	}

	d->m_boundingRect = bounding;
	emit d->boundingRectangleChanged_p(bounding);
}

void ZegoScreenCaptureSettings::appendLogString(const QString& log)
{
	if (log.isEmpty()) return;

	Q_D(ZegoScreenCaptureSettings);
	emit d->appendLog_p(log);
}

void ZegoScreenCaptureSettings::setCaptureImage(const QPixmap& pixmap)
{
	Q_D(ZegoScreenCaptureSettings);
	emit d->setCaptureImage_p(pixmap);
}

void ZegoScreenCaptureSettings::setWindowMode(int mode)
{
	m_windowMode = mode;
}

int ZegoScreenCaptureSettings::getWinwowMode()
{
	return m_windowMode;
}

ZegoScreenCaptureSettings::Target ZegoScreenCaptureSettings::currentTarget(void) const
{
	Q_D(const ZegoScreenCaptureSettings);
	return (ZegoScreenCaptureSettings::Target)d->m_target;
}

QString ZegoScreenCaptureSettings::currentScreen(void) const
{
	Q_D(const ZegoScreenCaptureSettings);
	return d->m_curScreenName;
}

qint64 ZegoScreenCaptureSettings::currentWindow(void) const
{
	Q_D(const ZegoScreenCaptureSettings);
	return d->m_curWindowId;
}

QRect ZegoScreenCaptureSettings::currentRectangle(void) const
{
	Q_D(const ZegoScreenCaptureSettings);
	return d->m_rectSliderAction->data().toRect();
}

QSize ZegoScreenCaptureSettings::currentResolution(void) const
{
	Q_D(const ZegoScreenCaptureSettings);
	return d->m_curResolution;
}

ZegoScreenCaptureSettings::CaptureState ZegoScreenCaptureSettings::currentCaptureState(void) const
{
	Q_D(const ZegoScreenCaptureSettings);
	return (CaptureState)d->m_captureState;
}

void ZegoScreenCaptureSettings::updateCaptureState(ZegoScreenCaptureSettings::CaptureState state)
{
	Q_D(ZegoScreenCaptureSettings);

	if (d->m_captureState == state)
		return;

	d->m_captureState = state;
	if (state == CaptureIdle)
	{
		d->m_captureAction->setText(QStringLiteral("开始捕捉"));
		if (d->m_publishState == PublishConnecting || d->m_publishState == Publishing)
		{
			d->m_publishAction->trigger();
		}
	}
	else if (state == CaptureWorking)
	{
		d->m_captureAction->setText(QStringLiteral("停止捕捉"));
	}
}

void ZegoScreenCaptureSettings::updatePublishState(ZegoScreenCaptureSettings::PublishState state)
{
	Q_D(ZegoScreenCaptureSettings);

	if (d->m_publishState == state)
		return;

	//if (d->m_publishState == UnPublish && state == Publishing)
		//return;

	d->m_publishState = state;
	if (state == UnPublish)
	{
		d->m_publishAction->setEnabled(true);
		d->m_publishAction->setText(QStringLiteral("开始推流"));
		emit d->streamUrlChanged_p("", "");
	}
	else if (state == PublishConnecting)
	{
		d->m_publishAction->setEnabled(false);
	}
	else if (state == Publishing)
	{
		d->m_publishAction->setEnabled(true);
		d->m_publishAction->setText(QStringLiteral("停止推流"));
	}
}

void ZegoScreenCaptureSettings::updatePlayState(PlayState state)
{
	Q_D(ZegoScreenCaptureSettings);
	//标记是否正在拉流
	bool bPlay = false;
	if (d->m_playState == state)
		return;

	if ((state == PlayConnecting) && (d->m_playState == PlayState::Playing))
	{
		return;
	}

	d->m_playState = state;
	if ((state == UnPlay)&& (d->m_playState != PlayState::Playing))
	{
		d->m_PlayAction->setEnabled(true);
		d->m_PlayAction->setText(QStringLiteral("开始拉流"));
		//emit d->streamUrlChanged_p("", "");
	}
	else if (state == PlayConnecting)
	{
		d->m_PlayAction->setEnabled(false);
	}
	else if (state == Playing)
	{
		d->m_PlayAction->setEnabled(true);
		d->m_PlayAction->setText(QStringLiteral("停止拉流"));
	}
}


void ZegoScreenCaptureSettings::setPublishStreamUrl(const QString& rtmp, const QString& hls)
{
	Q_D(ZegoScreenCaptureSettings);
	emit d->streamUrlChanged_p(rtmp, hls);
}

ZegoScreenCaptureSettings::PublishState ZegoScreenCaptureSettings::currentPublishState(void) const
{
	Q_D(const ZegoScreenCaptureSettings);
	return (PublishState)d->m_publishState;
}

ZegoScreenCaptureSettingsPrivate::ZegoScreenCaptureSettingsPrivate(ZegoScreenCaptureSettings* parent)
	: QObject(parent), q_ptr(parent)
{
	m_targetSelectAction = Action(new QAction);
	connect(m_targetSelectAction.data(), &QAction::changed, this, [this]() 
	{
		auto action = dynamic_cast<QAction*>(sender());
		if (!action) return;

		if (m_target != action->data().toInt())
		{
			Q_Q(ZegoScreenCaptureSettings);
			m_target = action->data().toInt();
			emit q->targetChanged(m_target);
		}
	});

	m_screenSelectAction = Action(new QAction);
	connect(m_screenSelectAction.data(), &QAction::changed, this, [this]()
	{
		auto action = dynamic_cast<QAction*>(sender());
		if (!action) return;

		int curSel = action->data().toInt();
		auto& varMap = m_screenList[curSel];
		if (m_curScreenName != varMap["name"].toString())
		{
			Q_Q(ZegoScreenCaptureSettings);
			m_curScreenName = varMap["name"].toString();
			emit q->screenSelectChanged(m_curScreenName);
		}
	});

	QString refreshText = QStringLiteral("刷新");
	m_refreshScreenAction = Action(new QAction);
	m_refreshScreenAction->setText(refreshText);
	connect(m_refreshScreenAction.data(), &QAction::triggered,
		this, [this](bool checked) 
	{
		Q_Q(ZegoScreenCaptureSettings);
		emit q->screenRefreshRequested();
	});

	m_windowSelectAction = Action(new QAction);
	connect(m_windowSelectAction.data(), &QAction::changed, this, [this]()
	{
		auto action = dynamic_cast<QAction*>(sender());
		if (!action) return;

		int curSel = action->data().toInt();
		auto& varMap = m_windowList[curSel];
		if (m_curWindowId != varMap["id"].toLongLong())
		{
			Q_Q(ZegoScreenCaptureSettings);
			m_curWindowId = varMap["id"].toLongLong();
			emit q->windowSelectChanged(m_curWindowId);
		}
	});

	m_refreshWindowAction = Action(new QAction);
	m_refreshWindowAction->setText(refreshText);
	connect(m_refreshWindowAction.data(), &QAction::triggered, this, [this](bool checked)
	{
		Q_Q(ZegoScreenCaptureSettings);
		emit q->windowRefreshRequested();
	});

	m_generateRandomRectAction = Action(new QAction);
	m_generateRandomRectAction->setText(QStringLiteral("随机"));
	connect(m_generateRandomRectAction.data(), &QAction::triggered, this, [this](bool checked) 
	{
		auto action = dynamic_cast<QAction*>(sender());
		if (!action || m_boundingRect.isNull())
			return;

		int x = qrand() % m_boundingRect.width();
		int y = qrand() % m_boundingRect.height();
		int w = qrand() % m_boundingRect.width() + 100;
		int h = qrand() % m_boundingRect.height() + 100;
		QRect rect(x, y, w, h);
		if (rect == m_rectSliderAction->data().toRect())
			return;

		m_rectSliderAction->setData(rect);
		emit rectangleChanged_p(rect);

		if (m_target == ZegoScreenCaptureSettings::Rectangle)
		{
			Q_Q(ZegoScreenCaptureSettings);
			emit q->rectangleChanged(rect);
		}
	});

	m_rectSliderAction = Action(new QAction);
	connect(m_rectSliderAction.data(), &QAction::changed, this, [this]() 
	{
		auto action = dynamic_cast<QAction*>(sender());
		if (!action) return;

		if (m_target == ZegoScreenCaptureSettings::Rectangle)
		{
			Q_Q(ZegoScreenCaptureSettings);
			emit q->rectangleChanged(action->data().toRect());
		}
	});

	m_screenNameListModel = StringListModel(new QStringListModel);
	m_windowTitleListModel = StringListModel(new QStringListModel);
	m_resolutionListModel = StringListModel(new QStringListModel);

	m_resolutionSelectAction = Action(new QAction);
	connect(m_resolutionSelectAction.data(), &QAction::changed, this, [this]()
	{
		auto action = dynamic_cast<QAction*>(sender());
		if (!action) return;

		int curSel = action->data().toInt();
		auto resolution = m_resolutionList[curSel];
		if (m_curResolution != resolution)
		{
			Q_Q(ZegoScreenCaptureSettings);
			m_curResolution = resolution;
			emit q->resolutionSelectChanged(m_curResolution);
		}
	});

	m_bitrateSliderAction = Action(new QAction);
	connect(m_bitrateSliderAction.data(), &QAction::changed, this, [this]()
	{
		if (auto action = dynamic_cast<QAction*>(sender()))
		{
			Q_Q(ZegoScreenCaptureSettings);
			int num = action->data().toInt();
			emit q->bitrateChanged(action->data().toInt());
		}
	});

	m_framerateSliderAction = Action(new QAction);
	connect(m_framerateSliderAction.data(), &QAction::changed, this, [this]()
	{
		if (auto action = dynamic_cast<QAction*>(sender()))
		{
			Q_Q(ZegoScreenCaptureSettings);
			emit q->framerateChanged(action->data().toInt());
		}
	});

	m_cursorSwitchAction = Action(new QAction);
	m_cursorSwitchAction->setText(QStringLiteral("显示光标"));
	m_cursorSwitchAction->setCheckable(true);
	connect(m_cursorSwitchAction.data(), &QAction::toggled,
		parent, &ZegoScreenCaptureSettings::cursorToggled);

	m_clickAnimationAction = Action(new QAction);
	m_clickAnimationAction->setText(QStringLiteral("点击动画"));
	m_clickAnimationAction->setCheckable(true);
	connect(m_clickAnimationAction.data(), &QAction::toggled,
		parent, &ZegoScreenCaptureSettings::clickAnimationToggled);

	m_captureAction = Action(new QAction);
	m_captureAction->setText(QStringLiteral("开始捕捉"));
	m_captureAction->setData(0);
	connect(m_captureAction.data(), &QAction::triggered, this, [this](bool) 
	{
		Q_Q(ZegoScreenCaptureSettings);
		emit q->captureRequested(m_captureState);
	});

	m_publishAction = Action(new QAction);
	m_publishAction->setText(QStringLiteral("开始分享"));
	m_publishAction->setData(0);
	connect(m_publishAction.data(), &QAction::triggered, this, [this](bool)
	{
		Q_Q(ZegoScreenCaptureSettings);
		emit q->publishRequested(m_publishState);
	});

	//add
	m_PlayAction = Action(new QAction);
	m_PlayAction->setText(QStringLiteral("开始拉流"));
	connect(m_PlayAction.data(), &QAction::triggered, this, [this](bool) {
		Q_Q(ZegoScreenCaptureSettings);
		emit q->PlayStreamRequested(m_playState);
	});


	m_addExcludedWindowAction = Action(new QAction);
	m_addExcludedWindowAction->setText(QStringLiteral("添加过滤窗口"));
	m_addExcludedWindowAction->setData(0);
	connect(m_addExcludedWindowAction.data(), &QAction::triggered, this, [this](bool)
	{
		Q_Q(ZegoScreenCaptureSettings);
		emit q->addExcludedWindowRequested();
	});

	m_removeExcludedWindowAction = Action(new QAction);
	m_removeExcludedWindowAction->setText(QStringLiteral("移除过滤窗口"));
	m_removeExcludedWindowAction->setData(0);
	connect(m_removeExcludedWindowAction.data(), &QAction::triggered, this, [this](bool)
	{
		Q_Q(ZegoScreenCaptureSettings);
		emit q->removeExcludedWindowRequested();
	});

	m_openThumbnailViewAction = Action(new QAction);
	m_openThumbnailViewAction->setText(QStringLiteral("窗口预览"));
	m_openThumbnailViewAction->setData(0);
	connect(m_openThumbnailViewAction.data(), &QAction::triggered, this, [this](bool)
	{
		Q_Q(ZegoScreenCaptureSettings);
		emit q->thumbnailWindowCapture(m_curWindowId);
	});
}

ZegoScreenCaptureSettingsPrivate::~ZegoScreenCaptureSettingsPrivate()
{
}

void ZegoScreenCaptureSettingsPrivate::bitrateRange(int& min, int& max) const
{
	min = 300 * 1024;
	max = 3000 * 1024;
}

int ZegoScreenCaptureSettingsPrivate::bitrateStep(void) const
{
	return 100 * 1024;
}

void ZegoScreenCaptureSettingsPrivate::framerateRange(int& min, int& max) const
{
	min = 10;
	max = 30;
}

int ZegoScreenCaptureSettingsPrivate::framerateStep(void) const
{
	return 5;
}