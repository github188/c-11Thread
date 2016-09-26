#pragma once
#include "stdafx.h"
#include "DeviceManger.h"
#include "HCNetSDK\HCNetSDK.h"

typedef struct 
{
	int loginId;
	int alarmHandle;
	std::string ip;
	int port;
}LoginHandleManger;

enum PICTURE_TYPE
{
	PLATE_TYPE,
	CAR_TYPE
};

typedef struct{
	int  iPort;
	int  iChannel;
	int iPalteType;//����������-1����ͨ����0��Ҫ������1�ӵ�������2Σ�ճ���
	unsigned int uiBigPicLen;
	unsigned int uiSmallLen;
	NET_DVR_PLATE_INFO  struPlateInfo;    //������Ϣ�ṹ
	NET_DVR_VEHICLE_INFO struVehicleInfo; //������Ϣ
	std::string szCameraName;
	std::string szIp;
	std::string szBigPicUrl;
	std::string szSmallPicUrl;
	std::string pBigPicData;
	std::string pSmallPicData;
	std::string szHapentTime;
}UpLoadInfo;

class CAlarmManger:public CMangerInterface
{
public:
	CAlarmManger();
	CAlarmManger(CDeviceManger *pDevice)
	{
		m_deviceManger = pDevice;
		NET_DVR_Init();
	};

	~CAlarmManger();
public:
	int loop();
	int Close();
public:
	int LoginDevice(MangerDeviceInfo deviceInfo);
	int LogoutDevice();
private:
	int transformColor(int color);

	std::vector<MangerDeviceInfo>  m_vDeviceManger;
	std::vector<LoginHandleManger> m_vLoginHandle;
private:
	CDeviceManger *m_deviceManger;
};

