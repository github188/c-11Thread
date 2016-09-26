#include "stdafx.h"
#include "ConfigManger.h"

CConfigManger::CConfigManger()
{
}

CConfigManger::~CConfigManger()
{
}

void CConfigManger::detachThread()
{
	std::cout << "CConfigManger mainLoop" << std::endl;
	hlog_init("log4cxx.properties");
}
