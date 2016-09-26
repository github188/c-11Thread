#pragma once
//
// Copyright (c) 2009 Hikvision Digital Technology Co., Ltd.
//
// Summary:
//     CMS WebService ��ض��塣
//
// Modification History:
//   2009-09-29:
//     V1.0 / ��ͨ�� / ����
//

#if (defined(_WIN32) || defined(_WIN32_WCE))

    //
    // Summary:
    //     cmsws_web_service export / import
    //
    #ifdef HIK_CMSWS_DLL_EXPORTS
    #define CMSWS_EXTERN __declspec(dllexport)
    #else
    #define CMSWS_EXTERN __declspec(dllimport)
    #endif

    //
    // Summary:
    //     CMS WebService API ���Ͷ���
    //
    #define CMSWS_API __stdcall

    //
    // Summary:
    //     TLS ������
    //
    #define TLS_DECLARE __declspec(thread)

    //
    // Summary:
    //     base type
    //
    typedef short               cmsws_int16;
    typedef unsigned short      cmsws_uint16;
    typedef int                 cmsws_int32;
    typedef unsigned int        cmsws_uint32;
    typedef __int64             cmsws_int64;
    typedef unsigned __int64    cmsws_uint64;

    typedef cmsws_int32         cmsws_bool;
    #define cmsws_true          1
    #define cmsws_false         0

#elif (defined(__linux__) || defined(__APPLE__))

    //
    // Summary:
    //     cmsws_web_service export / import
    //
    #define CMSWS_EXTERN extern "C" 

    //
    // Summary:
    //     CMS WebService API ���Ͷ���
    //
    #define CMSWS_API 

    //
    // Summary:
    //     TLS ������
    //
    #define TLS_DECLARE __thread

    //
    // Summary:
    //     base type
    //
    typedef short                   cmsws_int16;
    typedef unsigned short          cmsws_uint16;
    typedef int                     cmsws_int32;
    typedef unsigned int            cmsws_uint32;
    #if defined(__LP64__)
        typedef signed long         cmsws_int64;
        typedef unsigned long       cmsws_uint64;
    #else
        typedef signed long long    cmsws_int64;
        typedef unsigned long long  cmsws_uint64;
    #endif	//defined(__LP64__)

    typedef cmsws_int32         cmsws_bool;
    #define cmsws_true          1
    #define cmsws_false         0

#endif


//
// Summary:
//     include stdsoap2.h
//
#include "stdsoap2.h"


//
// Summary:
//     typedef cmsws_soap
//
typedef struct soap cmsws_soap;

//
// Summary:
//     typedef cmsws_namespace
//
typedef struct Namespace cmsws_namespace;


//
// Summary:
//     NULL
//
#ifndef NULL
#define NULL 0
#endif

//
// Summary:
//     __cdecl
//
#if (!defined(_MSC_VER) && !defined(__cdecl))
#define __cdecl
#endif


//
// Summary:
//     cmsws ����ֵ���塣
//
#define CMSWS_SUCCESS   1   // �����ɹ�
#define CMSWS_FAILURE   0   // ����ʧ��


//
// Summary:
//     cmsws service stub �����塣
//
#define CMSWS_SOAP_PARAM_ERROR          0x01000001      // ���������Ч
#define CMSWS_SOAP_MALLOC_ERROR         0x01000002      // �����ڴ����
#define CMSWS_SOAP_RESPONSE_NIL         0x01000003      // �������ظ��� XML Ϊ��
#define CMSWS_SOAP_ERROR_CODE_NIL       0x01000004      // �������ظ��� errorCode Ϊ��

//
// Summary:
//     cmsws service skel �����塣
//
#define CMSWS_SOAP_SKEL_NO_SERVICE_ENTRY    0x02000001  // ��������ڲ�����


//
// Summary:
//     ���� CMS WebService ���ص� errorCode ����
//
#define CMS_SUCCESSED                   0                //�����ɹ�
#define CMS_FAILED                      10000            //����ʧ��

//�û���¼������
#define CMS_USERNAME_ERROR              10001            //�û���������
#define CMS_PWD_ERROR                   10002            //�������
#define CMS_USER_HAS_LOGIN              10003            //�û��Ѿ���¼
#define CMS_USER_NOT_EXCLUSIVE          10004            //�û����Ʋ�Ψһ
#define CMS_USER_EXPIRED                10005            //�û��Ѿ�����
#define CMS_USER_DELETE                 10006            //�û���ɾ��

#define CMS_USERSESSION_NOT_EXIST       10010            //�û��ỰID������

//��Ӵ�����
#define CMS_INDEX_CODE_HAS_EXIST        20001            //���������Ѿ�����
#define CMS_PARENT_ID_ERROR             20002            //��ID����
#define CMS_ID_NOT_EXIST                20003            //IDֵ������
#define CMS_USER_NAME_EXIST             20004            //�û����Ѿ�����
#define CMS_INTERNAL_ERROR              20005            //ϵͳ�ڲ�����

//���ݿ��ѯ������
#define CMS_SELECT_NONE                 30001            //��ѯ��������


//����������
#define OBJECT_TYPE_SERVER              20000 // ���������
#define OBJECT_TYPE_VRM_SVR             20001 // VRM
#define OBJECT_TYPE_PCNVR_SVR           20002 // PC_NVR
#define OBJECT_TYPE_NVTPROXY            20003 // NVT_PROXY
#define OBJECT_TYPE_STREAM_SVR          20004 // ��ý�������
#define OBJECT_TYPE_ALARM_SVR           20005 // ����������
#define OBJECT_TYPE_DECODE_SVR          20006 // ���������
#define OBJECT_TYPE_DECODE_PROXY_SVR    20007 // ����ǽ������������������飩
#define OBJECT_TYPE_PCNVR_SVR_BN        20008 // Ƕ��ʽ�洢
#define OBJECT_TYPE_NM_SVR              20009 // ���ܷ�����
#define OBJECT_TYPE_CASE_SVR            20010 // �������������
#define OBJECT_TYPE_PTZ_SERVER          20011 // ��̨���������
#define OBJECT_TYPE_INTER_AREA          20012 // ����������


//
// Summary:
//     �趨�ṹ����� 4 �ֽڶ��롣
//
// #pragma pack(4)

//
// Summary:
//     CommonResultResponse
//
typedef struct cmsws_CommonAddResult_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     ������¼�ı�š�
    //
    int id;

} CommonAddResultResponse;

//
// Summary:
//     CommonResultResponse
//
typedef struct cmsws_CommonResult_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;

} CommonResultResponse;

//
// Summary:
//     LoginRestriction
//
typedef struct cmsws_LoginRestriction
{
    int restrictId;             // ���Ʊ� ID
    bool timeRestrict;          // �Ƿ����ʱ�����Ƶ�¼��0 ��ʾ�����ƣ�1 ��ʾ����
    cmsws_int64 beginTime;      // ÿ��ĵ�¼��ʼʱ��
    cmsws_int64 endTime;        // ÿ���¼�Ľ���ʱ��
    bool ipRestrict;            // �Ƿ���� IP ��ַ���ƣ�0 ��ʾ�����ƣ�1 ��ʾ����
    const char* ipAddr;         // IP ��ַ����

    int operatorId;             // ������Ա ID������Ǹ��û���Ϊ 0
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} LoginRestriction;

//
// Summary:
//     UserInfo
//
typedef struct cmsws_UserInfo
{
    int userId;                             // �û�id ֵ
    const char* name;                       // �û���
    const char* pwd;                        // �û�����
    int status;                             // 0-������1-���ᣬ2-ע��
    int controlUnitId;                      // �û������Ŀ��Ƶ�Ԫ�� ID
    const char* realName;                   // �û�����ʵ����
    const char* phoneNo;                    // �û��ĵ绰����
    const char* email;                      // �û��� E-MAIL ��ַ
    int loginTimes;                         // �û���¼����
    cmsws_int64 lastLoginTime;              // ����¼ʱ��
    cmsws_int64 expireTime;                 // ʧЧʱ��
    int sequenceIdx;                        // ��������
    const char* description;                // ��ע��Ϣ

    short priority;
    int restrictId;

    int operatorId;                         // ������Ա ID������Ǹ��û���Ϊ 0
    cmsws_int64 createTime;                 // ����ʱ��
    cmsws_int64 updateTime;                 // ���һ�θ���ʱ��

} UserInfo;

//
// Summary:
//     UserInfoArrayResponse
//
typedef struct cmsws_UserInfoArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     �û���Ϣ���顣
    //
    UserInfo** userInfoArray;
    //
    // Summary:
    //     �û���Ϣ���鳤�ȡ�
    //
    int userInfoArrayLength;

} UserInfoArrayResponse;

