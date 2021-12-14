#include <QApplication>

#include "ZegoScreenCaptureDemo.h"
#include "ZegoScreenCaptureSettings.h"
#include "ZegoScreenCaptureController.h"
#include <QObject>
#include <QRect>
#include <QVector>

int main(int argc, char *argv[])
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);

	QFont defaultFont;
	defaultFont.setFamily(QStringLiteral("Microsoft YaHei"));
	defaultFont.setPixelSize(16);
	app.setFont(defaultFont);

	//������Ļ�ɼ���س�ʼ������
	ZegoScreenCaptureController controller;
	//����Demo�������
	ZegoScreenCaptureDemo widget; 
    //controller.video_play = widget.video_play;
	controller.m_CaptureView = &widget.getView();

	widget.attachSettings(controller.settings());
	widget.show();
	return app.exec();
}