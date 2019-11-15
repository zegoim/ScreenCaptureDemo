#include "ZegoScreenCaptureDemo.h"
#include "ZegoScreenCaptureSettings.h"
#include "ZegoScreenCaptureSettings_p.h"

#include <QStringListModel>

// helper function
void attachButton(QToolButton* button, Action action)
{
	if (!button || action.isNull())
		return;

	if (button->defaultAction() == action)
		return;

	button->removeAction(action.data());
	button->setDefaultAction(action.data());
}

//////////////////////////////////////////////////////////////////////////////////
ZegoScreenCaptureDemo::ZegoScreenCaptureDemo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(720, 480);
	setWindowTitle(QStringLiteral("ZEGO桌面分享/外部采集Demo"));
}

ZegoScreenCaptureDemo::~ZegoScreenCaptureDemo()
{
}

// attach the settings model to ui
void ZegoScreenCaptureDemo::attachSettings(ZegoScreenCaptureSettings* settings)
{
	if (!settings) return;

	// capture settings
	connectTargetSelectAction(settings->d_func()->targetSelectAction());

	attachButton(ui.btn_refresh_screen, settings->d_func()->refreshScreenAction());
	attachButton(ui.btn_refresh_window, settings->d_func()->refreshWindowAction());
	attachButton(ui.btn_random_rect, settings->d_func()->generateRandomRectAction());
	attachButton(ui.btn_add_excluded_window, settings->d_func()->addExcludedWindowAction());
	attachButton(ui.btn_remove_excluded_window, settings->d_func()->removeExcludedWindowAction());
	//attachButton(ui.btn_thumbnail, settings->d_func()->openThumbnailViewAction());

	connect(ui.btn_thumbnail, &QToolButton::clicked, this, &ZegoScreenCaptureDemo::onOpenThumbnailView);
	connect(this, &ZegoScreenCaptureDemo::SetThumbnailWindow, settings, &ZegoScreenCaptureSettings::thumbnailWindowCapture);

	connectRectSlider(settings->d_func()->rectSilderAction());
	onBoundingRectangleChanged(settings->d_func()->boundingRectangle());

	ui.combo_screen->setModel(settings->d_func()->screenNameListModel().data());
	connectComboBox(ui.combo_screen, settings->d_func()->screenSelectAction());
	connect(settings->d_func(), &ZegoScreenCaptureSettingsPrivate::screenIndexChanged_p, 
		ui.combo_screen, &QComboBox::setCurrentIndex);

	ui.combo_window->setModel(settings->d_func()->windowTitleListModel().data());
	connectComboBox(ui.combo_window, settings->d_func()->windowSelectAction());
	connect(settings->d_func(), &ZegoScreenCaptureSettingsPrivate::windowIndexChanged_p,
		ui.combo_window, &QComboBox::setCurrentIndex);
	
	// misc settings
	ui.combo_resolution->setModel(settings->d_func()->resolutionModel().data());
	connectComboBox(ui.combo_resolution, settings->d_func()->resolutionSelectAction());
	connect(settings->d_func(), &ZegoScreenCaptureSettingsPrivate::resolutionIndexChanged_p,
		ui.combo_resolution, &QComboBox::setCurrentIndex);

	int min(0), max(0);
	settings->d_func()->bitrateRange(min, max);
	ui.slider_bitrate->setRange(min, max);
	ui.slider_bitrate->setSingleStep(settings->d_func()->bitrateStep());
	connectVideoSettingsSlider(QStringLiteral("bitrate"), settings->d_func()->bitrateAction());

	settings->d_func()->framerateRange(min, max);
	ui.slider_framerate->setRange(min, max);
	ui.slider_framerate->setSingleStep(settings->d_func()->framerateStep());
	connectVideoSettingsSlider(QStringLiteral("framerate"), settings->d_func()->framerateAction());

	connectCheckBox(ui.check_cursor, settings->d_func()->cursorSwitchAction());
	connectCheckBox(ui.check_clickanimation, settings->d_func()->clickAnimationSwitchAction());

	// capture and publish action
	attachButton(ui.btn_capture, settings->d_func()->captureAction());
	attachButton(ui.btn_publish, settings->d_func()->publishAction());

	connect(settings->d_func(), &ZegoScreenCaptureSettingsPrivate::boundingRectangleChanged_p,
		this, &ZegoScreenCaptureDemo::onBoundingRectangleChanged);
	connect(settings->d_func(), &ZegoScreenCaptureSettingsPrivate::rectangleChanged_p,
		this, &ZegoScreenCaptureDemo::onRectangleChanged);
	// edit text update
	connect(settings->d_func(), &ZegoScreenCaptureSettingsPrivate::appendLog_p,
		this, &ZegoScreenCaptureDemo::onAppendLog);
	connect(settings->d_func(), &ZegoScreenCaptureSettingsPrivate::streamUrlChanged_p, 
		this, &ZegoScreenCaptureDemo::onStreamUrlChanged, Qt::QueuedConnection);

	///////////////////////////////////////////////////////////////////////////////////////////////
	// init params
	settings->d_func()->refreshScreenAction()->trigger();
	settings->d_func()->refreshWindowAction()->trigger();
	settings->d_func()->generateRandomRectAction()->trigger();
	ui.slider_bitrate->setValue(1500 * 1024);
	ui.slider_framerate->setValue(15);
	ui.check_cursor->setCheckState(Qt::Checked);
	ui.check_clickanimation->setCheckState(Qt::Checked);
	ui.radio_screen->setChecked(true);

	settings->setResolutionList({ QSize(640, 360), QSize(854, 480), QSize(1280, 720), QSize(1920, 1080), QSize(720, 1280) },
		QSize(1280, 720));
}

