
/****************************************************************\
Copyright 2010 Hikvision System Technology Co., Ltd.   

FileName: PowerCommonWebService_Services.h

Description: ����WebService�ӿڵ�ͷ�ļ� 	 

Modification History:      

<version >     <time>           <author>          <desc>
v1.0        2010-06-28          YunlongHe           Create

\****************************************************************/

#pragma once

#include "DeviceInfoService_Defines.h"

#ifdef __cplusplus
extern "C"
{
#endif

    CMSWS_EXTERN Stru_getDvrInfoResponse* CMSWS_API DeviceInfoService_getAllDeviceInfo(const char* endpointUri);

#ifdef __cplusplus
}

#endif