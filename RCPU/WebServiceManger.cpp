#include "WebServiceManger.h"
#include "ConfigManger.h"
#include "WebServiceInterface\VehicleInfoService_Defines.h"
#include "WebServiceInterface\VehicleInfoService_Services.h"
#include "WebServiceInterface\VehicleInfoService_stub.h"

CWebServiceManger::CWebServiceManger(CConfigManger *config)
{
	m_configManger = config;
}


CWebServiceManger::~CWebServiceManger()
{

}


int CWebServiceManger::loop()
{
	if (m_vecMessageQueue.size() > 0)
	{
		std::pair<int, UpLoadInfo> tempPair = PopMessage();
		switch (tempPair.first)
		{
		case UploadPicture:
			UploadAlarm(tempPair.second);
			break;
		case GetDevice:

			break;
		default:
			break;
		}
	}
	else
	{
		//LOG_ERROR("m_vecMessageQueue is NULL");
		HPR_Sleep(1000);
	}
	return 0;
}

int CWebServiceManger::PushMessage(std::pair<int, UpLoadInfo> message)
{
	AutoLock autoLock(m_mutex);
	int nRet = 0;
	m_vecMessageQueue.push_back(message);
	return nRet;
}
std::pair< int, UpLoadInfo> CWebServiceManger::PopMessage()
{
	AutoLock autoLock(m_mutex);
	std::pair< int, UpLoadInfo> pairRet;
	if (m_vecMessageQueue.size() > 0)
	{
		pairRet = m_vecMessageQueue.front();
		m_vecMessageQueue.erase(m_vecMessageQueue.begin());
	}
	return pairRet;
}


int CWebServiceManger::UploadAlarm(UpLoadInfo info)
{
	std::string url = "http://";
	url += m_configManger->GetCmsIp();
	url += ":";
	url += m_configManger->GetCmsPortStr();
	url += "/services/VehicleInfoService?wsdl";
	

	/*std::string strGssIp = CResModule::GetInstance()->GetGssIp();
	int iGssPort = CResModule::GetInstance()->GetGssPort();
	sprintf(szUrl, "http://%s:%d/services/VehicleInfoService?wsdl", strGssIp.c_str(), iGssPort);*/

	if (!VehicleInfoService_Init(NULL))
	{
		LOG_ERROR("VehicleInfoService_Init error 失败");
		return HPR_ERROR;
	}

	cmsws_soap*  pSap = VehicleInfoService_GetSoapEnv();
	pSap->accept_timeout = 2;
	pSap->recv_timeout = 2;
	pSap->send_timeout = 2;
	pSap->connect_timeout = 2;

	Stru_saveVehicleEventReq req = { 0 };
	req.iCarType = info.struVehicleInfo.byVehicleType;
	req.iCarColor = info.struVehicleInfo.byColor;
	req.iPlateAttr = info.iPalteType;
	req.iPlateColor = info.struPlateInfo.byColor;
	req.iPort = info.iPort;
	req.iChannel = info.iChannel;
	strncpy(req.szIp, info.strIp.c_str(), info.strIp.length());
	strncpy(req.szCameraName, info.strCameraName.c_str(), info.strCameraName.length());
	strncpy(req.szBigPicUrl, info.strBigPicUrl.c_str(), info.strBigPicUrl.length());
	strncpy(req.szSmallPicUrl, info.strSmallPicUrl.c_str(), info.strSmallPicUrl.length());
	strncpy(req.szstartEndTime, info.strHapentTime.c_str(), info.strHapentTime.length());
	strncpy(req.sLicense, info.struPlateInfo.sLicense, sizeof(info.struPlateInfo.sLicense));
	if (VehicleInfoService_saveVehicleRecordAndAlarm(&req, url.c_str()) != 0)
	{
		int errorCode = 0;
		const char* errorReason;
		const char* errorDetail;
		VehicleInfoService_GetLastError(&errorCode, &errorReason, &errorDetail);
		//LOG_ERROR("上报过车数据失败！VehicleInfoService_saveVehicleRecordAndAlarm  errorCode = %d,errorReason = %s, errorDetail = %s [webservices:%s]", errorCode, errorReason, errorDetail, url.c_str());
	}
	else
	{
		//LOG_DEBUG("前端设备[%s]上报过车数据成功[%s] big : %s small : %s", req.szIp, req.sLicense, req.szBigPicUrl, req.szSmallPicUrl);
	}

	//释放临时开辟的空间
	VehicleInfoService_FreeTemporaryData();
	VehicleInfoService_Uninit();
	return 0;
}
