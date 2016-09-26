//PowerCommonWebService接口头文件
//created by hikvision power group

#pragma once

#include "cmsws_defines.h"

typedef struct Stru_DvrDevInfo
{
    int  iId;
    char szName[128];
    char szIndex[64];
    char szIp[32];
    int  iPort;
    char szUserName[64];
    char szPwd[32];
    char szUpdateTime[32];
    char szRev1[32];
    int  iRev1;
}Stru_DvrDevInfo;

typedef struct  Stru_getDvrInfoResponse
{ 
    int iResult;    
    int iErrorCode;
    int iInfoNum;
	int currentPage;
	int totalPage;
    Stru_DvrDevInfo *pInfo;
}Stru_getDvrInfoResponse;
 
typedef struct  Stru_getDvrInfo
{ 
	int pageNum;
	int pageSize;
}Stru_getDvrInfo;