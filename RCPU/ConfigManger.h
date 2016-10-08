#pragma once
#include "MangerInterface.h"

class CMarkupSTL;
class CConfigManger :public CMangerInterface
{
public:
	CConfigManger();
	~CConfigManger();
public:
	void detachThread();

private:
	void loadXml(std::string fileName);
	void loopRead(CMarkupSTL markup);
	void readConfig(std::string nodeName, std::string markupData);
private:
	std::string m_strLocalIp;
	std::string m_strCmsIp;
	std::string m_strCmsPort;
	int m_iCmsPort;
	std::string m_strPmsIp;
	int m_iPmsPort;
public:
	std::string GetLocalIp()
	{
		return m_strLocalIp;
	};

	std::string GetCmsIp()
	{
		return m_strCmsIp;
	};

	int GetCmsPort()
	{
		return m_iCmsPort;
	};

	std::string GetCmsPortStr()
	{
		return m_strCmsPort;
	};

	std::string GetPmsIp()
	{
		return m_strPmsIp;
	};

	

	int GetPmsPort()
	{
		return m_iPmsPort;
	};
};