//
// Summary:
//     UserInfoPageResponse
//
typedef struct cmsws_UserInfoPage_response
{
    bool result;
    int errorCode;

    int pageSize;
    int currentPage;

    int allRow;
    int totalPage;

    UserInfo** userInfoArray;
    int userInfoArrayLength;

} UserInfoPageResponse;


//
// Summary:
//     ControlCenterInfo
//
typedef struct cmsws_ControlCenterInfo
{
    int id;                     // ���Ƶ�Ԫ ID
    const char* indexCode;      // �������
    const char* name;           // ��������
    const char* description;    // ��ע��Ϣ
    int parentId;               // �ϼ���� ID ��0 ��ʾ����
    int unitLevel;              // ���Ƶ�Ԫ�����ļ��𣬸���ԪΪ 0 ��������ʾ�����Ĳ��
    bool useStreamSvr;          // �Ƿ�ʹ����ý��
    int streamSvId;             // ��ý����������
    int sequenceIdx;            // ��������

    int cmsCascadeId;
    int cmsCascadeType;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} ControlCenterInfo, ControlUnit;


//
// Summary:
//     ControlCenterInfo
//
typedef struct cmsws_ControlCenterWithPrivilege
{
    int id;                     // ���Ƶ�Ԫ ID
    const char* indexCode;      // �������
    const char* name;           // ��������
    const char* description;    // ��ע��Ϣ
    int parentId;               // �ϼ���� ID ��0 ��ʾ����
    int unitLevel;              // ���Ƶ�Ԫ�����ļ��𣬸���ԪΪ 0 ��������ʾ�����Ĳ��
    bool useStreamSvr;          // �Ƿ�ʹ����ý��
    int streamSvId;             // ��ý����������
    int sequenceIdx;            // ��������

    int cmsCascadeId;
    int cmsCascadeType;

    int* privilegeCodeArray;
    int privilegeCodeArrayLength;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} ControlCenterWithPrivilege;

//
// Summary:
//     ControlCenterWithPrivilegeResponse
//
typedef struct cmsws_ControlCenterWithPrivilege_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     controlCenter
    //
    ControlCenterWithPrivilege* controlCenter;

} ControlCenterWithPrivilegeResponse;

//
// Summary:
//     ControlCenterWithPrivilegeArrayResponse
//
typedef struct cmsws_ControlCenterWithPrivilegeArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     ControlCenterWithPrivilege Array ��
    //
    ControlCenterWithPrivilege** controlCenterInfoArray;
    //
    // Summary:
    //     Length of ControlCenterWithPrivilege array��
    //
    int controlCenterInfoArrayLength;

} ControlCenterWithPrivilegeArrayResponse;


//
// Summary:
//     RegionInfo
//
typedef struct cmsws_RegionInfo
{
    int regionId;               // ����ID��
    const char* indexCode;      // �������
    const char* name;           // ��������
    int parentId;               // �ϼ���� ID��0 ��ʾ����
    int regionLevel;            // ���������ļ��𣬸���ԪΪ0��������ʾ�����Ĳ��
    int controlUnitId;          // �����Ŀ��Ƶ�Ԫ
    bool useStreamSv;           // �Ƿ�ʹ����ý��
    int streamSvId;             // ��ý����

    int operatorId;             // ������Ա ID������Ǹ��û���Ϊ 0
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} RegionInfo;

//
// Summary:
//     RegionInfoArrayResponse
//
typedef struct cmsws_RegionInfoArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     ������Ϣ���顣
    //
    RegionInfo** regionInfoArray;
    //
    // Summary:
    //     ������Ϣ���鳤�ȡ�
    //
    int regionInfoArrayLength;

} RegionInfoArrayResponse;


//
// Summary:
//     RegionInfoWithPrivilege
//
typedef struct cmsws_RegionInfoWithPrivilege
{
    int regionId;               // ����ID��
    const char* indexCode;      // �������
    const char* name;           // ��������
    int parentId;               // �ϼ���� ID��0 ��ʾ����
    int regionLevel;            // ���������ļ��𣬸���ԪΪ0��������ʾ�����Ĳ��
    int controlUnitId;          // �����Ŀ��Ƶ�Ԫ
    bool useStreamSv;           // �Ƿ�ʹ����ý��
    int streamSvId;             // ��ý����

    int* privilegeCodeArray;
    int privilegeCodeArrayLength;

    int operatorId;             // ������Ա ID������Ǹ��û���Ϊ 0
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

    const char* streamPath;

} RegionInfoWithPrivilege;

//
// Summary:
//     RegionInfoWithPrivilegeArrayResponse
//
typedef struct cmsws_RegionInfoWithPrivilegeArrayResponse_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     RegionInfoWithPrivilege Array ��
    //
    RegionInfoWithPrivilege** regionInfoArray;
    //
    // Summary:
    //     Length of RegionInfoWithPrivilege array��
    //
    int regionInfoArrayLength;

} RegionInfoWithPrivilegeArrayResponse;

//
// Summary:
//     RegionInfoWithPrivilegePageResponse
//
typedef struct cmsws_RegionInfoWithPrivilegePage_response
{
    bool result;
    int errorCode;

    int pageSize;
    int currentPage;

    int allRow;
    int totalPage;

    RegionInfoWithPrivilege** regionInfoArray;
    int regionInfoArrayLength;

} RegionInfoWithPrivilegePageResponse;


//
// Summary:
//     CyclePlan
//
typedef struct cmsws_CyclePlan
{
    int planId;                     // ��ѭ�ƻ���ˮ��
    const char* planName;           // ��ѭ����
    cmsws_int64 startTime;          // ��ʼʱ��
    cmsws_int64 stopTime;           // ����ʱ��
    int cycleTime;                  // ��ѭʱ��
    int groupId;                    // ����������
    int cyclePlanType;

    int* cycleAreaIdArray;          // ��ѭ��������
    int cycleAreaIdArrayLength;     // ��ѭ�������鳤��

    int* cycleCameraIdArray;        // ��ѭ��ص�����
    int cycleCameraIdArrayLength;   // ��ѭ��ص����鳤��

} CyclePlan;

//
// Summary:
//     CyclePlanArrayResponse
//
typedef struct cmsws_CyclePlanArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     ��ѭ�ƻ���Ϣ���顣
    //
    CyclePlan** cyclePlanArray;
    //
    // Summary:
    //     ��ѭ�ƻ���Ϣ���鳤�ȡ�
    //
    int cyclePlanArrayLength;

} CyclePlanArrayResponse;


//
// Summary:
//     AudioOut
//
typedef struct cmsws_AudioOut
{
    int aoId;                   // ���������ˮ��
    int aoIndex;                // �������ͨ������
    const char* aoName;         // �������ͨ������
    short outFlag;              // ����ͨ���Ƿ��
    int decodeResId;            // ������ID��

    int operatorId;             // ������Ա ID������Ǹ��û���Ϊ 0
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AudioOut;

//
// Summary:
//     AudioOutArrayResponse
//
typedef struct cmsws_AudioOutArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     �������ͨ������
    //
    AudioOut** audioOutArray;
    //
    // Summary:
    //     �������ͨ�����鳤��
    //
    int audioOutArrayLength;

} AudioOutArrayResponse;


//
// Summary:
//     VoutArea
//
typedef struct cmsws_VoutArea
{
    int areaIndex;              // �����������
    const char* areaName;       // �����������
    int alarmFlag;              // �Ƿ����ڱ���
    int decIndex;               // ��������ͨ��
    int voId;                   // ���������ˮ��

    int voutAreaId;             // vout_area ����

    int operatorId;             // ������Ա ID������Ǹ��û���Ϊ 0
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} VoutArea;


//
// Summary:
//     VrmServer
//
typedef struct cmsws_VrmServer
{
    const char* ipAddr;         // 
    int ctrlPort;               // ���ƶ˿�

    int vrmId;                  // ������ID��
    const char* indexCode;      // �������
    const char* name;           // ����������
    int controlUnitId;          // ���Ƶ�ԪID

    short maxRecordTask;        // ����ͬʱ¼��������
    short maxTaskPerIpsan;      // ÿ̨IP-SAN���ͬʱִ�е�¼��������
    short maxVodPerIpsan;       // 

    int freeSpace;              // δ����Ĵ洢�ռ�
    int totalSpace;             // �洢�ռ�������

    bool useSoftDog;            // �Ƿ����������
    int sequenceIdx;            // 

    int nvtStorePort;           // 
    int webPort;                // 

	int searchPort;
	short shareFlag;

    int netAgentPort;
    int rtpTcpBasePort;
    int rtpUdpBasePort;
    int rtspPort;
    const char* secondIp;
    int udpPortCount;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} VrmServer;

//
// Summary:
//     VrmServerArrayResponse
//
typedef struct cmsws_VrmServerArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     vrm ���顣
    //
    VrmServer** vrmServerArray;
    //
    // Summary:
    //     vrm ���鳤�ȡ�
    //
    int vrmServerArrayLength;

} VrmServerArrayResponse;

