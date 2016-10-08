#pragma once
#include <mutex>
#include "MangerInterface.h"
#include "pms\VRBSDK.h"
#include "commonClass.h"
#include "AlarmManger.h"

class CWebServiceManger;

class CPMSManger 
	: public CMangerInterface
{
public:
	CPMSManger();
	CPMSManger(CWebServiceManger *webservice)
	{
		m_webServiceManger = webservice;
	}

	~CPMSManger();
public:
	int Start();
	int Close();
	
public:
	int UpLoadPic(UpLoadInfo info);
	int SetPmsConfig(std::string pmsIp, int pmsPort);
public:
	int loop();
private:
	int initPms();
	int uinitPms();
private:
	void pushUpLoadQueue(UpLoadInfo info);
	UpLoadInfo frontUpLoadQueue();

private:
	VRB_HANDLE m_iPmsHandle;
	std::string m_strPmsIp;
	int m_iPmsPort;
	std::vector<UpLoadInfo> m_vecUpLoad;
	std::mutex m_mutex;
private:
	CWebServiceManger *m_webServiceManger;
private:
	void uploadToCMS(UpLoadInfo info);
};

