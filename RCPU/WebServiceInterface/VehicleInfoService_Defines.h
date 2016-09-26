//PowerCommonWebService�ӿ�ͷ�ļ�
//created by hikvision power group

#pragma once

#include "cmsws_defines.h"

typedef struct Stru_CarInfo
{
    int  iPlateAttr;                    //���ƹ���---�ӵ�...
    int  iPlateType;					//��������   //������
    int  iPlateColor;					//������ɫ    
    char sLicense[32];		            //���ƺ���
    int  iCarType;		                //��������    //������
    int  iCarColor;		                //����0��	С��1��	����2  //������
}Stru_CarInfo;

typedef struct  Stru_getVehicleInfoResponse
{ 
    int iResult;    
    int iErrorCode;
    int iInfoNum;
    Stru_CarInfo *pInfo;
}Stru_getVehicleInfoResponse;

typedef struct Stru_saveVehicleEventReq
{ 
    char szCameraName[64]; 
    char szIp[32];
    int  iPort;
    int  iChannel;
    char sLicense[32];		//���ƺ���
    int  iPlateColor;		//������ɫ
    int  iCarColor;		//����ɫ
    int  iCarType;			//������
    char szBigPicUrl[256];
    char szSmallPicUrl[256];
    char szstartEndTime[32];
    int  iPlateAttr;                    //���ƹ���---�ӵ�...
}Stru_saveVehicleEventReq;

