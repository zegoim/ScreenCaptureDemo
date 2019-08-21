#include <QApplication>

#include "ZegoScreenCaptureDemo.h"
#include "ZegoScreenCaptureSettings.h"
#include "ZegoScreenCaptureController.h"

int main(int argc, char *argv[])
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QApplication app(argc, argv);

	QFont defaultFont;
	defaultFont.setFamily(QStringLiteral("Microsoft YaHei"));
	defaultFont.setPixelSize(16);
	app.setFont(defaultFont);

	ZegoScreenCaptureController controller;
	ZegoScreenCaptureDemo widget;
	widget.attachSettings(controller.settings());
	widget.show();
	return app.exec();
}