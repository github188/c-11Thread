#include "DeviceManger.h"
#include "MangerInterface.h"

#if 1
//ʹ������webservice�ӿ�
#include "WebServiceInterface\DeviceInfoService_Defines.h"
#include "WebServiceInterface\DeviceInfoService_Services.h"
#include "WebServiceInterface\DeviceInfoService_stub.h"
#else
//ʹ��վ��webservice�ӿ�
//...
#endif

#include "hlog\hlog.h"
#include "hpr\HPR_Hpr.h"

CDeviceManger::CDeviceManger()
{

}

CDeviceManger::~CDeviceManger()
{

}

int CDeviceManger::AddDevice(MangerDeviceInfo deviceInfo)
{
	if (&deviceInfo == NULL)
		return -1;
	if (m_ManualDeviceInfo.size() > 0)
	{
		std::vector<MangerDeviceInfo>::iterator iter = m_ManualDeviceInfo.begin();
		for (; iter != m_ManualDeviceInfo.end(); iter++)
		{
			if (strcmp((*iter).szIp, deviceInfo.szIp) == 0 &&
				(*iter).iPort == deviceInfo.iPort)
			{
				if (strcmp((*iter).szUserName, deviceInfo.szUserName) == 0 &&
					strcmp((*iter).szPwd, deviceInfo.szPwd) == 0)
				{
					//LOG_INFO("Device is exist! name : %s , ip : %s ,port : %d", deviceInfo.szName, deviceInfo.szIp, deviceInfo.iPort);
					
					return 1;
				}
				else
				{
					m_ManualDeviceInfo.erase(iter);
					break;
				}
			}
		}
	}
	
	LOG_INFO("Add New Device: name : %s , ip : %s ,port : %d", deviceInfo.szName, deviceInfo.szIp, deviceInfo.iPort);
	m_ManualDeviceInfo.push_back(deviceInfo);
	return 0;
}

int CDeviceManger::DeleteDevice(MangerDeviceInfo deviceInfo)
{
	if (&deviceInfo == NULL)
		return -1;
	std::vector<MangerDeviceInfo>::iterator iter = m_ManualDeviceInfo.begin();
	for (; iter != m_ManualDeviceInfo.end(); iter++)
	{
		if ((*iter).szIp == deviceInfo.szIp && (*iter).szPwd == deviceInfo.szPwd)
		{
			LOG_INFO("Del Device: name : %s , ip : %s ,port : %d", 
				deviceInfo.szName, deviceInfo.szIp, deviceInfo.iPort);
			m_ManualDeviceInfo.erase(iter);
			return 0;
		}
	}
	LOG_INFO("del device is not exit!");
	return 1;
}

int CDeviceManger::loop()
{
	int nRet = 0;
	{
		//ѭ����cms����ץ�Ļ�
		GetDeviceFromGSS();
		HPR_Sleep(60000);
		m_bDeviceChange = false;
	}
	return 0;
}