void ZegoScreenCaptureDemo::onBoundingRectangleChanged(QRect rect)
{
	ui.slider_x->setRange(rect.left(), rect.right());
	ui.slider_y->setRange(rect.top(), rect.bottom());
	ui.slider_w->setRange(0, rect.width());
	ui.slider_h->setRange(0, rect.height());
}

void ZegoScreenCaptureDemo::onRectangleChanged(QRect rect)
{
	ui.slider_x->setValue(rect.x());
	ui.label_x->setText(QStringLiteral("x: %1").arg(rect.x()));
	ui.slider_y->setValue(rect.y());
	ui.label_y->setText(QStringLiteral("y: %1").arg(rect.y()));

	ui.slider_w->setValue(rect.width());
	ui.label_w->setText(QStringLiteral("w: %1").arg(rect.width()));
	ui.slider_h->setValue(rect.height());
	ui.label_h->setText(QStringLiteral("h: %1").arg(rect.height()));
}

void ZegoScreenCaptureDemo::onAppendLog(const QString& log)
{
	ui.list_log->addItem(log);
	ui.list_log->scrollToBottom();
}

void ZegoScreenCaptureDemo::onStreamUrlChanged(const QString& rtmp, const QString& hls)
{
	ui.edit_rtmpurl->setText(rtmp);
	ui.edit_hlsurl->setText(hls);
}
void ZegoScreenCaptureDemo::onOpenThumbnailView()
{
	m_ThumbnailView.exec();
	int WinID = m_ThumbnailView.GetCaptureWindow();
	emit SetThumbnailWindow(WinID);
}

void ZegoScreenCaptureDemo::connectTargetSelectAction(QSharedPointer<QAction> action)
{
	auto weakAction = action.toWeakRef();
	ui.radio_screen->disconnect(this);
	connect(ui.radio_screen, &QRadioButton::toggled, this, [weakAction](bool checked)
	{
		auto action = weakAction.lock();
		if (checked && action)
		{
			action->setData(ZegoScreenCaptureSettings::Screen);
		}
	});

	ui.radio_window->disconnect(this);
	connect(ui.radio_window, &QRadioButton::toggled, this, [weakAction](bool checked)
	{
		auto action = weakAction.lock();
		if (checked && action)
		{
			action->setData(ZegoScreenCaptureSettings::Window);
		}
	});

	ui.radio_rect->disconnect(this);
	connect(ui.radio_rect, &QRadioButton::toggled, this, [weakAction](bool checked) 
	{
		auto action = weakAction.lock();
		if (checked && action)
		{
			action->setData(ZegoScreenCaptureSettings::Rectangle);
		}
	});
}

void ZegoScreenCaptureDemo::connectRectSlider(QSharedPointer<QAction> action)
{
	auto weakAction = action.toWeakRef();
	auto onSliderChanged = [this, weakAction](int value)
	{
		if (auto action = weakAction.lock())
		{
			auto curRect = action->data().toRect();
			auto sliderRect = QRect(ui.slider_x->value(), ui.slider_y->value(),
				ui.slider_w->value(), ui.slider_h->value());
			
			if (curRect != sliderRect)
			{
				action->setData(sliderRect);
				ui.label_x->setText(QStringLiteral("x: %1").arg(sliderRect.x()));
				ui.label_y->setText(QStringLiteral("y: %1").arg(sliderRect.y()));
				ui.label_w->setText(QStringLiteral("w: %1").arg(sliderRect.width()));
				ui.label_h->setText(QStringLiteral("h: %1").arg(sliderRect.height()));
			}
		}
	};

	ui.slider_x->disconnect(this);
	connect(ui.slider_x, &QSlider::valueChanged, this, onSliderChanged);

	ui.slider_y->disconnect(this);
	connect(ui.slider_y, &QSlider::valueChanged, this, onSliderChanged);

	ui.slider_w->disconnect(this);
	connect(ui.slider_w, &QSlider::valueChanged, this, onSliderChanged);

	ui.slider_h->disconnect(this);
	connect(ui.slider_h, &QSlider::valueChanged, this, onSliderChanged);
}

void ZegoScreenCaptureDemo::connectComboBox(QComboBox* combobox, QSharedPointer<QAction> action)
{
	if (!combobox || action.isNull())
		return;

	combobox->disconnect(this);
	auto weakAction = action.toWeakRef();
	connect(combobox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), 
		this, [weakAction](int index)
	{
		if (index < 0)
			return;

		if (auto action = weakAction.lock())
		{
			action->setData(index);
		}
	});
}

void ZegoScreenCaptureDemo::connectCheckBox(QCheckBox* checkbox, QSharedPointer<QAction> action)
{
	if (!checkbox || action.isNull())
		return;

	checkbox->disconnect(this);
	auto weakAction = action.toWeakRef();
	connect(checkbox, &QCheckBox::stateChanged, this, [weakAction](int state) 
	{
		if (auto action = weakAction.lock())
		{
			action->setChecked(state != Qt::Unchecked);
		}
	});
}

void ZegoScreenCaptureDemo::connectVideoSettingsSlider(const QString& name, QSharedPointer<QAction> action)
{
	if (name.isEmpty() || action.isNull())
		return;

	auto slider = findChild<QSlider*>(QStringLiteral("slider_%1").arg(name));
	if (!slider)
		return;

	slider->disconnect(this);
	auto weakAction = action.toWeakRef();
	connect(slider, &QSlider::valueChanged, this, [this, name, weakAction](int value)
	{
		if (auto label = findChild<QLabel*>(QStringLiteral("label_%1").arg(name)))
		{
			int k = value / 1024;
			label->setText(k > 0 ? QStringLiteral("%1k").arg(k) : QStringLiteral("%1").arg(value));
		}

		if (auto action = weakAction.lock())
		{
			action->setData(value);
		}
	});
}