//
// Summary:
//     StreamServer
//
typedef struct cmsws_StreamServer
{
    int streamSvId;             // ������ID��
    int controlUnitId;          // ���Ƶ�ԪID
    const char* indexCode;      // �������
    const char* name;           // ����������
    const char* ipAddr;         // 
    int ctrlPort;               // ���ƶ˿�
    int rtspPort;               // RTSP�����˿�
    
    short shareFlag;            // �Ƿ������¼���������ʹ�ã�1��ʾ����ʹ�ã�0��ʾ������ʹ��
    const char* relativePath;   // �ļ��㲥���·��
    int sequenceIdx;            // 

    int netAgentPort;
    int rtpTcpBasePort;
    int rtpUdpBasePort;
    const char* secondIp;
    int udpPortCount;
    
    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} StreamServer;

//
// Summary:
//     StreamServerArrayResponse
//
typedef struct cmsws_StreamServerArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     StreamServer ���顣
    //
    StreamServer** streamServerArray;
    //
    // Summary:
    //     StreamServer ���鳤�ȡ�
    //
    int streamServerArrayLength;

} StreamServerArrayResponse;

//
// Summary:
//     AlarmServer
//
typedef struct cmsws_AlarmServer
{
    int alarmSvId;              // ������ID��
    int controlUnitId;          // ���Ƶ�ԪID
    const char* indexCode;      // �������
    const char* name;           // ����������
    const char* ipAddr;         // 
    int ctrlPort;               // ���ƶ˿�
    bool useSoftDog;            // �Ƿ����������
    short workMode;             // ����ģʽ��0-������1-������
    int sequenceIdx;            // 

    int netAgentPort;
    const char* secondIp;
    const char* smsCom;
    int maListenPort;
    int notifyWay;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmServer;

//
// Summary:
//     AlarmServerArrayResponse
//
typedef struct cmsws_AlarmServerArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     AlarmServer ���顣
    //
    AlarmServer** alarmServerArray;
    //
    // Summary:
    //     AlarmServer ���鳤�ȡ�
    //
    int alarmServerArrayLength;

} AlarmServerArrayResponse;

//
// Summary:
//     PcnvrServer
//
typedef struct cmsws_PcnvrServer
{
    int pcnvrId;
    const char* indexCode;
    const char* name;
    int vrmId;

    const char* ipAddr;
    int ctrlPort;
    int webPort;
    short maxRecordTask;
    bool useSoftDog;

    int netAgentPort;
    int rtpTcpBasePort;
    int rtpUdpBasePort;
    int rtspPort;
    const char* secondIp;
    int udpPortCount;

    int controlUnitId;
	int intRev1;
	int intRev2;
	const char* strRev1;
	const char* strRev2;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} PcnvrServer;

//
// Summary:
//     PcnvrServerArrayResponse
//
typedef struct cmsws_PcnvrServerArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     PcnvrServer ���顣
    //
    PcnvrServer** pcnvrServerArray;
    //
    // Summary:
    //     PcnvrServer ���鳤�ȡ�
    //
    int pcnvrServerArrayLength;

} PcnvrServerArrayResponse;

//
// Summary:
//     PtzServer
//
typedef struct cmsws_PtzServer
{
    int controlUnitId;
    int ctrlPort;
    const char* indexCode;
    const char* ipAddr;
    const char* name;
    int netAgentPort;
    int netZoneId;
    int port;
    int ptzServerId;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��
    
} PtzServer;

//
// Summary:
//     PtzServerArrayResponse
//
typedef struct cmsws_PtzServerArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     PtzServer ���顣
    //
    PtzServer** ptzServerArray;
    //
    // Summary:
    //     PtzServer ���鳤�ȡ�
    //
    int ptzServerArrayLength;

} PtzServerArrayResponse;

//
// Summary:
//     InterAreaServer
//
typedef struct cmsws_InterAreaServer
{
    const char* indexCode;
    const char* ipAddr;
    const char* name;

    int controlUnitId;
    int ctrlPort;
    int interAreaId;
    int netAgentPort;
    int netZoneId;
    int port;
    int uaPort;

    int clientPort;
    int streamPort;
    int ptzPort;

    int type;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} InterAreaServer;

typedef struct cmsws_PAGServer
{
    char *alarmIpAddr;
    char *indexCode;
    char *ipAddr;
    char *name;

    int alarmServerId;
    int controlUnitId;
    int ctrlPort;
    int netAgentPort;
    int netZoneId;	
    int operatorId;
    int pagServerId;
    int port;

    cmsws_int64 createTime;
    cmsws_int64 updateTime;
}PAGServer;

typedef struct cmsws_VrbServer
{
	const char* indexCode;
	const char* ipAddr;
	const char* name;

	int controlUnitId;
	int ftpPort;
	int httpPort;
	int intRev1;
	int intRev2;

	int netAgentPort;
	int netZoneId;

	int rtpTcpBasePort;
	int rtpUdpBasePort;
	int rtspPort;
	short shareFlag;
	int snmpPort;
	const char* strRev1;
	const char* strRev2;
	int udpPortCount;
	int vrbServerId;
	int webServicePort;

	int operatorId;             // ����ԱID
	cmsws_int64 createTime;     // ����ʱ��
	cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} VrbServer;



//
// Summary:
//     AllVrbInfoArrayResponse
//
typedef struct cmsws_VrbServerArray_response
{
	//
	// Summary:
	//     true - �����ɹ���
	//     false - ����ʧ�ܡ�
	//
	bool result;
	//
	// Summary:
	//     ����ʧ��ʱ���ش�����š�
	//     �����ɹ����� 0 ��
	//
	int errorCode;
	//
	// Summary:
	//     PtzServer ���顣
	//
	VrbServer** vrbServerArray;
	//
	// Summary:
	//     PtzServer ���鳤�ȡ�
	//
	int vrbServerArrayLength;

} AllVrbInfoArrayResponse;
//
// Summary:
//     InterAreaServerArrayResponse
//
typedef struct cmsws_InterAreaServerArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     InterAreaServer ���顣
    //
    InterAreaServer** interAreaServerArray;
    //
    // Summary:
    //     InterAreaServer ���鳤�ȡ�
    //
    int interAreaServerArrayLength;

} InterAreaServerArrayResponse;

//
// Summary:
//     PAGServerArrayResponse
//
typedef struct cmsws_PAGServerArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     InterAreaServer ���顣
    //
    PAGServer** PAGServerArray;
    //
    // Summary:
    //     InterAreaServer ���鳤�ȡ�
    //
    int PAGServerArrayLength;

}PAGServerArrayResponse;

//
// Summary:
//     AllServerArrayResponse
//
typedef struct cmsws_AllServerArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     AlarmServer ���顣
    //
    AlarmServer** alarmServerArray;
    //
    // Summary:
    //     AlarmServer ���鳤�ȡ�
    //
    int alarmServerArrayLength;
	//
	// Summary:
	//     PcnvrServer ���顣
	//
	PcnvrServer** pcnvrServerArray;
	//
	// Summary:
	//     PcnvrServer ���鳤�ȡ�
	//
	int pcnvrServerArrayLength;
    //
    // Summary:
    //     StreamServer ���顣
    //
    StreamServer** streamServerArray;
    //
    // Summary:
    //     StreamServer ���鳤�ȡ�
    //
    int streamServerArrayLength;
    //
    // Summary:
    //     VrmServer ���顣
    //
    VrmServer** vrmServerArray;
    //
    // Summary:
    //     VrmServer ���鳤�ȡ�
    //
    int vrmServerArrayLength;
    //
    // Summary:
    //     PtzServer ���顣
    //
    PtzServer** ptzServerArray;
    //
    // Summary:
    //     PtzServer ���鳤�ȡ�
    //
    int ptzServerArrayLength;
    //
    // Summary:
    //     InterAreaServer ���顣
    //
    InterAreaServer** interAreaServerArray;
    //
    // Summary:
    //     InterAreaServer ���鳤�ȡ�
    //
    int interAreaServerArrayLength;
    //
    // Summary:
    //     PAGServerArray ���顣
    //
    PAGServer** PAGServerArray;
    //
    // Summary:
    //     PAGServerArrayLength ���鳤�ȡ�
    //
    int PAGServerArrayLength;

} AllServerArrayResponse;


//
// Summary:
//     ScheduleTemplate
//
typedef struct cmsws_ScheduleTemplate
{
    int schedTemplId;
    const char* name;
    const char* description;
    int type;

    const char* mondaySched;
    const char* tuesdaySched;
    const char* wednesdaySched;
    const char* thursdaySched;
    const char* fridaySched;
    const char* saturdaySched;
    const char* sundaySched;

    int preRecordTime;
    int delayRecordTime;
   
    int sequenceIdx;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} ScheduleTemplate;

