#include "AlarmManger.h"
#include "PMSManger.h"
#include "hpr\HPR_Time.h"
//回调函数
void CALLBACK AlarmMessage2PicCallBack(LONG  lCommand, NET_DVR_ALARMER  *pAlarmer, char  *pAlarmInfo, DWORD  dwBufLen, void  *pUser);

CAlarmManger::CAlarmManger()
{

}


CAlarmManger::~CAlarmManger()
{
	
}

int CAlarmManger::Close()
{
	CMangerInterface::Close();
	LogoutDevice();
	return 0;
}

int CAlarmManger::loop()
{
	int nRet = HPR_OK;

	if (m_deviceManger->DeviceIsChange())
	{
		std::vector<MangerDeviceInfo>  tempDevice = m_deviceManger->GetManualDevice();
		std::vector<MangerDeviceInfo>::iterator  iterDeivice = tempDevice.begin();
		for (; iterDeivice != tempDevice.end(); iterDeivice++)
		{
			std::vector<MangerDeviceInfo>::iterator iterLogin = m_vDeviceManger.begin();
			for (; iterLogin != m_vDeviceManger.end(); iterLogin++)
			{
				if (strcpy_s((*iterLogin).szIp, (*iterDeivice).szIp) == 0 && (*iterDeivice).iPort == (*iterLogin).iPort)
				{
					//LOG_INFO("device is login!");
					nRet = HPR_ERROR;
					break;
				}
			}
			if (HPR_OK == nRet)
			{
				//LOG_INFO("device start login!");
				if (HPR_OK == LoginDevice(*iterDeivice))
				{
					m_vDeviceManger.push_back(*iterDeivice);
				}
				////LOG_INFO("device login end!");
			}
		}
	}
	else
	{
		HPR_Sleep(1000);
	}
		
	return nRet;
}

//回调函数
void CALLBACK AlarmMessage2PicCallBack(LONG  lCommand, NET_DVR_ALARMER  *pAlarmer, char  *pAlarmInfo, DWORD  dwBufLen, void  *pUser)
{
	CAlarmManger *alarm = (CAlarmManger *)pUser;
	switch (lCommand)
	{
		case COMM_ALARM_RULE:
		{
				////LOG_INFO("COMM_ALARM_RULE");
		}
			break;
		case COMM_ITS_PLATE_RESULT:
		{
				//0x3050报警值上传
				////LOG_INFO("COMM_ITS_PLATE_RESULT");
				//抓拍机终端图片上传
				NET_ITS_PLATE_RESULT* plateInfo = (NET_ITS_PLATE_RESULT*)pAlarmInfo;
				//车牌信息
				std::string plate = plateInfo->struPlateInfo.sLicense;
				////LOG_INFO("plate num : %s", plate.c_str());

				UpLoadInfo Alarm_info = { 0 };
				Alarm_info.strIp = pAlarmer->sDeviceIP;
				Alarm_info.iPort = pAlarmer->wLinkPort;
				Alarm_info.iChannel = plateInfo->byChanIndex;
				Alarm_info.struPlateInfo = plateInfo->struPlateInfo;
				Alarm_info.struVehicleInfo = plateInfo->struVehicleInfo;

				//建立报警时间结构
				HPR_TIME_EXP_S alarmTime = { 0 };
				HPR_ExpTimeFromTimeLocal(HPR_TimeNow(), &alarmTime);
				alarmTime.tm_year += 1900;
				alarmTime.tm_mon += 1;
				char temp[32];
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "%04d-%02d-%02dT%02d:%02d:%02d", alarmTime.tm_year,
					alarmTime.tm_mon,
					alarmTime.tm_mday,
					alarmTime.tm_hour,
					alarmTime.tm_min,
					alarmTime.tm_sec);
				Alarm_info.strHapentTime = temp;
				for (int i = 0; i < (int)plateInfo->dwPicNum; i++)
				{
					if (plateInfo->struPicInfo[i].byType == CAR_TYPE)  //1车辆图
					{
						Alarm_info.pBigPicData = plateInfo->struPicInfo[i].pBuffer == NULL ? "" : (char *)plateInfo->struPicInfo[i].pBuffer;
						Alarm_info.uiBigPicLen = plateInfo->struPicInfo[i].dwDataLen;					
					}
					else if (plateInfo->struPicInfo[i].byType == PLATE_TYPE)  //0车牌图
					{
						Alarm_info.pSmallPicData = plateInfo->struPicInfo[i].pBuffer == NULL ? "" : (char *)plateInfo->struPicInfo[i].pBuffer;
						Alarm_info.uiSmallLen = plateInfo->struPicInfo[i].dwDataLen;
					}
				}

				//上传图片
				alarm->UpLoadPicToPms(Alarm_info);
		}
			break;
		case COMM_UPLOAD_PLATE_RESULT:
		{
				//LOG_INFO("COMM_UPLOAD_PLATE_RESULT");

		}
			break;
		case COMM_ITS_GATE_VEHICLE:
		{
				//LOG_INFO("COMM_ITS_GATE_VEHICLE");

		}
			break;
	default:
		break;
	}
}

