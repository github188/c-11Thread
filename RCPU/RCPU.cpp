// RCPU.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DeviceManger.h"
#include "ConfigManger.h"
#include "AlarmManger.h"
#include "WebServiceManger.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CConfigManger ConfigManger;
	ConfigManger.Start();

	CDeviceManger DeviceManger;
	DeviceManger.Start();
	HPR_Sleep(1000);
	MangerDeviceInfo testDevice = {0};
	strcpy_s( testDevice.szIp , "10.21.130.51");
	testDevice.iPort = 8000;
	strcpy_s(testDevice.szName, "admin"); 
	strcpy_s(testDevice.szUserName, "admin");
	strcpy_s(testDevice.szPwd, "12345");


	CWebServiceManger WebServiceManger;
	WebServiceManger.Start();

	for (int i = 0; i < 10; i++)
	{
		testDevice.iPort = 8000 +  i;
		DeviceManger.AddDevice(testDevice);
	}

	DeviceManger.AddDevice(testDevice);
	CAlarmManger AlarmManger(&DeviceManger);
	AlarmManger.Start();

	HPR_Sleep(100000);
	AlarmManger.Close();
	
	while (true)
	{
		HPR_Sleep(10000);
	}
	return 0;
}