//
// Summary:
//     AlarmEventInput
//
typedef struct cmsws_AlarmEventInput
{
    int alarmEventInputId;
    int alarmEventId;

    int alarmInputSource;
    int alarmInputType;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmEventInput;

//
// Summary:
//     AlarmTriggerClient
//
typedef struct cmsws_AlarmTriggerClient
{
    int triggerClientId;
    int alarmEventId;

    bool soundFlag;
    const char* soundText;
    
    int talkChan;
    int talkDeviceId;
    bool talkFlag;

    bool wordsOverlayFlag;
    const char* wordsOverlayTxt;

    bool validFlag;
    bool promt;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmTriggerClient;

//
// Summary:
//     AlarmTriggerEmail
//
typedef struct cmsws_AlarmTriggerEmail
{
    int triggerEmailId;
    int alarmEventId;

    int userId;
    const char* emailTitle;
    const char* emailContent;

    bool validFlag;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmTriggerEmail;

//
// Summary:
//     AlarmTriggerIo
//
typedef struct cmsws_AlarmTriggerIo
{
    int triggerIoId;
    int alarmEventId;

    int ioId;
    bool ioState;

    bool validFlag;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmTriggerIo;

//
// Summary:
//     AlarmTriggerMessage
//
typedef struct cmsws_AlarmTriggerMessage
{
    int triggerMessageId;
    int alarmEventId;

    int userId;
    const char* msgContent;
    
    bool validFlag;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmTriggerMessage;

//
// Summary:
//     AlarmTriggerPopupVideo
//
typedef struct cmsws_AlarmTriggerPopupVideo
{
    int popupVideoId;
    int alarmEventId;

    int cameraId;

    bool promt;
    bool validFlag;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmTriggerPopupVideo;

//
// Summary:
//     AlarmTriggerPreset
//
typedef struct cmsws_AlarmTriggerPreset
{
    int triggerPresetId;
    int alarmEventId;

    int cameraId;
    int presetIndexNormal;
    int presetIndexTrigger;
    
    bool validFlag;
    int type;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmTriggerPreset;

//
// Summary:
//     AlarmTriggerSnapshot
//
typedef struct cmsws_AlarmTriggerSnapshot
{
    int triggerSnapshotId;
    int alarmEventId;

    int cameraId;
    
    bool validFlag;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmTriggerSnapshot;

//
// Summary:
//     AlarmTriggerTvwall
//
typedef struct cmsws_AlarmTriggerTvwall
{
    int triggerTvwallId;
    int alarmEventId;

    int areaId;
    int cameraId;
    
    bool validFlag;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmTriggerTvwall;

//
// Summary:
//     AlarmTriggerVrm
//
typedef struct cmsws_AlarmTriggerVrm
{
    int triggerVrmId;
    int alarmEventId;

    int cameraId;
    int vrmId;
    
    bool validFlag;

    const char* recIndexCode;
    int recordStyle;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmTriggerVrm;


//
// Summary:
//     AlarmTriggerPicture
//
typedef struct cmsws_AlarmTriggerPicture
{
	int alarmEventId;
	bool clientFlag;
	const char* createTime;
	int intRev1;
	int intRev2;
	int intervalTime;
	int operatorId;
	const char* strRev1;
	const char* strRev2;
	int triggerPicId;
	const char* updateTime;
	bool validFlag;

}AlarmTriggerPicture;

//
// Summary:
//     SimpleAlarmTriggerEmail
//
typedef struct cmsws_SimpleAlarmTriggerEmail
{
    const char* emailContent;
    const char* emailTitle;

    int alarmEventId;
    int triggerEmailId;
    int userId;

} SimpleAlarmTriggerEmail;

//
// Summary:
//     SimpleAlarmEventInput
//
typedef struct cmsws_SimpleAlarmEventInput
{
    int alarmEventId;
    int alarmEventInputId;
    int alarmInputSource;
    int alarmInputType;

} SimpleAlarmEventInput;

//
// Summary:
//     SimpleAlarmTriggerPopupVideo
//
typedef struct cmsws_cs_SimpleAlarmTriggerPopupVideo
{
    int alarmEventId;
    int cameraId;
    int popupVideoId;

    bool promt;

} SimpleAlarmTriggerPopupVideo;

//
// Summary:
//     SimpleAlarmTriggerClient
//
typedef struct cmsws_cs_SimpleAlarmTriggerClient
{
    const char* soundText;
    const char* wordsOverlayTxt;

    int alarmEventId;
    int talkChan;
    int talkDeviceId;
    int triggerClientId;

    bool promt;
    bool soundFlag;
    bool talkFlag;
    bool wordsOverlayFlag;

} SimpleAlarmTriggerClient;

//
// Summary:
//     SimpleAlarmTriggerIo
//
typedef struct cmsws_SimpleAlarmTriggerIo
{
    int alarmEventId;
    int ioId;
    int ioType;
    int triggerIoId;

    bool ioState;

} SimpleAlarmTriggerIo;

//
// Summary:
//     SimpleAlarmTriggerMessage
//
typedef struct cmsws_SimpleAlarmTriggerMessage
{
    const char* msgContent;

    int alarmEventId;
    int triggerMessageId;
    int userId;

} SimpleAlarmTriggerMessage;

//
// Summary:
//     SimpleAlarmTriggerPreset
//
typedef struct cmsws_SimpleAlarmTriggerPreset
{
    int alarmEventId;
    int cameraId;
    int presetIndexNormal;
    int presetIndexTrigger;
    int triggerPresetId;
    int type;

} SimpleAlarmTriggerPreset;

//
// Summary:
//     SimpleAlarmTriggerSnapshot
//
typedef struct cmsws_SimpleAlarmTriggerSnapshot
{
    int alarmEventId;
    int cameraId;
    int triggerSnapshotId;

} SimpleAlarmTriggerSnapshot;

//
// Summary:
//     SimpleAlarmTriggerTvwall
//
typedef struct cmsws_SimpleAlarmTriggerTvwall
{
    int alarmEventId;
    int areaId;
    int cameraId;
    int triggerTvwallId;

} SimpleAlarmTriggerTvwall;

//
// Summary:
//     SimpleAlarmTriggerVrm
//
typedef struct cmsws_SimpleAlarmTriggerVrm
{
    const char* recIndexCode;

    int alarmEventId;
    int cameraId;
    int recordStyle;
    int triggerVrmId;
    int vrmId;

} SimpleAlarmTriggerVrm;


//
// Summary:
//     SimpleAlarmTriggerPicture
//
typedef struct cmsws_SimpleAlarmTriggerPicture
{
	int alarmEventId;
	bool clientFlag;
	int intervalTime;
	int operatorId;
	int triggerPicId;
	bool validFlag;

} SimpleAlarmTriggerPicture;

//
// Summary:
//     PresetInfo
//
typedef struct cmsws_PresetInfo
{
    int presetId;
    const char* name;

    int indexNo;
    int cameraId;
    int type;
    bool isUsed;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} PresetInfo;

//
// Summary:
//     PresetInfoArrayResponse
//
typedef struct cmsws_PresetInfoArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     PresetInfo Array
    //
    PresetInfo** presetInfoArray;
    //
    // Summary:
    //     Length of PresetInfo array
    //
    int presetInfoArrayLength;

} PresetInfoArrayResponse;


//
// Summary:
//     MonitorScreenGroupWithPrivilege
//
typedef struct cmsws_MonitorScreenGroupWithPrivilege
{
    int groupId;                // ����������ˮ�ţ����������ID��
    const char* groupName;      // �������������
    const char* proxyIp;        // ���������IP
    int proxyPort;              // ����������˿�

    int controlUnitId;

    int alarmTime;
    int configPort;
    int netAgentPort;
    const char* secondIp;

    int* privilegeCodeArray;
    int privilegeCodeArrayLength;

    int operatorId;             // ������Ա ID������Ǹ��û���Ϊ 0
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

    const char* indexCode;

} MonitorScreenGroupWithPrivilege, MonitorScreenGroup;

//
// Summary:
//     MonitorScreenGroupWithPrivilegeArrayResponse
//
typedef struct cmsws_MonitorScreenGroupWithPrivilegeArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     ����������Ϣ���顣
    //
    MonitorScreenGroupWithPrivilege** monitorScreenGroupArray;
    //
    // Summary:
    //     ����������Ϣ���鳤�ȡ�
    //
    int monitorScreenGroupArrayLength;

} MonitorScreenGroupWithPrivilegeArrayResponse;

//
// Summary:
//     MonitorScreenGroupWithPrivilegePageResponse
//
typedef struct cmsws_MonitorScreenGroupWithPrivilegePage_response
{
    bool result;
    int errorCode;

    int pageSize;
    int currentPage;

    int allRow;
    int totalPage;

    MonitorScreenGroupWithPrivilege** monitorScreenGroupArray;
    int monitorScreenGroupArrayLength;

} MonitorScreenGroupWithPrivilegePageResponse;


//
// Summary:
//     UserStatus
//
typedef struct cmsws_UserStatus
{
    int userStatusId;
    int userId;

    const char* sessionId;
    cmsws_int64 heartBeatTime;
    
    int loginType;
    const char* loginAddr;
    int longinPort;
    
    int status;
    
} UserStatus;

//
// Summary:
//     UserStatusArrayResponse
//
typedef struct cmsws_UserStatusArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     UserStatus Array
    //
    UserStatus** userStatusArray;
    //
    // Summary:
    //     Length of UserStatus array
    //
    int userStatusArrayLength;

} UserStatusArrayResponse;

//
// Summary:
//     UserStatusPageResponse
//
typedef struct cmsws_UserStatusPage_response
{
    bool result;
    int errorCode;

    int pageSize;
    int currentPage;

    int allRow;
    int totalPage;

    UserStatus** userStatusArray;
    int userStatusArrayLength;

} UserStatusPageResponse;

//
// Summary:
//     DeviceInfo
//
typedef struct cmsws_DeviceInfo
{
    int typeCode;               // ���ͱ��
    const char* name;           // �豸����
    int registerType;           // ע������,0-��ͨ/1-˽������/2-��ͨ����
    const char* networkAddr;    // �豸��IP��ַ
    int networkPort;            // ����˿�
    const char* userName;       // �豸��¼���û���
    const char* userPwd;        // �û�����

    int deviceId;
    const char* indexCode;      // �������
    int controlUnitId;          // �����Ŀ��Ƶ�Ԫ
    const char* dnsAddr;        // dns��IP��ַ
    int dnsPort;                // dns�Ķ˿ں�
    const char* serialNo;       // �豸���к�,������ʹ��IP-Serverʱ��ѯ
    int sequenceIdx;

    int alarmInCount;
    int alarmOutCount;
    int cameraChanCount;
    int talkChanCount;

    int matrixId;
    int status;

    int pagServerId;
    const char* pagServerIp;
    int pagServerPort;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} DeviceInfo;

//
// Summary:
//     DeviceInfoPageResponse
//
typedef struct cmsws_DeviceInfoPage_response
{
    bool result;
    int errorCode;

    int pageSize;
    int currentPage;

    int allRow;
    int totalPage;

    DeviceInfo** deviceInfoArray;
    int deviceInfoArrayLength;

} DeviceInfoPageResponse;


//
// Summary:
//     DeviceInfoArrayResponse
//
typedef struct cmsws_DeviceInfoArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     �豸��Ϣ���顣
    //
    DeviceInfo** deviceInfoArray;
    //
    // Summary:
    //     �豸��Ϣ���鳤�ȡ�
    //
    int deviceInfoArrayLength;

} DeviceInfoArrayResponse;


//
// Summary:
//     IoInfo
//
typedef struct cmsws_IoInfo
{
    int ioId;
    const char* indexCode;
    const char* name;

    int deviceId;
    int channel;
    int regionId;
    int type;

} IoInfo;

//
// Summary:
//     IoInfoPageResponse
//
typedef struct cmsws_IoInfoPage_response
{
    bool result;
    int errorCode;

    int pageSize;
    int currentPage;

    int allRow;
    int totalPage;

    IoInfo** ioInfoArray;
    int ioInfoArrayLength;

} IoInfoPageResponse;


//
// Summary:
//     IoInfoArrayResponse
//
typedef struct cmsws_IoInfoArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     IoInfo Array
    //
    IoInfo** ioInfoArray;
    //
    // Summary:
    //     Length of IoInfo array
    //
    int ioInfoArrayLength;

} IoInfoArrayResponse;

//
// Summary:
//     SysInfo
//
typedef struct cmsws_SysInfo
{
    int sysInfoId;

    const char* parameterName;
    const char* strValue;

    int valueType;
    int intValue;
    
    cmsws_int64 createTime;

} SysInfo;

//
// Summary:
//     SysInfoArrayResponse
//
typedef struct cmsws_SysInfoArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     SysInfo Array
    //
    SysInfo** sysInfoArray;
    //
    // Summary:
    //     Length of SysInfo array
    //
    int sysInfoArrayLength;

} SysInfoArrayResponse;


//
// Summary:
//     AlarmChannelInfo
//
typedef struct cmsws_AlarmChannelInfo
{
    int alarmChanId;
    int alarmDevId;
    int channel;
    int regionId;
    int type;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmChannelInfo;

//
// Summary:
//     AlarmChannelInfoArrayResponse
//
typedef struct cmsws_AlarmChannelInfoArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     AlarmChannelInfo Array
    //
    AlarmChannelInfo** alarmChannelInfoArray;
    //
    // Summary:
    //     Length of AlarmChannelInfo array
    //
    int alarmChannelInfoArrayLength;

} AlarmChannelInfoArrayResponse;


//
// Summary:
//     AlarmDevice
//
typedef struct cmsws_AlarmDevice
{
    int alarmDevId;
    int controlUnitId;
    const char* indexCode;
    const char* name;

    int typeCode;
    int connectType;
    const char* ipAddr;
    int port;
    const char* devUsername;
    const char* devPsw;
    
    int inputNum;
    int outputNum;
    int sequenceIdx;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} AlarmDevice;

//
// Summary:
//     AlarmDeviceArrayResponse
//
typedef struct cmsws_AlarmDeviceArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     AlarmDevice Array
    //
    AlarmDevice** alarmDeviceArray;
    //
    // Summary:
    //     Length of AlarmDevice array
    //
    int alarmDeviceArrayLength;

} AlarmDeviceArrayResponse;


//
// Summary:
//     CameraInfoWithPrivilege
//
typedef struct cmsws_CameraInfoWithPrivilege
{
    int cameraId;                   // ͨ��ID
    int cameraType;                 // ��ص����ͣ�0-ǹ��/1-����/2-����/3-��̨
    int chanNum;                    // ͨ���ţ���1��ʼ
    int connectType;                // ��ص�����Э��,0-TCP/1-UDP/2-MCAST/3-RTP
    int deviceId;                   // �豸ID
    const char* indexCode;          // �������
    const char* name;               // ��ص�����
    int *privilegeCodeArray;        // Ȩ�޴�������
    int privilegeCodeArrayLength;   // Ȩ�޴������鳤��

    int* recLacationArray;
    int recLacationArrayLength;

    int regionId;                   // ����ID
    int sequenceIndex;              // �Ŷ����
    short shareFlag;                // 0��ʾ������������1��ʾ���������Ƶ�Ԫ����
    int streamType;                 // 0-������ 1-������

    int vrmId;
    const char* matrixCode;
    int pixel;
    int ptzType;
    bool sound;
	const char* keyboardCode;

    const char* multicastAddr;

} CameraInfoWithPrivilege;

//
// Summary:
//     CameraInfoWithPrivilegePage
//
typedef struct cmsws_CameraInfoWithPrivilegePage
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     cameraInfoWithPrivilege Array
    //
    CameraInfoWithPrivilege** cameraInfoWithPrivilegeArray;
    //
    // Summary:
    //     cameraInfoWithPrivilegeArray Length
    //
    int cameraInfoWithPrivilegeArrayLength;
    //
    // Summary:
    //     current page items
    //
    int pageSize;
    //
    // Summary:
    //     current page index
    //
    int currentPage;
    //
    // Summary:
    //     total items
    //
    int allRow;
    //
    // Summary:
    //     total pages
    //
    int totalPage;

} CameraInfoWithPrivilegePage;

//
// Summary:
//     DeviceInfoWithPrivilege
//
typedef struct cmsws_DeviceInfoWithPrivilege
{
    int deviceId;
    const char* indexCode;          // �������
    const char* name;               // �豸����
    int controlUnitId;              // �����Ŀ��Ƶ�Ԫ

    int* privilegeCodeArray;             // Ȩ�޴�������
    int privilegeCodeArrayLength;        // Ȩ�޴������鳤��

    int typeCode;                   // ���ͱ��
    const char* serialNo;           // �豸���к�,������ʹ��IP-Serverʱ��ѯ

    int registerType;               // ע������,0-��ͨ/1-˽������/2-��ͨ����
    const char* networkAddr;        // �豸��IP��ַ
    int networkPort;                // ����˿�
    const char* dnsAddr;            // dns��IP��ַ
    int dnsPort;                    // dns�Ķ˿ں�

    const char* userName;           // �豸��¼���û���
    const char* userPwd;            // �û�����

    int talkChanCount;
    int matrixId;
    int curState;

} DeviceInfoWithPrivilege;

//
// Summary:
//     DeviceInfoWithPrivilegePage
//
typedef struct cmsws_DeviceInfoWithPrivilegePage
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     deviceInfoWithPrivilege Array
    //
    DeviceInfoWithPrivilege** deviceInfoWithPrivilegeArray;
    //
    // Summary:
    //     deviceInfoWithPrivilegeArray Length
    //
    int deviceInfoWithPrivilegeArrayLength;
    //
    // Summary:
    //     current page items
    //
    int pageSize;
    //
    // Summary:
    //     current page index
    //
    int currentPage;
    //
    // Summary:
    //     total items
    //
    int allRow;
    //
    // Summary:
    //     total pages
    //
    int totalPage;

} DeviceInfoWithPrivilegePage;


//
// Summary:
//     CameraInfo
//
typedef struct cmsws_CameraInfo
{
    int cameraId;
    const char* indexCode;
    const char* name;

    const char* privilegeCode;
    const char* recLacation;

    int cameraType;
    int connectType;
    int streamType;

    int regionId;
    int deviceId;
    int chanNum;
    
    int mainBitRate;
    int mainRateType;
    int subBitRate;
    int subRateType;
    
    short shareFlag;
    int sequenceIdx;

    const char* matrixCode;
    int pixel;
    int ptzType;
    bool sound;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} CameraInfo;

//
// Summary:
//     CameraInfoArrayResponse
//
typedef struct cmsws_CameraInfoArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     CameraInfo Array
    //
    CameraInfo** cameraInfoArray;
    //
    // Summary:
    //     Length of CameraInfo array
    //
    int cameraInfoArrayLength;

} CameraInfoArrayResponse;