int CAlarmManger::LoginDevice(MangerDeviceInfo deviceInfo)
{
	NET_DVR_USER_LOGIN_INFO userinfo = {};
	strncpy(userinfo.sDeviceAddress, deviceInfo.szIp, sizeof(userinfo.sDeviceAddress));
	userinfo.wPort = deviceInfo.iPort;
	strncpy(userinfo.sUserName, deviceInfo.szUserName, sizeof(userinfo.sUserName));
	strncpy(userinfo.sPassword, deviceInfo.szPwd, sizeof(userinfo.sPassword));

	NET_DVR_DEVICEINFO_V30 dstInfo = {};
	int iLoginId = NET_DVR_Login_V40(&userinfo, &dstInfo);
	if (iLoginId < 0)
	{
		int iError = NET_DVR_GetLastError();
		if (iError == 7)
		{
			LOG_ERROR("登录失败[%s][%s:%d] 用户名密码错误", deviceInfo.szName, deviceInfo.szIp, deviceInfo.iPort);
		}
		else
		{
			LOG_ERROR("登录失败[%s][%s:%d] error:%d", deviceInfo.szName, deviceInfo.szIp, deviceInfo.iPort, iError);
		}
	}
	else
	{
		NET_DVR_SetDVRMessageCallBack_V30(AlarmMessage2PicCallBack, this);
		NET_DVR_SETUPALARM_PARAM tmpSetupParam = { 0 };
		tmpSetupParam.byFaceAlarmDetection = 1;//1-表示人脸侦测报警扩展(INTER_FACE_DETECTION) 
		tmpSetupParam.byAlarmInfoType = 1; //上传报警信息类型（抓拍机支持），0-老报警信息（NET_DVR_PLATE_RESULT），1-新报警信息(NET_ITS_PLATE_RESULT)2012-9-28
		tmpSetupParam.dwSize = sizeof(NET_DVR_SETUPALARM_PARAM);
		int  iAlarmHandle = NET_DVR_SetupAlarmChan_V41(iLoginId, &tmpSetupParam);
		if (iAlarmHandle < 0)
		{
			int iError = NET_DVR_GetLastError();
			LOG_ERROR("布防失败[%s][%s:%d] error:%d", deviceInfo.szName, deviceInfo.szIp, deviceInfo.iPort, iError);
			NET_DVR_Logout_V30(iLoginId);
		}
		else
		{
			LoginHandleManger device_login;
			device_login.loginId = iLoginId;
			device_login.alarmHandle = iAlarmHandle;
			device_login.ip = userinfo.sDeviceAddress == NULL ? "" : userinfo.sDeviceAddress;
			device_login.port = userinfo.wPort;
			m_vLoginHandle.push_back(device_login);
			LOG_ERROR("登录布防成功[%s][%s:%d]", deviceInfo.szName, deviceInfo.szIp, deviceInfo.iPort);
			return HPR_OK;
		}
	}

	return HPR_ERROR;
}

int CAlarmManger::LogoutDevice()
{
	int nRet = HPR_OK;
	std::vector<LoginHandleManger>::iterator iter = m_vLoginHandle.begin();
	for (; iter != m_vLoginHandle.end(); iter++)
	{
		nRet = NET_DVR_CloseAlarmChan_V30((*iter).alarmHandle);
		if (nRet != HPR_TRUE)
		{
			nRet = NET_DVR_GetLastError();
			//LOG_ERROR("NET_DVR_CloseAlarmChan_V30 error : %d ，IP : %s ,port : %d", nRet, (*iter).ip.c_str(), (*iter).port);

			continue;
		}
		nRet = NET_DVR_Logout_V30((*iter).loginId);
		if (nRet != HPR_TRUE)
		{
			nRet = NET_DVR_GetLastError();
			//LOG_ERROR("NET_DVR_Logout_V30 error : %d ，IP : %s ,port : %d", nRet, (*iter).ip.c_str(), (*iter).port);
			continue;
		}
		//LOG_INFO("Logout Success!  IP : %s ,port : %d", (*iter).ip.c_str(), (*iter).port);
	}

	return HPR_OK;
}

int CAlarmManger::transformColor(int color)
{
	int nRet = 0;

	return nRet;
}

int CAlarmManger::UpLoadPicToPms(UpLoadInfo upLoadInfo)
{
	int nRet = HPR_OK;
	//上传至PMS
	m_pmsManger->UpLoadPic(upLoadInfo);
	return nRet;
}