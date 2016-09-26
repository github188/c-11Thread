#pragma once
#include "stdafx.h"
#include "MangerInterface.h"

struct MangerDeviceInfo{
	int  iId;
	char szName[128];
	char szIndex[64];
	char szIp[32];
	int  iPort;
	char szUserName[64];
	char szPwd[32];
	char szUpdateTime[32];
	char szRev1[32];
	int  iRev1;
};

class CDeviceManger : public CMangerInterface
{
public:
	CDeviceManger();
	~CDeviceManger();
public:
	int AddDevice(MangerDeviceInfo deviceInfo);
	int DeleteDevice(MangerDeviceInfo deviceInfo);
private:
	int loop();
private:
	std::vector<MangerDeviceInfo> m_CmsDeviceInfo;
	std::vector<MangerDeviceInfo> m_ManualDeviceInfo;
public:
	std::vector<MangerDeviceInfo> GetManualDevice()
	{
		return m_ManualDeviceInfo;
	}
private:
	int GetDeviceFromGSS();
};

