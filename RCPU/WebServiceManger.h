#pragma once
#include "hpr\HPR_Hpr.h"
#include "hlog\hlog1.h"
#include "MangerInterface.h"
#include "commonClass.h"
#include "AlarmManger.h"
#include <vector>
#include <mutex>


enum WebServiceCMD
{
	UploadPicture,
	GetDevice
};

class CConfigManger;

class CWebServiceManger :
	public CMangerInterface
{
public:
	CWebServiceManger(CConfigManger *config);
	~CWebServiceManger();
public:
	int PushMessage(std::pair<int, UpLoadInfo> message);
	std::pair<int, UpLoadInfo> PopMessage();

private:
	int loop();

private:
	std::vector<std::pair<int, UpLoadInfo>> m_vecMessageQueue;
	std::mutex m_mutex;

public:
	CConfigManger *m_configManger;
public:
	int UploadAlarm(UpLoadInfo info);
};

