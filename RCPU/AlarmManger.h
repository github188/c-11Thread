#pragma once
#ifndef ALARM_MANGER
#define ALARM_MANGER
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
	int iPalteType;//车辆归属，-1：普通车，0重要车辆，1逃单车辆，2危险车辆
	unsigned int uiBigPicLen;
	unsigned int uiSmallLen;
	NET_DVR_PLATE_INFO  struPlateInfo;    //车牌信息结构
	NET_DVR_VEHICLE_INFO struVehicleInfo; //车辆信息
	std::string strCameraName;
	std::string strIp;
	std::string strBigPicUrl;
	std::string strSmallPicUrl;
	char* pBigPicData;
	char* pSmallPicData;
	std::string strHapentTime;
	std::string strPmsUrl;
}UpLoadInfo;

class CPMSManger;
class CAlarmManger:public CMangerInterface
{
public:
	CAlarmManger();
	CAlarmManger(CDeviceManger *pDevice,CPMSManger *pPms)
	{
		m_deviceManger = pDevice;
		m_pmsManger = pPms;
		NET_DVR_Init();
	};

	~CAlarmManger();
public:
	virtual int loop();
	virtual int Close();
public:
	int LoginDevice(MangerDeviceInfo deviceInfo);
	int LogoutDevice();

public:
	int UpLoadPicToPms(UpLoadInfo upLoadInfo);
private:
	int transformColor(int color);

	std::vector<MangerDeviceInfo>  m_vDeviceManger;
	std::vector<LoginHandleManger> m_vLoginHandle;
private:
	CDeviceManger *m_deviceManger;
	CPMSManger *m_pmsManger;
};
#endif
