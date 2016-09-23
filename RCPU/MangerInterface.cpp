#include "MangerInterface.h"


CMangerInterface::CMangerInterface()
{
}

CMangerInterface::~CMangerInterface()
{
}

void CMangerInterface::detachThread()
{
	while (!m_isExit)
	{
		loop();
	}
};

int CMangerInterface::loop()
{
	return 0;
};

int CMangerInterface::Start()
{
	this->m_isExit = false;
	MangerThread = std::thread(&CMangerInterface::detachThread, this);
	MangerThread.detach();
	return 0;
};

int CMangerInterface::Close()
{
	this->m_isExit = true;
	MangerThread.~thread();
	return 0;
};