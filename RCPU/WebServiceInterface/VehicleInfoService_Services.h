
/****************************************************************\
Copyright 2010 Hikvision System Technology Co., Ltd.   

FileName: PowerCommonWebService_Services.h

Description: 级联WebService接口的头文件 	 

Modification History:      

<version >     <time>           <author>          <desc>
v1.0        2010-06-28          YunlongHe           Create

\****************************************************************/

#pragma once

#include "VehicleInfoService_Defines.h"

#ifdef __cplusplus
extern "C"
{
#endif

    CMSWS_EXTERN Stru_getVehicleInfoResponse* CMSWS_API VehicleInfoService_getVehicleInfo(const char* endpointUri);

    CMSWS_EXTERN int CMSWS_API VehicleInfoService_saveVehicleRecordAndAlarm(Stru_saveVehicleEventReq *pReq, const char* endpointUri);

#ifdef __cplusplus
}

#endif