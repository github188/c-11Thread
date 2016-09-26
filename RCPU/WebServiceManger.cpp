#include "WebServiceManger.h"

CWebServiceManger::CWebServiceManger()
{
	test = 0;
}


CWebServiceManger::~CWebServiceManger()
{
}

int CWebServiceManger::loop()
{
	AutoLock autoLock(m_mutex);
	if (m_vecMessageQueue.size() > 0)
	{
		std::pair<int, std::string> tempVec = m_vecMessageQueue.front();
		switch (tempVec.first)
		{
		case TransformPicture:

			break;
		case GetDevice:

			break;
		default:
			break;
		}
	}
	else
	{
		LOG_ERROR("m_vecMessageQueue is NULL");
	}
	HPR_Sleep(1000);
	return 0;
}

int CWebServiceManger::PushMessage(std::pair<int, std::string> message)
{
	int nRet = 0;
	AutoLock autoLock(m_mutex);
	m_vecMessageQueue.push_back(message);
	return nRet;
}
