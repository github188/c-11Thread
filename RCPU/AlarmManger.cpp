#include "AlarmManger.h"
//�ص�����
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
	std::vector<MangerDeviceInfo>  tempDevice = m_deviceManger->GetManualDevice();
	std::vector<MangerDeviceInfo>::iterator  iterDeivice = tempDevice.begin();
	for (; iterDeivice != tempDevice.end(); iterDeivice++)
	{
		int nRet = HPR_OK;
		std::vector<MangerDeviceInfo>::iterator iterLogin = m_vDeviceManger.begin();
		for (; iterLogin != m_vDeviceManger.end(); iterLogin++)
		{
			if (strcpy_s((*iterLogin).szIp, (*iterDeivice).szIp) == 0 && (*iterDeivice).iPort == (*iterLogin).iPort)
			{
				LOG_INFO("device is login!");
				nRet = HPR_ERROR;
				break;
			}
		}
		if (HPR_OK == nRet)
		{
			LOG_INFO("device start login!");
			if (HPR_OK == LoginDevice(*iterDeivice))
			{
				m_vDeviceManger.push_back(*iterDeivice);
			}
			LOG_INFO("device login end!");
		}
	}
	HPR_Sleep(1000);
	return HPR_OK;
}

//�ص�����
void CALLBACK AlarmMessage2PicCallBack(LONG  lCommand, NET_DVR_ALARMER  *pAlarmer, char  *pAlarmInfo, DWORD  dwBufLen, void  *pUser)
{
	switch (lCommand)
	{
		case COMM_ALARM_RULE:
		{
				LOG_INFO("COMM_ALARM_RULE");
		}
			break;
		case COMM_ITS_PLATE_RESULT:
		{
				//0x3050����ֵ�ϴ�
				LOG_INFO("COMM_ITS_PLATE_RESULT");
				//ץ�Ļ��ն�ͼƬ�ϴ�
				NET_ITS_PLATE_RESULT* plateInfo = (NET_ITS_PLATE_RESULT*)pAlarmInfo;
				//������Ϣ
				std::string plate = plateInfo->struPlateInfo.sLicense;
				LOG_INFO("plate num : %s", plate.c_str());

				UpLoadInfo Alarm_info = { 0 };
				for (int i = 0; i < (int)plateInfo->dwPicNum; i++)
				{
					if (plateInfo->struPicInfo[i].byType == CAR_TYPE)  //1����ͼ
					{
						Alarm_info.pBigPicData = plateInfo->struPicInfo[i].pBuffer == NULL ? "" : (char *)plateInfo->struPicInfo[i].pBuffer;
						Alarm_info.uiBigPicLen = plateInfo->struPicInfo[i].dwDataLen;
					}
					else if (plateInfo->struPicInfo[i].byType == PLATE_TYPE)  //0����ͼ
					{
						Alarm_info.pSmallPicData = plateInfo->struPicInfo[i].pBuffer == NULL ? "" : (char *)plateInfo->struPicInfo[i].pBuffer;
						Alarm_info.uiSmallLen = plateInfo->struPicInfo[i].dwDataLen;
					}
				}
				Alarm_info.szIp = pAlarmer->sDeviceIP;
				Alarm_info.iPort = pAlarmer->wLinkPort;
				Alarm_info.iChannel = plateInfo->byChanIndex;
				Alarm_info.struPlateInfo = plateInfo->struPlateInfo;
				Alarm_info.struVehicleInfo = plateInfo->struVehicleInfo;

				//У׼������ɫ����ɫת��
				//GetRightInfo(WorkData);
				//�ϴ�����ͼ��cms������webservice�ӿ�
				//CProEvent::GetInstance()->ProcCarEvent(WorkData);
		}
			break;
		case COMM_UPLOAD_PLATE_RESULT:
		{
				LOG_INFO("COMM_UPLOAD_PLATE_RESULT");

		}
			break;
		case COMM_ITS_GATE_VEHICLE:
		{
				LOG_INFO("COMM_ITS_GATE_VEHICLE");

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
			LOG_ERROR("��¼ʧ��[%s][%s:%d] �û����������", deviceInfo.szName, deviceInfo.szIp, deviceInfo.iPort);
		}
		else
		{
			LOG_ERROR("��¼ʧ��[%s][%s:%d] error:%d", deviceInfo.szName, deviceInfo.szIp, deviceInfo.iPort, iError);
		}
	}
	else
	{
		NET_DVR_SetDVRMessageCallBack_V30(AlarmMessage2PicCallBack, NULL);
		NET_DVR_SETUPALARM_PARAM tmpSetupParam = { 0 };
		tmpSetupParam.byFaceAlarmDetection = 1;//1-��ʾ������ⱨ����չ(INTER_FACE_DETECTION) 
		tmpSetupParam.byAlarmInfoType = 1; //�ϴ�������Ϣ���ͣ�ץ�Ļ�֧�֣���0-�ϱ�����Ϣ��NET_DVR_PLATE_RESULT����1-�±�����Ϣ(NET_ITS_PLATE_RESULT)2012-9-28
		tmpSetupParam.dwSize = sizeof(NET_DVR_SETUPALARM_PARAM);
		int  iAlarmHandle = NET_DVR_SetupAlarmChan_V41(iLoginId, &tmpSetupParam);
		if (iAlarmHandle < 0)
		{
			int iError = NET_DVR_GetLastError();
			LOG_ERROR("����ʧ��[%s][%s:%d] error:%d", deviceInfo.szName, deviceInfo.szIp, deviceInfo.iPort, iError);
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
			LOG_ERROR("��¼�����ɹ�[%s][%s:%d]", deviceInfo.szName, deviceInfo.szIp, deviceInfo.iPort);
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
			LOG_ERROR("NET_DVR_CloseAlarmChan_V30 error : %d ��IP : %s ,port : %d", nRet, (*iter).ip.c_str(), (*iter).port);

			continue;
		}
		nRet = NET_DVR_Logout_V30((*iter).loginId);
		if (nRet != HPR_TRUE)
		{
			nRet = NET_DVR_GetLastError();
			LOG_ERROR("NET_DVR_Logout_V30 error : %d ��IP : %s ,port : %d", nRet, (*iter).ip.c_str(), (*iter).port);
			continue;
		}
		LOG_INFO("Logout Success!  IP : %s ,port : %d", (*iter).ip.c_str(), (*iter).port);
	}

	return HPR_OK;
}

int CAlarmManger::transformColor(int color)
{
	int nRet = 0;

	return nRet;
}