//
// Summary:
//     CameraInfoPageResponse
//
typedef struct cmsws_CameraInfoPage_response
{
	bool result;
	int errorCode;

	int pageSize;
	int currentPage;

	int allRow;
	int totalPage;

	CameraInfo** cameraInfoArray;
	int cameraInfoArrayLength;

} CameraInfoPageResponse;


//
// Summary:
//     ReqPageConfig
//
typedef struct cmsws_ReqPageConfig
{
    int length;
    int offset;

    int sortDir;
    const char* sortField;

} ReqPageConfig;


//
// Summary:
//     AlarmLog
//
typedef struct cmsws_AlarmLog
{
    const char* alarmLogId;
    int controlUnitId;

    int alarmEventId;
    const char* alarmEventName;
    
    int alarmInputSource;
    int alarmInputType;

    cmsws_int64 alarmStartTime;
    cmsws_int64 alarmStopTime;
    
    const char* logRemark;
    const char* logTxt;

    bool triggerRecord;

} AlarmLog;

//
// Summary:
//     AlarmLogPageResponse
//
typedef struct cmsws_AlarmLogPage_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     AlarmLog Array
    //
    AlarmLog** alarmLogArray;
    //
    // Summary:
    //     Length of AlarmLog array
    //
    int alarmLogArrayLength;
    //
    // Summary:
    //     current page items
    //
    int pageSize;
    //
    // Summary:
    //     current page index
    //
    int currentPage;
    //
    // Summary:
    //     total items
    //
    int allRow;
    //
    // Summary:
    //     total pages
    //
    int totalPage;

} AlarmLogPageResponse;

