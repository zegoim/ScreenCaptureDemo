#pragma once

#include <QObject>
#include "LiveRoom.h"
#include "video_capture.h"

class ZegoExternalCaptureDevice : public QObject, public AVE::VideoCaptureDevice
{
	Q_OBJECT
public:
	ZegoExternalCaptureDevice();
	virtual ~ZegoExternalCaptureDevice();
	friend class ScreenCaptureCallback;

public:
	bool IsCapturing(void) const;
	AVE::VideoCaptureDevice::Client* Client(void);

	virtual void AllocateAndStart(AVE::VideoCaptureDevice::Client* client);
	virtual void StopAndDeAllocate();

	virtual int StartCapture();
	virtual int StopCapture();

	virtual int SetFrameRate(int framerate);
	virtual int SetResolution(int width, int height);
	virtual int SetFrontCam(int bFront);
	virtual int SetView(void *view);
	virtual int SetViewMode(int nMode);
	virtual int SetViewRotation(int nRotation);
	virtual int SetCaptureRotation(int nRotation);
	virtual int StartPreview();
	virtual int StopPreview();
	virtual int EnableTorch(bool bEnable);
	virtual int TakeSnapshot();
	virtual int SetPowerlineFreq(unsigned int nFreq);

private:
	AVE::VideoCaptureDevice::Client* m_veClient = nullptr;
	bool m_isCapturing = false;
};

class ZegoExternalCaptureFactory :
	public QObject,
	public AVE::VideoCaptureFactory
{
	Q_OBJECT

public:
	ZegoExternalCaptureFactory(QObject* parent);
	virtual ~ZegoExternalCaptureFactory();

	virtual AVE::VideoCaptureDevice* Create(const char* device_id);
	virtual void Destroy(AVE::VideoCaptureDeviceBase *vc);

	ZegoExternalCaptureDevice* Device(void);

	Q_SIGNAL void sigDeviceCreated(void);
	Q_SIGNAL void sigDeviceDestroyed(void);

private:
	ZegoExternalCaptureDevice* m_captureDevice = nullptr;
};