#pragma once
#include "hpr\HPR_Hpr.h"
#include "hlog\hlog1.h"
#include "MangerInterface.h"
#include <vector>
#include <mutex>

enum WebServiceCMD
{
	TransformPicture,
	GetDevice
};

class AutoLock
{
public:
	AutoLock(std::mutex &mux)
	{
		m_mutex = &mux;
		(*m_mutex).lock();
	}
	~AutoLock()
	{
		(*m_mutex).unlock();
	}
private:
	std::mutex *m_mutex;
};


class CWebServiceManger :
	public CMangerInterface
{
public:
	CWebServiceManger();
	~CWebServiceManger();
public:
	int PushMessage(std::pair<int, std::string> message);

	void testNum()
	{
		AutoLock autoLock(m_mutex);
		for (int i = 0; i < 1000; i++)
		{
			HPR_Sleep(1000);
			this->test = i;
			LOG_INFO("test num is %d", test);
		}
	};

private:
	int loop();
	

private:
	std::vector<std::pair<int, std::string>> m_vecMessageQueue;
	std::mutex m_mutex;

private:
	int test;
};