//
// Summary:
//     AlarmLogReq
//
typedef struct cmsws_AlarmLogReq
{
    const char* alarmLogId;
    int controlUnitId;
    
    int alarmEventId;
    const char* alarmEventName;

    int alarmInputSource;
    int alarmInputType;

    cmsws_int64 beginTime;
    cmsws_int64 endTime;

    const char* logRemark;
    const char* logTxt;

    bool triggerRecord;

} AlarmLogReq;


//
// Summary:
//     DeviceLog
//
typedef struct cmsws_DeviceLog
{
    int monitorLogId;
    int controlUnitId;
    const char* logTxt;

    int mainType;
    int minorType;

    int objectId;
    int objectType;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��

} DeviceLog;

//
// Summary:
//     DeviceLogPageResponse
//
typedef struct cmsws_DeviceLogPage_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     DeviceLog Array
    //
    DeviceLog** deviceLogArray;
    //
    // Summary:
    //     Length of DeviceLog array
    //
    int deviceLogArrayLength;
    //
    // Summary:
    //     current page items
    //
    int pageSize;
    //
    // Summary:
    //     current page index
    //
    int currentPage;
    //
    // Summary:
    //     total items
    //
    int allRow;
    //
    // Summary:
    //     total pages
    //
    int totalPage;

} DeviceLogPageResponse;

//
// Summary:
//     DeviceLogReq
//
typedef struct cmsws_DeviceLogReq
{
    int monitorLogId;
    int controlUnitId;
    int operatorId;

    cmsws_int64 beginTime;
    cmsws_int64 endTime;

    const char* logTxt;

    int mainType;
    int minorType;
    
    int objectId;
    int objectType;

} DeviceLogReq;


//
// Summary:
//     MonitorLog
//
typedef struct cmsws_MonitorLog
{
    int monitorLogId;
    int controlUnitId;

    const char* logTitle;
    const char* logTxt;

    int mainType;
    int minorType;

    int objectId;
    int objectType;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��

} MonitorLog;

//
// Summary:
//     MonitorLogPageResponse
//
typedef struct cmsws_MonitorLogPage_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     MonitorLog Array
    //
    MonitorLog** monitorLogArray;
    //
    // Summary:
    //     Length of MonitorLog array
    //
    int monitorLogArrayLength;
    //
    // Summary:
    //     current page items
    //
    int pageSize;
    //
    // Summary:
    //     current page index
    //
    int currentPage;
    //
    // Summary:
    //     total items
    //
    int allRow;
    //
    // Summary:
    //     total pages
    //
    int totalPage;

} MonitorLogPageResponse;

//
// Summary:
//     MonitorLogReq
//
typedef struct cmsws_MonitorLogReq
{
    int monitorLogId;
    int controlUnitId;

    cmsws_int64 beginTime;
    cmsws_int64 endTime;

    const char* logTitle;
    const char* logTxt;

    int mainType;
    int minorType;

    int objectId;
    int objectType;

    int operatorId;

} MonitorLogReq;


//
// Summary:
//     OperationLog
//
typedef struct cmsws_OperationLog
{
    int opterationLogId;
    int ctrlUnitId;
    const char* logTxt;
    
    int mainType;
    int minorType;
    
    int resourceId;
    int userId;
    cmsws_int64 triggerTime;

} OperationLog;

//
// Summary:
//     OperationLogPageResponse
//
typedef struct cmsws_OperationLogPage_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     OperationLog Array
    //
    OperationLog** operationLogArray;
    //
    // Summary:
    //     Length of OperationLog array
    //
    int operationLogArrayLength;
    //
    // Summary:
    //     current page items
    //
    int pageSize;
    //
    // Summary:
    //     current page index
    //
    int currentPage;
    //
    // Summary:
    //     total items
    //
    int allRow;
    //
    // Summary:
    //     total pages
    //
    int totalPage;

} OperationLogPageResponse;

//
// Summary:
//     OperationLogReq
//
typedef struct cmsws_OperationLogReq
{
    int opterationLogId;
    int ctrlUnitId;

    cmsws_int64 beginTime;
    cmsws_int64 endTime;

    const char* logTxt;

    int mainType;
    int minorType;

    int resourceId;
    int userId;

} OperationLogReq;


//
// Summary:
//     MonitorLogMinorType
//
typedef struct cmsws_MonitorLogMinorType
{
    int minorType;
    const char* name;
    cmsws_int64 createTime;

} MonitorLogMinorType;

//
// Summary:
//     MonitorLogMinorTypeArrayResponse
//
typedef struct cmsws_MonitorLogMinorTypeArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     MonitorLogMinorType Array
    //
    MonitorLogMinorType** minorTypeArray;
    //
    // Summary:
    //     Length of MonitorLogMinorType array
    //
    int minorTypeArrayLength;

} MonitorLogMinorTypeArrayResponse;


//
// Summary:
//     WorkState
//
typedef struct cmsws_WorkState
{
    int objectId;
    int objectType;

    int stateType;
    const char* stateInfo;

    cmsws_int64 updateTime;

    int objectCtrlUnitId;
    const char* objectIp;
    const char* objectName;

} WorkState;

//
// Summary:
//     WorkStateResponse
//
typedef struct cmsws_WorkState_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     WorkState instance
    //
    WorkState* stateInfo;

} WorkStateResponse;

//
// Summary:
//     WorkStatePageResponse
//
typedef struct cmsws_WorkStatePage_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     WorkState Array
    //
    WorkState** workStateArray;
    //
    // Summary:
    //     Length of WorkState array
    //
    int workStateArrayLength;
    //
    // Summary:
    //     current page items
    //
    int pageSize;
    //
    // Summary:
    //     current page index
    //
    int currentPage;
    //
    // Summary:
    //     total items
    //
    int allRow;
    //
    // Summary:
    //     total pages
    //
    int totalPage;

} WorkStatePageResponse;


