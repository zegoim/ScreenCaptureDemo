#ifndef ZEGOTHUMBNAILVIEW_H
#define ZEGOTHUMBNAILVIEW_H

#include <QDialog>
#include "ui_ZegoThumbnailView.h"


struct ThumbnailInfo
{
	int WinID;
	int ThumbnailID;
	QRect rect;
	QRect rectThumbnail;
	QString strTitle;
	QPixmap  pixmap;
};

class ZegoThumbnailView : public QDialog
{
	Q_OBJECT

public:
	ZegoThumbnailView(QWidget *parent = 0);
	~ZegoThumbnailView();

	int GetCaptureWindow()const;
protected:
	void paintEvent(QPaintEvent *p);
	bool eventFilter(QObject *watched, QEvent *event);
private:
	QVector<QRect> m_rects;
	QVector<ThumbnailInfo> m_Infos;
private:
	Ui::ZegoThumbnailView ui;
	int m_CaptureWinID;
};

#endif // ZEGOTHUMBNAILVIEW_H
