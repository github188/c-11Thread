#pragma once
#include "stdafx.h"


class CMangerInterface{
public:
	CMangerInterface();
	virtual ~CMangerInterface();
public:
	virtual void detachThread();
	virtual int loop();
	virtual int Start();
	virtual int Close();

private:
	std::thread MangerThread;
private:
	bool m_isExit;
};