//
// Summary:
//     DecodeDevice
//
typedef struct cmsws_DecodeDevice
{
    int decodeDevId;
    const char* name;

    int decodeMod;
    const char* devType;

    const char* ipAddr;
    int port;

    const char* userName;
    const char* password;

    int controlUnitId;
    
} DecodeDevice;

//
// Summary:
//     DecodeDeviceArrayResponse
//
typedef struct cmsws_DecodeDeviceArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     DecodeDevice Array
    //
    DecodeDevice** decodeDeviceArray;
    //
    // Summary:
    //     Length of DecodeDevice array
    //
    int decodeDeviceArrayLength;

} DecodeDeviceArrayResponse;


//
// Summary:
//     DecodeServer
//
typedef struct cmsws_DecodeServer
{
    int decodeSvrId;
    const char* indexCode;
    const char* name;

    const char* ipAddr;
    int configPort;
    int ctrlPort;
    int dataPort;

    int workMod;
    short playbackBuf;
    short realBuf;
    short decodeMod;
    short videoSys;

    bool useSoftDog;
    int sequenceIdx;

    int netAgentPort;
    const char* secondIp;

    int controlUnitId;

} DecodeServer;

//
// Summary:
//     DecodeServerArrayResponse
//
typedef struct cmsws_DecodeServerArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     DecodeServer Array
    //
    DecodeServer** decodeServerArray;
    //
    // Summary:
    //     Length of DecodeServer array
    //
    int decodeServerArrayLength;

} DecodeServerArrayResponse;


//
// Summary:
//     OutputArea
//
typedef struct cmsws_OutputArea
{
	int alarmFlag;      // �Ƿ����ڱ���
    int areaIndex;      // �����������
    int decIndex;       // ����ͨ������
    int decodeResId;    // ������Դ��ˮ�� 
    int outputIndex;    // ���ͨ������
    int voutAreaId;     // ������ˮ��

	int groupId;
    const char* areaName;

} OutputArea;

//
// Summary:
//     OutputAreaArrayResponse
//
typedef struct cmsws_OutputAreaArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     ���������Ϣ���顣
    //
    OutputArea** outputAreaArray;
    //
    // Summary:
    //     ���������Ϣ���鳤�ȡ�
    //
    int outputAreaArrayLength;

} OutputAreaArrayResponse;


//
// Summary:
//     ScreenLayout
//
typedef struct cmsws_ScreenLayout
{
    int screenLayoutId;
    int userId;

    const char* name;
    int type;

    int height;
    int width;

    const char* xmlConfig;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} ScreenLayout;

//
// Summary:
//     ScreenLayoutArrayResponse
//
typedef struct cmsws_ScreenLayoutArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     ScreenLayout Array
    //
    ScreenLayout** screenLayoutArray;
    //
    // Summary:
    //     Length of ScreenLayout array
    //
    int screenLayoutArrayLength;

} ScreenLayoutArrayResponse;


//
// Summary:
//     PreviewGroupResource
//
typedef struct cmsws_PreviewGroupResource
{
    int previewGroupResId;
    const char* indexCode;

    int cyclePreviewGroupId;
    int presetNo;
    int resourceId;
    int resourceType;
    int sequenceIdx;

    int orderNum;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} PreviewGroupResource;

//
// Summary:
//     PreviewGroupResourcePageResponse
//
typedef struct cmsws_PreviewGroupResourcePage_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     PreviewGroupResource Array
    //
    PreviewGroupResource** previewGroupResourceArray;
    //
    // Summary:
    //     Length of PreviewGroupResource array
    //
    int previewGroupResourceArrayLength;
    //
    // Summary:
    //     current page items
    //
    int pageSize;
    //
    // Summary:
    //     current page index
    //
    int currentPage;
    //
    // Summary:
    //     total items
    //
    int allRow;
    //
    // Summary:
    //     total pages
    //
    int totalPage;

} PreviewGroupResourcePageResponse;


//
// Summary:
//     PreviewGroup
//
typedef struct cmsws_PreviewGroup
{
    int previewGroupId;
    const char* indexCode;
    const char* description;
    const char* name;
    
    int intervalTime;
    int screenLayoutId;
    int sequenceIdx;
    int shareMode;
    int type;
    int userId;

    int operatorId;             // ����ԱID
    cmsws_int64 createTime;     // ����ʱ��
    cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} PreviewGroup;

//
// Summary:
//     PreviewGroupArrayResponse
//
typedef struct cmsws_PreviewGroupArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     PreviewGroup Array
    //
    PreviewGroup** previewGroupArray;
    //
    // Summary:
    //     Length of PreviewGroup array
    //
    int previewGroupArrayLength;

} PreviewGroupArrayResponse;


//
// Summary:
//     EmapElementInformation
//
//typedef struct cmsws_EmapElementInfo
//{
//    const char* description;
//    const char* elementName;
//    const char* elementSubType;
//	const char* shapeXml;
//	const char* xmlRev;
//
//    int elementId;
//    int elementType;
//    int emapId;
//	int linkId;
//	int linkSubId;
//
//} EmapElementInformation;
typedef struct cmsws_EmapElementInfo
{
    int XPos;
    int YPos;
    const char* description;
    int elementId;
    const char* elementName;
    int elementType;
    int emapId;
    int iconId;
    bool isCustomIcon;
    int objectId;
    int objectSubId;

    int grounding;
    int outlineBorderColor;
    int style1;
    int style2;

    int intRev1;
    int intRev2;

    const char* strRev1;
    const char* strRev2;

} EmapElementInformation;

//
// Summary:
//     EmapElementInfoArrayResponse
//
typedef struct cmsws_EmapElementInfoArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     EmapElementInformation Array
    //
    EmapElementInformation** emapElementInfoArray;
    //
    // Summary:
    //     Length of EmapElementInformation array
    //
    int emapElementInfoArrayLength;

} EmapElementInfoArrayResponse;


//
// Summary:
//     EmapInformation
//
//typedef struct cmsws_EmapInfo
//{ 
//    const char* description;
//    const char* emapName;
//    const char* savePath;
//	const char* xmlRev;
//
//    double maxScale;
//    double minScale;
//
//	int emapId;
//    int parentEmapId;
//    int regionId;
//	int version;
//	int mapType;
//
//} EmapInformation;
typedef struct cmsws_EmapInfo
{ 
    const char* description;
    int emapId;
    const char* emapName;
    int parentEmapId;
    int regionId;
    const char* savePath;

    int version;

} EmapInformation;

//
// Summary:
//     EmapInfoArrayResponse
//
typedef struct cmsws_EmapInfoArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     EmapInformation Array
    //
    EmapInformation** emapInfoArray;
    //
    // Summary:
    //     Length of EmapInformation array
    //
    int emapInfoArrayLength;

} EmapInfoArrayResponse;


//
// Summary:
//     EmapPresetInfo
//
//typedef struct cmsws_EmapPresetInfo
//{
//    double XPos;
//    double YPos;
//    double zoomRate;
//    int emapId;
//    int emapPresetId;
//    int presetIndex;
//    const char* presetName;
//    int userId;
//    int gisId;
//
//    const char* xml;
//
//} EmapPresetInfo;
typedef struct cmsws_EmapPresetInfo
{
    double XPos;
    double YPos;
    double zoomRate;
    int emapId;
    int emapPresetId;
    int presetIndex;
    const char* presetName;
    int userId;
    int gisId;

} EmapPresetInfo;

//
// Summary:
//     EmapPresetInfoArrayResponse
//
typedef struct cmsws_EmapPresetInfoArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     EmapPresetInfo Array
    //
    EmapPresetInfo** emapPresetInfoArray;
    //
    // Summary:
    //     Length of EmapPresetInfo array
    //
    int emapPresetInfoArrayLength;

} EmapPresetInfoArrayResponse;


//
// Summary:
//     EmapPresetInfo
//
typedef struct cmsws_EmapGroup
{
    const char* description;
    const char* groupName;

    int emapId;
    int groupId;

} EmapGroup;

//
// Summary:
//     EmapGroupArrayResponse
//
typedef struct cmsws_EmapGroupArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     EmapGroup Array
    //
    EmapGroup** emapGroupArray;
    //
    // Summary:
    //     Length of EmapGroup array
    //
    int emapGroupArrayLength;

} EmapGroupArrayResponse;


//
// Summary:
//     ServerMultiIp
//
typedef struct cmsws_ServerMultiIp
{
    const char* svrIp;

    int netZoneId;
    int portType;
    int svrPort;

} ServerMultiIp;

//
// Summary:
//     ServerMultiIpArrayResponse
//
typedef struct cmsws_ServerMultiIpArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     ServerMultiIp Array
    //
    ServerMultiIp** serverMultiIpArray;
    //
    // Summary:
    //     Length of ServerMultiIp array
    //
    int serverMultiIpArrayLength;

} ServerMultiIpArrayResponse;


