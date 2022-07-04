#include "ZegoEventHandler.h"

ZegoEventHandler::ZegoEventHandler(QObject *parent): QObject(parent)
{

}

ZegoEventHandler::~ZegoEventHandler()
{

}

void ZegoEventHandler::onPublisherStateUpdate(const std::string& streamID, ZEGO::EXPRESS::ZegoPublisherState state, int errorCode, const std::string& extendedData)
{
	QString desc = QStringLiteral("## ��״̬��� > %1 ##").arg(state);
	emit WriteLog_p(desc);

	//�����ʱ�����ɹ�����ô��չ���ݻ����RTMP��hls�ĵ�ַ����ӡ��ʾ����
	if (!extendedData.empty() && (extendedData != "{}"))
	{
		std::string strRtmpUrl = "rtmp_url_list";
		std::string strHlsUrl = "hls_url_list";

		//rtmp
		uint iPos1 = extendedData.find(strRtmpUrl);
		uint iPos2 = extendedData.find("[", iPos1 + 1);
		uint iPos3 = extendedData.find("]", iPos2 + 1);
		if (iPos3 - iPos2 - 3 > 0)
		{
			strRtmpUrl = extendedData.substr(iPos2 + 2, iPos3 - iPos2 - 3);
		}

		//hls
		iPos1 = extendedData.find(strHlsUrl, iPos3);
		iPos2 = extendedData.find("[", iPos3 + 1);
		iPos3 = extendedData.find("]", iPos2 + 1);
		if (iPos3 - iPos2 - 3 > 0)
		{
			strHlsUrl = extendedData.substr(iPos2 + 2, iPos3 - iPos2 - 3);
		}

		emit setPublishStreamUrl_p(QString(strRtmpUrl.c_str()), QString(strHlsUrl.c_str()));

	}

	// �ص����½���Ҫ�л��߳�
	emit publishStateChanged_p((int)state);
}

void ZegoEventHandler::onPublisherQualityUpdate(const std::string& streamID, const ZEGO::EXPRESS::ZegoPublishStreamQuality& quality)
{
	if (streamID.empty())
		return;

	// ��������ʵʱͳ��
	QString desc = QStringLiteral("#### ʵʱͳ�� [%1] ����: %2 ֡��: %3 ����: %4 ####")
		.arg(QString(streamID.c_str())).arg(quality.level).arg(quality.videoSendFPS).arg(quality.videoKBPS);
	emit WriteLog_p(desc);
}

void ZegoEventHandler::onPlayerStateUpdate(const std::string& streamID, ZegoPlayerState state, int errorCode, const std::string& extendedData)
{
	PlayState mystate;
	//���°�ť״̬����������״̬
	switch (state)
	{
	case ZEGO::EXPRESS::ZEGO_PLAYER_STATE_NO_PLAY:
		mystate = UnPlay;
		break;
	case ZEGO::EXPRESS::ZEGO_PLAYER_STATE_PLAY_REQUESTING:
		mystate = PlayConnecting;
		break;
	case ZEGO::EXPRESS::ZEGO_PLAYER_STATE_PLAYING:
		mystate = Playing;
		break;
	default:
		break;
	}
	emit updatePlayState_p(mystate);
	//�����ɹ�����ô��ӡ�ɹ���ʾ��Ϣ
	if (mystate == Playing)
	{
		qDebug() << QString("PlayStream Successful!");
	}
	//�����չ����
	qDebug() << QString(extendedData.c_str());
}
