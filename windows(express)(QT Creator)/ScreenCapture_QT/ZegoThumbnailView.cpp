#include "ZegoThumbnailView.h"
#include"zego-windowthumbnail.h"
#include<QDesktopWidget>
#include<QPainter>

ZegoThumbnailView::ZegoThumbnailView(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowTitle(QStringLiteral("����Ԥ��"));

	QDesktopWidget* desktopWidget = QApplication::desktop();
	// 	//��ȡ���������С  
	// 	QRect deskRect = desktopWidget->availableGeometry();
	//��ȡ�豸��Ļ��С  
	QRect screenRect = desktopWidget->screenGeometry();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			QRect rect;
			rect.setLeft(j*screenRect.width() / 8 + j * 10);
			rect.setTop(i*screenRect.height() / 8 + i * 40);
			rect.setRight(screenRect.width() / 8 + 10 + rect.left());
			rect.setBottom(screenRect.height() / 8 + 40 + rect.top());
			m_rects.push_back(rect);
		}
	}
	setFixedSize(m_rects[0].width() * 4, m_rects[0].height() * 4);

	installEventFilter(this);
	//ע��ص�����׽�´��ڽ������ٺͱ���ı��¼�
	zego_windowthumbnail_reg_window_status_change_notify(ThumbnailWindowCallBack, this);
}

ZegoThumbnailView::~ZegoThumbnailView()
{

}

void ZegoThumbnailView::paintEvent(QPaintEvent *p)
{
	QPainter painter(this);
	for (const auto& it : m_Infos)
	{
		QRect rect;
		rect.setLeft(it.rectThumbnail.left());
		rect.setTop(it.rectThumbnail.bottom() + 5);
		rect.setRight(it.rectThumbnail.right());
		rect.setBottom(it.rectThumbnail.bottom() + 40);
		painter.drawText(rect, Qt::AlignCenter | Qt::AlignLeft, it.strTitle);
	}
}

int ZegoThumbnailView::GetCaptureWindow()const
{
	return m_CaptureWinID;
}


void ZegoThumbnailView::ThumbnailWindowCallBack(enum ZegoThumbnailWindowStatus status_code, struct ZegoThumbnailWindowInfo* window_info, void *user_data)
{
	if (status_code == kZegoThumbnailWindowStatusDestroy)
	{
		if (window_info)
		{
			zego_windowthumbnail_unregister(window_info->thumbnail_id);
		}
	}

	if (status_code == kZegoThumbnailWindowStatusCreate)
	{
		zego_windowthumbnail_register(0, window_info->thumbnail_id, 0, 0);
	}
	
}

bool ZegoThumbnailView::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QPoint coursePoint;
		coursePoint = QCursor::pos();//��ȡ��ǰ����λ��
		coursePoint = QWidget::mapFromGlobal(coursePoint);
		for (const auto& it : m_Infos)
		{
			if (it.rectThumbnail.contains(coursePoint))
			{
// 				m_CaptureWinID = it.WinID;
// 				zego_windowthumbnail_show_source_window((ZegoWindowHandle)it.WinID, kZegoThumbnailShowWindowCmdShow);
				this->hide();
				break;
			}
		}
	}
	else if (event->type() == QEvent::Paint)
	{
		//paintEvent(NULL);
		return false;
	}
	else if (event->type() == QEvent::Show)
	{
		m_CaptureWinID = NULL;
		int iCount = 0;
		ZegoThumbnailWindowInfo *info = zego_windowthumbnail_find_windows(&iCount);

		std::vector<ZegoThumbnailWindowInfo> v;
		for (int i = 0; i < iCount; i++)
		{
			v.push_back(info[i]);

			if (info[i].image_bits)
			{
				if (info[i].image_bits->bits)
				{
					QImage image(info[i].image_bits->bits, abs(info[i].image_bits->width), abs(info[i].image_bits->height), QImage::Format_ARGB32);

					QString s = QStringLiteral("C:\\work\\%1ͼƬ.bmp").arg(info[i].window_title);

					s = "C:\\work\\111111111111111.bmp";

					image.save(s);
				}
			}

			if (info[i].icon_bits)
			{
				if (info[i].icon_bits->bits)
				{
					QImage image(info[i].icon_bits->bits, abs(info[i].icon_bits->width), abs(info[i].icon_bits->height), QImage::Format_ARGB32);

					QString s = QStringLiteral("C:\\work\\%1ͼ��.bmp").arg(info[i].window_title);

					s = "C:\\work\\22222222222222222.bmp";
					image.save(s);
				}
			}
		}

		//ֻע��ǰ16������
		int ShowCount = iCount > 16 ? 16 : iCount;

		for (int i = 0; i < ShowCount; i++)
		{
			ZegoScreenCaptureRect rect;
			rect.left = m_rects[m_Infos.size()].left() + 5;
			rect.top = m_rects[m_Infos.size()].top() + 5;
			rect.right = m_rects[m_Infos.size()].right() - 5;
			rect.bottom = m_rects[m_Infos.size()].bottom() - 35;
			if (zego_windowthumbnail_register((ZegoWindowHandle)this->winId(), info[i].thumbnail_id, &rect,NULL))
			{

				ThumbnailInfo Info;
				Info.WinID = (int)info[i].handle;
				Info.ThumbnailID = info[i].thumbnail_id;
				Info.strTitle = QString::fromUtf8(info[i].window_title);
				Info.rect = m_rects[i];
				Info.rectThumbnail.setLeft(rect.left);
				Info.rectThumbnail.setTop(rect.top);
				Info.rectThumbnail.setRight(rect.right);
				Info.rectThumbnail.setBottom(rect.bottom);
				if (info[i].icon_bits)
				{
					//����ͼ������
					Info.pixmap = QPixmap::fromImage(QImage(info[i].icon_bits->bits, info[i].icon_bits->width, info[i].icon_bits->height, QImage::Format_ARGB32));
				}

				m_Infos.push_back(Info);
			}
		}

		for (int i = 16; i < iCount; i++)
		{
			zego_windowthumbnail_register(NULL, info[i].thumbnail_id, NULL, NULL);
		}

		zego_windowthumbnail_free_windows(info, iCount);
	}
	else if (event->type() == QEvent::Hide)
	{
		for (const auto& it : m_Infos)
		{
			zego_windowthumbnail_unregister(it.ThumbnailID);
		}
		m_Infos.clear();
	}
	return __super::eventFilter(watched, event);
}