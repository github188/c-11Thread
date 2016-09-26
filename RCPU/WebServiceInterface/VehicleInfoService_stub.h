#pragma once
//
// Copyright (c) 2009 Hikvision Digital Technology Co., Ltd.
//
// Summary:
//     PowerCommonWebService �ӿڶ���
//
// Modification History:
//  created by HYL 20100628
//
#include "cmsws_defines.h"

//
// Summary:
//     ͨ�ýӿڶ��塣
//
#ifdef __cplusplus
extern "C"
{
#endif

    //
    // Summary:
    //     ��ʼ����ǰ�߳�˽�е� VehicleInfoService Stub ��Դ��
    //
    // Parameters:
    //   [in] endpointUri:
    //     CommonServerService �� endpoint uri ��
    //
    // Returns:
    //     true - ��ʼ���ɹ���
    //     false - ��ʼ��ʧ�ܡ�
    //
    // Remarks:
    //     ���� VehicleInfoService_Init ��Ϊ��ǰ�̷߳����߳�˽�е� runtime environment ��Դ��
    //     ����ʹ��ȫ�ֵ� runtime environment ��Դ��
    //
    CMSWS_EXTERN bool CMSWS_API VehicleInfoService_Init(const char* endpointUri);

    //
    // Summary:
    //     �ͷ��� VehicleInfoService_Init ����ĵ�ǰ�߳�˽�е� VehicleInfoService Stub ��Դ��
    //
    CMSWS_EXTERN void CMSWS_API VehicleInfoService_Uninit(void);

    //
    // Summary:
    //     ���� VehicleInfoService �� endpoint uri��
    //
    // Parameters:
    //   [in] endpointUri:
    //     VehicleInfoService �� endpoint uri ��
    //
    CMSWS_EXTERN void CMSWS_API VehicleInfoService_ResetEndpointUri(const char* endpointUri);

    //
    // Summary:
    //     ��ȡ VehicleInfoService �������Ĵ�����Ϣ��
    //
    // Parameters:
    //   [out] errorCode:
    //     ������롣
    //   [out] errorReason:
    //     ���������ԭ��
    //   [out] errorDetail:
    //     �������ϸ��Ϣ��
    //
    // Remarks:
    //     errorReason, errorDetail ��Դ�����ӿ���������ͷš�
    //
    CMSWS_EXTERN void CMSWS_API VehicleInfoService_GetLastError(int* errorCode, const char** errorReason, const char** errorDetail);

    //
    // Summary:
    //     ��ȡ VehicleInfoService �� runtime environment��
    //
    // Returns:
    //     cmsws_soap* ָ�롣
    //
    // Remarks:
    //     �����û�ͨ�� gsoap ���ṩ�ķ������� VehicleInfoService �� runtime environment ��
    //     �����ͷ� cmsws_soap* ��
    //
    CMSWS_EXTERN cmsws_soap* CMSWS_API VehicleInfoService_GetSoapEnv(void);

    //
    // Summary:
    //     �ͷ������ VehicleInfoService ������������ʱ��Դ��
    //
    // Remarks:
    //     ������ÿ�ε��÷���ӿ�֮�󣬵��� VehicleInfoService_FreeTemporaryData �����ͷű��ε��÷������ʱ��Դ��
    //
    CMSWS_EXTERN void CMSWS_API VehicleInfoService_FreeTemporaryData(void);
#ifdef __cplusplus
}
#endif
