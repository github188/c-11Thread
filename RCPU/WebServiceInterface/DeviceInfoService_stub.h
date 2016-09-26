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
    //     ��ʼ����ǰ�߳�˽�е� DeviceInfoService Stub ��Դ��
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
    //     ���� DeviceInfoService_Init ��Ϊ��ǰ�̷߳����߳�˽�е� runtime environment ��Դ��
    //     ����ʹ��ȫ�ֵ� runtime environment ��Դ��
    //
    CMSWS_EXTERN bool CMSWS_API DeviceInfoService_Init(const char* endpointUri);

    //
    // Summary:
    //     �ͷ��� DeviceInfoService_Init ����ĵ�ǰ�߳�˽�е� DeviceInfoService Stub ��Դ��
    //
    CMSWS_EXTERN void CMSWS_API DeviceInfoService_Uninit(void);

    //
    // Summary:
    //     ���� DeviceInfoService �� endpoint uri��
    //
    // Parameters:
    //   [in] endpointUri:
    //     DeviceInfoService �� endpoint uri ��
    //
    CMSWS_EXTERN void CMSWS_API DeviceInfoService_ResetEndpointUri(const char* endpointUri);

    //
    // Summary:
    //     ��ȡ DeviceInfoService �������Ĵ�����Ϣ��
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
    CMSWS_EXTERN void CMSWS_API DeviceInfoService_GetLastError(int* errorCode, const char** errorReason, const char** errorDetail);

    //
    // Summary:
    //     ��ȡ DeviceInfoService �� runtime environment��
    //
    // Returns:
    //     cmsws_soap* ָ�롣
    //
    // Remarks:
    //     �����û�ͨ�� gsoap ���ṩ�ķ������� DeviceInfoService �� runtime environment ��
    //     �����ͷ� cmsws_soap* ��
    //
    CMSWS_EXTERN cmsws_soap* CMSWS_API DeviceInfoService_GetSoapEnv(void);

    //
    // Summary:
    //     �ͷ������ DeviceInfoService ������������ʱ��Դ��
    //
    // Remarks:
    //     ������ÿ�ε��÷���ӿ�֮�󣬵��� DeviceInfoService_FreeTemporaryData �����ͷű��ε��÷������ʱ��Դ��
    //
    CMSWS_EXTERN void CMSWS_API DeviceInfoService_FreeTemporaryData(void);
#ifdef __cplusplus
}
#endif
