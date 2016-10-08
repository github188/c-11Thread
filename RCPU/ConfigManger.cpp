#include "stdafx.h"
#include "ConfigManger.h"
#include "markup\markup.h"

const char* ConfigFileName = "RCPU.xml";

CConfigManger::CConfigManger()
{
	m_strLocalIp = "127.0.0.1";
	m_strCmsIp = "127.0.0.1";
	m_strPmsIp = "127.0.0.1";
	m_iCmsPort = 80;
	m_iPmsPort = 8088;
}

CConfigManger::~CConfigManger()
{
}

void CConfigManger::loopRead(CMarkupSTL markup)
{
	int i = 1;
	while (markup.FindNode(i))
	{
		LOG_INFO("%s", markup.GetTagName().c_str());
		while (markup.FindChildElem())
		{
			LOG_INFO("%s", markup.GetChildTagName().c_str());
			readConfig(markup.GetChildTagName().c_str(), markup.GetChildData().c_str());
			loopRead(markup);
		}
		i++;
	}
}

void CConfigManger::loadXml(std::string fileName)
{
	CMarkupSTL markupXml;
	markupXml.Load(fileName.c_str());

	if (markupXml.FindElem("config"))
	{
		markupXml.IntoElem();
		loopRead(markupXml);
	}
	else
	{
		LOG_ERROR("loadXml error! can't find Config elem!");
	}
}

void CConfigManger::detachThread()
{
	std::cout << "CConfigManger mainLoop" << std::endl;
	hlog_init("log4cxx.properties");
	loadXml(ConfigFileName);
}



void CConfigManger::readConfig(std::string nodeName, std::string markupData) 
{
	if (nodeName == "localIp")
	{
		m_strLocalIp = markupData;
		return;
	}
	else if(nodeName == "cmsIp")
	{
		m_strCmsIp = markupData;
		return;
	}
	else if (nodeName == "pmsIp")
	{
		m_strPmsIp = markupData;
		return;
	}
	else if (nodeName == "cmsPort")
	{
		m_strCmsPort = markupData.c_str();
		m_iCmsPort = atoi(markupData.c_str());
		return;
	}
	else if (nodeName == "pmsPort")
	{
		m_iPmsPort = atoi(markupData.c_str());
		return;
	}
}
