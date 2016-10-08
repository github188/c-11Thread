// RCPU.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Interface.h"

CInterface task;

int _tmain(int argc, _TCHAR* argv[])
{
	task.Start();

	
	//MangerDeviceInfo testDevice = { 0 };
	//strcpy_s(testDevice.szIp, "10.21.130.51");
	//testDevice.iPort = 8000;
	//strcpy_s(testDevice.szName, "admin");
	//strcpy_s(testDevice.szUserName, "admin");
	//strcpy_s(testDevice.szPwd, "12345");

	//for (int i = 0; i < 5; i++)
	//{
	//	testDevice.iPort = 8000 + i;
	//	DeviceManger.AddDevice(testDevice);
	//}

	//DeviceManger.AddDevice(testDevice);

	//HPR_Sleep(10000);
	//AlarmManger.Close();
	
	while (1)
	{
		HPR_Sleep(10000);
	}
	return 0;
}

