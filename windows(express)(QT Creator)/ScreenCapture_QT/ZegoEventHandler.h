#pragma once
#include <QObject>
#include <QDebug>
#include "ZegoExpressEventHandler.h"
#include "ZegoExpressDefines.h"
using namespace ZEGO::EXPRESS;

class ZegoEventHandler : public QObject, public ZEGO::EXPRESS::IZegoEventHandler
{
	Q_OBJECT
public:
	ZegoEventHandler(QObject *parent = Q_NULLPTR);
	~ZegoEventHandler(void);

	enum PlayState
	{
		UnPlay,
		PlayConnecting,
		Playing,
	};

	void onPublisherStateUpdate(const std::string& streamID, ZEGO::EXPRESS::ZegoPublisherState state, int errorCode, const std::string& extendedData) override;
	void onPublisherQualityUpdate(const std::string& streamID, const ZEGO::EXPRESS::ZegoPublishStreamQuality& quality) override;
	void onPlayerStateUpdate(const std::string& streamID, ZegoPlayerState state, int errorCode, const std::string& extendedData) override;

	Q_SIGNAL void publishStateChanged_p(int state);
	Q_SIGNAL void WriteLog_p(const QString log);
	Q_SIGNAL void setPublishStreamUrl_p(const QString& rtmp, const QString& hls);
	Q_SIGNAL void updatePlayState_p(int state);
};