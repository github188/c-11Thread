//PowerCommonWebService接口头文件
//created by hikvision power group

#pragma once

#include "cmsws_defines.h"

typedef struct Stru_CarInfo
{
    int  iPlateAttr;                    //车牌归属---逃单...
    int  iPlateType;					//车牌类型   //不启用
    int  iPlateColor;					//车牌颜色    
    char sLicense[32];		            //车牌号码
    int  iCarType;		                //车辆类型    //不启用
    int  iCarColor;		                //其他0、	小型1、	大型2  //不启用
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
    char sLicense[32];		//车牌号码
    int  iPlateColor;		//车牌颜色
    int  iCarColor;		//车颜色
    int  iCarType;			//车类型
    char szBigPicUrl[256];
    char szSmallPicUrl[256];
    char szstartEndTime[32];
    int  iPlateAttr;                    //车牌归属---逃单...
}Stru_saveVehicleEventReq;

