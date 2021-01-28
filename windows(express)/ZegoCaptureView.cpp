#include "ZegoCaptureView.h"
#include <QImage>
#include<QPainter>
#include<QDesktopWidget>

ZegoCaptureView::ZegoCaptureView(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

ZegoCaptureView::~ZegoCaptureView()
{
}

void ZegoCaptureView::SetCaptureImage(const QPixmap& pixmap)
{
	//m_pixmap = pixmap;
	//update();
	HWND h = (HWND)winId();
	int n = 0;
}

//void ZegoCaptureView::paintEvent(QPaintEvent *p)
//{
//	QPainter painter(this);
//
//	QRect screenRect = geometry();
//
//	QPixmap fitpixmap = m_pixmap.scaled(screenRect.width(), screenRect.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//
//	painter.drawPixmap(0, 0, fitpixmap);
//
//	//painter.drawText(screenRect, Qt::AlignCenter | Qt::AlignLeft, "12345");
//}

