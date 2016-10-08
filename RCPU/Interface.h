#pragma once
#include "stdafx.h"

class CConfigManger;
class CWebServiceManger;
class CPMSManger;
class CDeviceManger;
class CAlarmManger;

class CInterface
{
public:
	CInterface();
	~CInterface();
public:
	void Start();
	void Close();
private:
	CConfigManger *ConfigManger;
	CWebServiceManger *WebServiceManger;
	CPMSManger *PMSManger;
	CDeviceManger *DeviceManger;
	CAlarmManger *AlarmManger;
};

