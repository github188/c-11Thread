#pragma once
#include "MangerInterface.h"
class CConfigManger :public CMangerInterface
{
public:
	CConfigManger();
	~CConfigManger();
public:
	void detachThread();

};