//
// Summary:
//     RecordState
//
typedef struct cmsws_RecordState
{
    int cameraId;   // ��ص��š�
    int deviceCode; // 0 - �豸û�жԸ�ͨ��¼�񣬷�������ֵ��
    int nvrCode;    // 0 - NVRû�жԸ�ͨ��¼�񣬷�������ֵ��

} RecordState;

//
// Summary:
//     RecordStateArrayResponse
//
typedef struct cmsws_RecordStateArray_response
{
    //
    // Summary:
    //     true - �����ɹ���
    //     false - ����ʧ�ܡ�
    //
    bool result;
    //
    // Summary:
    //     ����ʧ��ʱ���ش�����š�
    //     �����ɹ����� 0 ��
    //
    int errorCode;
    //
    // Summary:
    //     RecordState Array
    //
    RecordState** recordStateArray;
    //
    // Summary:
    //     Length of RecordState array
    //
    int recordStateArrayLength;

} RecordStateArrayResponse;

typedef struct cmsws_MonitorServer
{
	int controlUnitId;
	int ctrlPort;
	int dataPort;
	const char* indexCode;
	int intRev1;
	int intRev2;
	const char* ipAddr;
	const char* msgQueue;
	const char* name;
	int netMonSvId;
	const char* secondIp;
	int sequenceIdx;
	const char* strRev1;
	const char* strRev2;
	bool useSoftDog;

	int operatorId;             // ����ԱID
	cmsws_int64 createTime;     // ����ʱ��
	cmsws_int64 updateTime;     // ���һ�θ���ʱ��

} MonitorServer;

//added by hyl 20110916 begin
typedef struct cmsPower_WSRequest
{
    const char* indexCode;
    const char* sessionId;
    const char* type;
    int version;
}WSRequest;

typedef struct cmsPower_WSResponse
{
    int code;
    const char* msg;
    bool result;
    int version;
}WSResponse;

//added by hyl 20110916 end

//
// Summary:
//     �ָ��ṹ��Ĭ�϶��뷽ʽ��
//
// #pragma pack()


//
//
// Summary:
//     ZeroMemory
//
#ifndef ZeroMemory
#define ZeroMemory(dst, size) memset(dst, 0, size)
#endif


//
// Summary:
//     ��� runtime environment ��
//
#define GET_SOAP_ENV(rtn) \
    cmsws_soap* soapEnv = SoapWrapper::GetSoapEnv(); \
    if (!soapEnv) \
    { \
        return (rtn); \
    }

//
// Summary:
//     ����ռ䣬������ (char*)psz ���ݡ�
//
#define COPY_PSZ(pszDst, pszSrc) \
    { \
        (pszDst) = 0; \
        if ((void*)(pszSrc)) \
        { \
            int size = strlen((pszSrc)); \
            if (size > 0) \
            { \
                char* tmp = (char*)soap_malloc((soapEnv), size + 1); \
                if (tmp) \
                { \
                    memcpy(tmp, (pszSrc), size); \
                    *(tmp + size) = '\0'; \
                    (pszDst) = tmp; \
                } \
            } \
        } \
    }

//
// Summary:
//     �������Ƿ�������������������ô�����Ϣ�󷵻ء�
//
#define CHECK_PARAM_AND_SET_ERROR_AND_RETURN(param, condition, nError, pszFault, pszDetail, rtn) \
    if ((condition) == (param)) \
    { \
        char* faultString = 0; \
        COPY_PSZ(faultString, pszFault) \
        char* detailString = 0; \
        COPY_PSZ(detailString, pszDetail); \
        soap_set_sender_error((soapEnv), faultString, detailString, (nError)); \
        return (rtn); \
    }

//
// Summary:
//     ΪӦ�� gSoap �Կյ�ָ���������л�Ϊ����һ����Ԫ�ص����飬�ʶԴ��������������ĳ��ȡ�
//
#define CHECK_ARRAY_SIZE(pointer_array) \
    if (!(pointer_array) || ((pointer_array ## Length) == 1 && !(*(pointer_array)))) \
    { \
        (pointer_array ## Length) = 0; \
    }

//
// Summary:
//     ������������
//
#define CHECK_PARAM(param, condition, pszFault, rtn) \
    CHECK_PARAM_AND_SET_ERROR_AND_RETURN(param, condition, CMSWS_SOAP_PARAM_ERROR, pszFault, NULL, rtn)

//
// Summary:
//     ����ڴ���䡣
//
#define CHECK_MALLOC(param, pszFault, rtn) \
    CHECK_PARAM_AND_SET_ERROR_AND_RETURN(param, NULL, CMSWS_SOAP_MALLOC_ERROR, pszFault, NULL, rtn)

//
// Summary:
//     ��� axis2 webservice response ������
//
#define CHECK_RESPONSE(response, rtn) \
    CHECK_PARAM_AND_SET_ERROR_AND_RETURN(response->return_, NULL, CMSWS_SOAP_RESPONSE_NIL, NULL, NULL, rtn)

//
// Summary:
//     ��� NVR Web Service ��ڡ�
//
#define CHECK_SERVICE_ENTRY(entry, pszFault, rtn) \
    CHECK_PARAM_AND_SET_ERROR_AND_RETURN(entry, NULL, CMSWS_SOAP_SKEL_NO_SERVICE_ENTRY, pszFault, NULL, rtn)


//
// Summary:
//     ��ȡ service endpoint uri ��
//
#define GET_ENDPOINT_URI(newUri) \
    ((newUri) ? (newUri) : SoapWrapper::GetEndpointUri())


//
// Summary:
//     ��ȡ string* Ϊ const char* ��
//
// Remarks:
//     ����ʹ�� STL string ������ char* ��
//
//     ��Ҫ�Դ��ݵ��ַ������� UTF-8 �� MB ת�롣
//
// #define GET_C_STR(string_pointer) ((string_pointer) ? (string_pointer)->c_str() : 0)
// #define GET_C_STR(string_pointer) ((const char*)(string_pointer))
#define GET_C_STR(string_pointer) (platform_u82mb((soapEnv), (const char*)(string_pointer)))

//
// Summary:
//     ��ȡ *(std_type_pointer) �� value ��
//
#define GET_STV_DEFAULT(std_type_pointer, default_value) \
    ((std_type_pointer) ? *(std_type_pointer) : (default_value))


//
// Summary:
//     ����ռ䣬������ (char*)psz ���ݡ�
//
// Remarks:
//     ��Ҫ�Ի�ȡ���ַ������� MB �� UTF-8 ת�롣
//
//#define CHECK_COPY_PSZ(pszDst, pszSrc, pszFault, rtn) \
//    { \
//        (pszDst) = 0; \
//        if ((pszSrc)) \
//        { \
//            int size = strlen((pszSrc)); \
//            if (size > 0) \
//            { \
//                char* tmp = (char*)soap_malloc((soapEnv), size + 1); \
//                CHECK_MALLOC(tmp, (pszFault), (rtn)); \
//                memcpy(tmp, (pszSrc), size); \
//                *(tmp + size) = '\0'; \
//                (pszDst) = tmp; \
//            } \
//        } \
//    }
#define CHECK_COPY_PSZ(pszDst, pszSrc, pszFault, rtn) \
    { \
        (pszDst) = ""; \
        if ((void*)(pszSrc)) \
        { \
            int size = strlen((pszSrc)); \
            if (size > 0) \
            { \
                pszDst = platform_mb2u8((soapEnv), pszSrc); \
                CHECK_MALLOC((pszDst), (pszFault), (rtn)); \
            } \
        } \
    }

//
// Summary:
//     ����ռ䣬������ std_type �� value ��
//
#define CHECK_COPY_STV(std_type_dst_pointer, std_type_size, std_type_src, pszFault, rtn) \
    soap_malloc((soapEnv), (std_type_size)); \
    CHECK_MALLOC((std_type_dst_pointer), (pszFault), (rtn)); \
    memcpy((std_type_dst_pointer), &(std_type_src), (std_type_size))

//
// Summary:
//     ���� n �������ռ䣬���� 0 ��
//
#define CHECK_AND_ZERO_MALLOC_N(dst_pointer, dst_type_size, n, pszFault, rtn) \
    soap_malloc((soapEnv), (dst_type_size) * (n)); \
    CHECK_MALLOC((dst_pointer), (pszFault), (rtn)); \
    ZeroMemory((dst_pointer), (dst_type_size) * (n))

//
// Summary:
//     ����ռ䣬���� 0 ��
#define CHECK_AND_ZERO_MALLOC(dst_pointer, dst_type_size, pszFault, rtn) \
    CHECK_AND_ZERO_MALLOC_N(dst_pointer, dst_type_size, 1, pszFault, rtn)

