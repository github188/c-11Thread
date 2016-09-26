#pragma once
//
// Copyright (c) 2009 Hikvision Digital Technology Co., Ltd.
//
// Summary:
//     PowerCommonWebService 接口定义
//
// Modification History:
//  created by HYL 20100628
//
#include "cmsws_defines.h"

//
// Summary:
//     通用接口定义。
//
#ifdef __cplusplus
extern "C"
{
#endif

    //
    // Summary:
    //     初始化当前线程私有的 VehicleInfoService Stub 资源。
    //
    // Parameters:
    //   [in] endpointUri:
    //     CommonServerService 的 endpoint uri 。
    //
    // Returns:
    //     true - 初始化成功。
    //     false - 初始化失败。
    //
    // Remarks:
    //     调用 VehicleInfoService_Init 可为当前线程分配线程私有的 runtime environment 资源。
    //     否则，使用全局的 runtime environment 资源。
    //
    CMSWS_EXTERN bool CMSWS_API VehicleInfoService_Init(const char* endpointUri);

    //
    // Summary:
    //     释放由 VehicleInfoService_Init 分配的当前线程私有的 VehicleInfoService Stub 资源。
    //
    CMSWS_EXTERN void CMSWS_API VehicleInfoService_Uninit(void);

    //
    // Summary:
    //     设置 VehicleInfoService 的 endpoint uri。
    //
    // Parameters:
    //   [in] endpointUri:
    //     VehicleInfoService 的 endpoint uri 。
    //
    CMSWS_EXTERN void CMSWS_API VehicleInfoService_ResetEndpointUri(const char* endpointUri);

    //
    // Summary:
    //     获取 VehicleInfoService 最后产生的错误信息。
    //
    // Parameters:
    //   [out] errorCode:
    //     错误代码。
    //   [out] errorReason:
    //     产生错误的原因。
    //   [out] errorDetail:
    //     错误的详细信息。
    //
    // Remarks:
    //     errorReason, errorDetail 资源由链接库管理，请勿释放。
    //
    CMSWS_EXTERN void CMSWS_API VehicleInfoService_GetLastError(int* errorCode, const char** errorReason, const char** errorDetail);

    //
    // Summary:
    //     获取 VehicleInfoService 的 runtime environment。
    //
    // Returns:
    //     cmsws_soap* 指针。
    //
    // Remarks:
    //     允许用户通过 gsoap 库提供的方法操作 VehicleInfoService 的 runtime environment 。
    //     请勿释放 cmsws_soap* 。
    //
    CMSWS_EXTERN cmsws_soap* CMSWS_API VehicleInfoService_GetSoapEnv(void);

    //
    // Summary:
    //     释放因调用 VehicleInfoService 服务而分配的临时资源。
    //
    // Remarks:
    //     建议在每次调用服务接口之后，调用 VehicleInfoService_FreeTemporaryData 立即释放本次调用分配的临时资源。
    //
    CMSWS_EXTERN void CMSWS_API VehicleInfoService_FreeTemporaryData(void);
#ifdef __cplusplus
}
#endif
