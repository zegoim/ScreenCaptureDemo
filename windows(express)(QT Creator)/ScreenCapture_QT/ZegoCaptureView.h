#pragma once

#include <QDialog>
#include "ui_ZegoCaptureView.h"

class ZegoCaptureView : public QDialog
{
	Q_OBJECT

public:
	ZegoCaptureView(QWidget *parent = Q_NULLPTR);
	~ZegoCaptureView();

	void SetCaptureImage(const QPixmap& pixmap);

private:
	Ui::ZegoCaptureView ui;
	QPixmap m_pixmap;
};