int CDeviceManger::GetDeviceFromGSS()
{
	int iRet = HPR_ERROR;
	std::string url = "http://10.21.130.223:80/services/DeviceInfoService?wsdl";
	char szUrl[256] = { 0 };

	//��configGSS.xml�����ļ���ȡip��ַ�Ͷ˿�
	//url��configGSS.xml��ȡ���Ժ���ķ��㣬������Ĵ���
	//std::string tempUrl = "http://%s:%d/gcs/services/DeviceInfoService?wsdl";
	//��װurl
	//sprintf(szUrl, tempUrl.c_str(), strGssIp.c_str(), iGssPort);
	//std::string url = szUrl;
	//��ʼ��webservice�ӿڣ���ȡ�豸�ӿ�
	if (!DeviceInfoService_Init(NULL))
	{
		LOG_ERROR("DeviceInfoService_Init ��ʼ��ʧ��!");
		return HPR_ERROR;
	}

	//����webservice��ȡ�豸��Ϣ
	cmsws_soap*  pSap = DeviceInfoService_GetSoapEnv();
	if (pSap != NULL)
	{
		pSap->accept_timeout = 2;
		pSap->recv_timeout = 2;
		pSap->send_timeout = 2;
		pSap->connect_timeout = 2;
	}
	else
	{
		LOG_ERROR("DeviceInfoService_GetSoapEnv ����Ϊ��!");
		return HPR_ERROR;
	}

#if 0
	
	bool isFindAll = false;
	int iPage = 1;
	int iPageSize = 200;
	do
	{
		Stru_getDvrInfo deviceInfo;
		deviceInfo.pageNum = iPage;
		deviceInfo.pageSize = iPageSize;
		Stru_getDvrInfoResponse * response = DeviceInfoService_getAllDeviceInfo(url.c_str(), &deviceInfo);

		if (response == NULL)
		{
			int errorCode = 0;
			const char* errorReason;
			const char* errorDetail;
			DeviceInfoService_GetLastError(&errorCode, &errorReason, &errorDetail);
			LOG_ERROR("��ȡץ�Ļ��豸��Ϣʧ�ܣ�DeviceInfoService_getVehicleInfo  errorCode = %d,errorReason = %s, errorDetail = %s [%s]", errorCode, errorReason, errorDetail, szUrl);
			break;
		}
		else if (response->iErrorCode != 0)
		{
			LOG_ERROR("��ȡץ�Ļ��豸��Ϣʧ�� [%s]", szUrl);
			break;
		}

		for (int j = 0; j < response->iInfoNum; ++j)
		{
			if (response->pInfo != NULL)
			{
				MangerDeviceInfo newDevInfo = { 0 };
				memcpy_s(&newDevInfo, sizeof(DeviceInfo), &response->pInfo[j], sizeof(DeviceInfo));
				m_CmsDeviceInfo.push_back(newDevInfo);
			}
		}

		iRet = HPR_OK;
		if (response->currentPage == response->totalPage)
		{
			isFindAll = !isFindAll;
		}
		else
		{
			iPage++;
		}
		LOG_DEBUG("��ȡץ�Ļ��豸��Ϊ:%d", response->iInfoNum);

	} while (!isFindAll);
#else
	do 
    {
        Stru_getDvrInfoResponse * response = DeviceInfoService_getAllDeviceInfo(url.c_str());
        if (response == NULL)
        {
            int errorCode = 0;
            const char* errorReason;
            const char* errorDetail;
            DeviceInfoService_GetLastError(&errorCode, &errorReason, &errorDetail); 
            LOG_ERROR("��ȡץ�Ļ��豸��Ϣʧ�ܣ�DeviceInfoService_getVehicleInfo  errorCode = %d,errorReason = %s, errorDetail = %s [%s]",errorCode,  errorReason, errorDetail, szUrl);
            break;
        }
        else if (response->iErrorCode != 0)
        {
            LOG_ERROR("��ȡץ�Ļ��豸��Ϣʧ�� [%s]",szUrl );
            break;
        }
        for (int j = 0; j < response->iInfoNum; ++j)
        {  
            if (response->pInfo != NULL)
            { 
				MangerDeviceInfo  newDevInfo = {0};
				memcpy_s(&newDevInfo, sizeof(MangerDeviceInfo), &response->pInfo[j], sizeof(MangerDeviceInfo));
				//m_CmsDeviceInfo.push_back(newDevInfo);
				AddDevice(newDevInfo);
            }
        }
		LOG_DEBUG("��ȡץ�Ļ��豸��Ϊ:%d", response->iInfoNum);
		m_bDeviceChange = true;
        iRet = HPR_OK;
    } while (0);

#endif

	//�ͷ���ʱ���ٵĿռ�
	DeviceInfoService_FreeTemporaryData();
	DeviceInfoService_Uninit();
	return iRet;
}
