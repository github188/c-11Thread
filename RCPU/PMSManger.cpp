#include "PMSManger.h"
#include "hlog\hlog.h"
#include "AlarmManger.h"
#include "WebServiceManger.h"
#include "ConfigManger.h"
#define DEBUG 1

CPMSManger::CPMSManger()
{
	
}

CPMSManger::~CPMSManger()
{

}

int CPMSManger::Start()
{
	CMangerInterface::Start();
	
	m_strPmsIp = m_webServiceManger->m_configManger->GetPmsIp();
	m_iPmsPort = m_webServiceManger->m_configManger->GetPmsPort();

	if (EC_OK != initPms())
	{
		LOG_ERROR("init Pms error!");
		return HPR_ERROR;
	}
	//连接pms
	if (EC_OK != vs_conn_pms(m_strPmsIp.c_str(), m_iPmsPort, &m_iPmsHandle))
	{
		//LOG_ERROR("vs_conn_pms fail %s:%d m_iPmsHandle:%d", m_strPmsIp.c_str(), m_iPmsPort, m_iPmsHandle);
		return HPR_ERROR;
	}
	else
	{
		//LOG_ERROR("vs_conn_pms sucess %s:%d m_iPmsHandle:%d", m_strPmsIp.c_str(), m_iPmsPort, m_iPmsHandle);
	}
	vs_set_timeout(1000, 2000);

	return 0;
}

int CPMSManger::Close()
{
	CMangerInterface::Close();

	if (EC_OK != vs_disconn(m_iPmsHandle))
	{
		//LOG_ERROR("vs_disconn fail %s:%d m_iPmsHandle:%d", m_strPmsIp.c_str(), m_iPmsPort, m_iPmsHandle);
		return HPR_ERROR;
	}

	if (EC_OK != uinitPms())
	{
		//LOG_ERROR("uinit Pms error!");
	}
	
	return HPR_OK;
}

int CPMSManger::loop()
{
	if (m_vecUpLoad.size() > 0)
	{
		UpLoadInfo upLoadInfo = frontUpLoadQueue();

		VRB_ERROR_CODE error_code(EC_ERROR);
		if (upLoadInfo.pBigPicData == NULL)
		{
			//LOG_ERROR("pBigPicData is NULL!");
		}
		else
		{
			char url[VRB_MAX_PIC_URL_LEN] = { 0 };

#if DEBUG
			//LOG_INFO("pData : %s, length %d", upLoadInfo.pBigPicData, upLoadInfo.uiBigPicLen);
#endif

			error_code = vs_upload_pic(m_iPmsHandle, upLoadInfo.pBigPicData, upLoadInfo.uiBigPicLen, NULL, url, NULL);
			if (EC_OK != error_code)
			{
				LOG_ERROR("上传[%s:%d]失败error_code=%d m_iPmsHandle:%d", m_strPmsIp.c_str(), m_iPmsPort, error_code, m_iPmsHandle);
			}
			else
			{
				upLoadInfo.strBigPicUrl = "http://";
				upLoadInfo.strBigPicUrl += m_strPmsIp;
				upLoadInfo.strBigPicUrl += ":";
				char sPort[MAX_PATH] = { 0 };
				HPR_Snprintf(sPort, MAX_PATH, "%d", m_iPmsPort);
				upLoadInfo.strBigPicUrl += sPort;
				upLoadInfo.strBigPicUrl += url;
				LOG_INFO("上传图片长度:%d 成功 返回地址[http://%s:%d%s] m_iPmsHandle:%d", upLoadInfo.uiBigPicLen, m_strPmsIp.c_str(), m_iPmsPort, url, m_iPmsHandle);
				
			}
		}

		if (upLoadInfo.pSmallPicData == NULL)
		{
			//LOG_ERROR("pBigPicData is NULL!");

		}
		else
		{
			char url[VRB_MAX_PIC_URL_LEN] = { 0 };
#if DEBUG
			//LOG_INFO("pData : %s, length %d", upLoadInfo.pSmallPicData, upLoadInfo.uiSmallLen);
#endif

			error_code = vs_upload_pic(m_iPmsHandle, upLoadInfo.pSmallPicData, upLoadInfo.uiSmallLen, NULL, url, NULL);
			if (EC_OK != error_code)
			{
				LOG_ERROR("上传[%s:%d]失败error_code=%d m_iPmsHandle:%d", m_strPmsIp.c_str(), m_iPmsPort, error_code, m_iPmsHandle);
			}
			else
			{
				upLoadInfo.strSmallPicUrl = "http://";
				upLoadInfo.strSmallPicUrl += m_strPmsIp;
				upLoadInfo.strSmallPicUrl += ":";
				char sPort[MAX_PATH] = { 0 };
				HPR_Snprintf(sPort, MAX_PATH, "%d", m_iPmsPort);
				upLoadInfo.strSmallPicUrl += sPort;
				upLoadInfo.strSmallPicUrl += url;
				LOG_INFO("上传图片长度:%d 成功 返回地址[http://%s:%d%s] m_iPmsHandle:%d", upLoadInfo.uiSmallLen, m_strPmsIp.c_str(), m_iPmsPort, url, m_iPmsHandle);
			}
		}
		uploadToCMS(upLoadInfo);
	}
	else
		HPR_Sleep(1000);
	return 0;
}

int CPMSManger::initPms()
{	
	return vs_init();
}

int CPMSManger::uinitPms()
{
	return vs_fini();
}

int CPMSManger::UpLoadPic(UpLoadInfo info)
{
	pushUpLoadQueue(info);
	return 0;
}

void CPMSManger::pushUpLoadQueue(UpLoadInfo info)
{
	AutoLock autoLock(m_mutex);
	if (m_vecUpLoad.size() < 1000)
		m_vecUpLoad.push_back(info);
}

UpLoadInfo CPMSManger::frontUpLoadQueue()
{
	AutoLock autoLock(m_mutex);
	UpLoadInfo tempInfo;
	if (m_vecUpLoad.size() > 0)
	{
		tempInfo = m_vecUpLoad.front();
		m_vecUpLoad.erase(m_vecUpLoad.begin());
		return tempInfo;
	}
	else
	{
		return tempInfo;
	}
}

int CPMSManger::SetPmsConfig(std::string pmsIp, int pmsPort)
{
	m_strPmsIp = pmsIp;
	m_iPmsPort = pmsPort;
	return 0;
}

void CPMSManger::uploadToCMS(UpLoadInfo info)
{
	std::pair<int, UpLoadInfo> message(UploadPicture,info);
	m_webServiceManger->PushMessage(message);
}