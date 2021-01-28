#pragma once

#include <QWidget>
#include "ui_ZegoScreenCaptureDemo.h"
#include "ZegoThumbnailView.h"

class ZegoScreenCaptureSettings;

class ZegoScreenCaptureDemo : public QWidget
{
	Q_OBJECT

public:
	ZegoScreenCaptureDemo(QWidget *parent = Q_NULLPTR);
	~ZegoScreenCaptureDemo(void);

	void attachSettings(ZegoScreenCaptureSettings* settings);

protected slots:
	void onBoundingRectangleChanged(QRect rect);
	void onRectangleChanged(QRect rect);
	void onAppendLog(const QString& log);
	void onStreamUrlChanged(const QString& rtmp, const QString& hls);
	void onOpenThumbnailView();

protected:
	void connectTargetSelectAction(QSharedPointer<QAction> action);
	void connectRectSlider(QSharedPointer<QAction> action);
	void connectComboBox(QComboBox* combobox, QSharedPointer<QAction> action);
	void connectCheckBox(QCheckBox* checkbox, QSharedPointer<QAction> action);
	void connectVideoSettingsSlider(const QString& name, QSharedPointer<QAction> action);
Q_SIGNAL void SetThumbnailWindow(int id);
private:
	ZegoThumbnailView		m_ThumbnailView;
private:
	Ui::ZegoScreenCaptureDemo ui;
};