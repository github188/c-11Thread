#pragma once
//
// Copyright (c) 2009 Hikvision Digital Technology Co., Ltd.
//
// Summary:
//     CMS WebService 相关定义。
//
// Modification History:
//   2009-09-29:
//     V1.0 / 胡通海 / 创建
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
    //     CMS WebService API 类型定义
    //
    #define CMSWS_API __stdcall

    //
    // Summary:
    //     TLS 声明宏
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
    //     CMS WebService API 类型定义
    //
    #define CMSWS_API 

    //
    // Summary:
    //     TLS 声明宏
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
//     cmsws 返回值定义。
//
#define CMSWS_SUCCESS   1   // 操作成功
#define CMSWS_FAILURE   0   // 操作失败


//
// Summary:
//     cmsws service stub 错误定义。
//
#define CMSWS_SOAP_PARAM_ERROR          0x01000001      // 传入参数无效
#define CMSWS_SOAP_MALLOC_ERROR         0x01000002      // 分配内存错误
#define CMSWS_SOAP_RESPONSE_NIL         0x01000003      // 服务器回复的 XML 为空
#define CMSWS_SOAP_ERROR_CODE_NIL       0x01000004      // 服务器回复的 errorCode 为空

//
// Summary:
//     cmsws service skel 错误定义。
//
#define CMSWS_SOAP_SKEL_NO_SERVICE_ENTRY    0x02000001  // 服务函数入口不存在


//
// Summary:
//     调用 CMS WebService 返回的 errorCode 定义
//
#define CMS_SUCCESSED                   0                //操作成功
#define CMS_FAILED                      10000            //操作失败

//用户登录错误码
#define CMS_USERNAME_ERROR              10001            //用户名不存在
#define CMS_PWD_ERROR                   10002            //密码错误
#define CMS_USER_HAS_LOGIN              10003            //用户已经登录
#define CMS_USER_NOT_EXCLUSIVE          10004            //用户名称不唯一
#define CMS_USER_EXPIRED                10005            //用户已经过期
#define CMS_USER_DELETE                 10006            //用户被删除

#define CMS_USERSESSION_NOT_EXIST       10010            //用户会话ID不存在

//添加错误码
#define CMS_INDEX_CODE_HAS_EXIST        20001            //索引编码已经存在
#define CMS_PARENT_ID_ERROR             20002            //夫ID错误
#define CMS_ID_NOT_EXIST                20003            //ID值不存在
#define CMS_USER_NAME_EXIST             20004            //用户名已经存在
#define CMS_INTERNAL_ERROR              20005            //系统内部错误

//数据库查询错误码
#define CMS_SELECT_NONE                 30001            //查询不到内容


//服务器类型
#define OBJECT_TYPE_SERVER              20000 // 服务器相关
#define OBJECT_TYPE_VRM_SVR             20001 // VRM
#define OBJECT_TYPE_PCNVR_SVR           20002 // PC_NVR
#define OBJECT_TYPE_NVTPROXY            20003 // NVT_PROXY
#define OBJECT_TYPE_STREAM_SVR          20004 // 流媒体服务器
#define OBJECT_TYPE_ALARM_SVR           20005 // 报警服务器
#define OBJECT_TYPE_DECODE_SVR          20006 // 解码服务器
#define OBJECT_TYPE_DECODE_PROXY_SVR    20007 // 电视墙代理服务器（监视屏组）
#define OBJECT_TYPE_PCNVR_SVR_BN        20008 // 嵌入式存储
#define OBJECT_TYPE_NM_SVR              20009 // 网管服务器
#define OBJECT_TYPE_CASE_SVR            20010 // 案件管理服务器
#define OBJECT_TYPE_PTZ_SERVER          20011 // 云台代理服务器
#define OBJECT_TYPE_INTER_AREA          20012 // 级联服务器


//
// Summary:
//     设定结构体最大按 4 字节对齐。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     新增记录的编号。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;

} CommonResultResponse;

//
// Summary:
//     LoginRestriction
//
typedef struct cmsws_LoginRestriction
{
    int restrictId;             // 限制表 ID
    bool timeRestrict;          // 是否进行时间限制登录，0 表示不限制，1 表示限制
    cmsws_int64 beginTime;      // 每天的登录开始时间
    cmsws_int64 endTime;        // 每天登录的结束时间
    bool ipRestrict;            // 是否进行 IP 地址限制，0 表示不限制，1 表示限制
    const char* ipAddr;         // IP 地址限制

    int operatorId;             // 操作人员 ID，如果是根用户则为 0
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} LoginRestriction;

//
// Summary:
//     UserInfo
//
typedef struct cmsws_UserInfo
{
    int userId;                             // 用户id 值
    const char* name;                       // 用户名
    const char* pwd;                        // 用户密码
    int status;                             // 0-正常，1-冻结，2-注销
    int controlUnitId;                      // 用户所属的控制单元的 ID
    const char* realName;                   // 用户的真实姓名
    const char* phoneNo;                    // 用户的电话号码
    const char* email;                      // 用户的 E-MAIL 地址
    int loginTimes;                         // 用户登录次数
    cmsws_int64 lastLoginTime;              // 最后登录时间
    cmsws_int64 expireTime;                 // 失效时间
    int sequenceIdx;                        // 排序索引
    const char* description;                // 备注信息

    short priority;
    int restrictId;

    int operatorId;                         // 操作人员 ID，如果是根用户则为 0
    cmsws_int64 createTime;                 // 创建时间
    cmsws_int64 updateTime;                 // 最后一次更新时间

} UserInfo;

//
// Summary:
//     UserInfoArrayResponse
//
typedef struct cmsws_UserInfoArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     用户信息数组。
    //
    UserInfo** userInfoArray;
    //
    // Summary:
    //     用户信息数组长度。
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
    int id;                     // 控制单元 ID
    const char* indexCode;      // 索引编号
    const char* name;           // 区域名称
    const char* description;    // 备注信息
    int parentId;               // 上级域的 ID ，0 表示根域
    int unitLevel;              // 控制单元所属的级别，根单元为 0 ，其他表示所属的层次
    bool useStreamSvr;          // 是否使用流媒体
    int streamSvId;             // 流媒体服务器编号
    int sequenceIdx;            // 排序索引

    int cmsCascadeId;
    int cmsCascadeType;

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} ControlCenterInfo, ControlUnit;


//
// Summary:
//     ControlCenterInfo
//
typedef struct cmsws_ControlCenterWithPrivilege
{
    int id;                     // 控制单元 ID
    const char* indexCode;      // 索引编号
    const char* name;           // 区域名称
    const char* description;    // 备注信息
    int parentId;               // 上级域的 ID ，0 表示根域
    int unitLevel;              // 控制单元所属的级别，根单元为 0 ，其他表示所属的层次
    bool useStreamSvr;          // 是否使用流媒体
    int streamSvId;             // 流媒体服务器编号
    int sequenceIdx;            // 排序索引

    int cmsCascadeId;
    int cmsCascadeType;

    int* privilegeCodeArray;
    int privilegeCodeArrayLength;

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} ControlCenterWithPrivilege;

//
// Summary:
//     ControlCenterWithPrivilegeResponse
//
typedef struct cmsws_ControlCenterWithPrivilege_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     ControlCenterWithPrivilege Array 。
    //
    ControlCenterWithPrivilege** controlCenterInfoArray;
    //
    // Summary:
    //     Length of ControlCenterWithPrivilege array。
    //
    int controlCenterInfoArrayLength;

} ControlCenterWithPrivilegeArrayResponse;


//
// Summary:
//     RegionInfo
//
typedef struct cmsws_RegionInfo
{
    int regionId;               // 区域ID表
    const char* indexCode;      // 索引编号
    const char* name;           // 区域名称
    int parentId;               // 上级域的 ID，0 表示根域
    int regionLevel;            // 区域所属的级别，根单元为0，其他表示所属的层次
    int controlUnitId;          // 所属的控制单元
    bool useStreamSv;           // 是否使用流媒体
    int streamSvId;             // 流媒体编号

    int operatorId;             // 操作人员 ID，如果是根用户则为 0
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} RegionInfo;

//
// Summary:
//     RegionInfoArrayResponse
//
typedef struct cmsws_RegionInfoArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     区域信息数组。
    //
    RegionInfo** regionInfoArray;
    //
    // Summary:
    //     区域信息数组长度。
    //
    int regionInfoArrayLength;

} RegionInfoArrayResponse;


//
// Summary:
//     RegionInfoWithPrivilege
//
typedef struct cmsws_RegionInfoWithPrivilege
{
    int regionId;               // 区域ID表
    const char* indexCode;      // 索引编号
    const char* name;           // 区域名称
    int parentId;               // 上级域的 ID，0 表示根域
    int regionLevel;            // 区域所属的级别，根单元为0，其他表示所属的层次
    int controlUnitId;          // 所属的控制单元
    bool useStreamSv;           // 是否使用流媒体
    int streamSvId;             // 流媒体编号

    int* privilegeCodeArray;
    int privilegeCodeArrayLength;

    int operatorId;             // 操作人员 ID，如果是根用户则为 0
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     RegionInfoWithPrivilege Array 。
    //
    RegionInfoWithPrivilege** regionInfoArray;
    //
    // Summary:
    //     Length of RegionInfoWithPrivilege array。
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
    int planId;                     // 轮循计划流水号
    const char* planName;           // 轮循名称
    cmsws_int64 startTime;          // 开始时间
    cmsws_int64 stopTime;           // 结束时间
    int cycleTime;                  // 轮循时间
    int groupId;                    // 监视屏组编号
    int cyclePlanType;

    int* cycleAreaIdArray;          // 轮循区域数组
    int cycleAreaIdArrayLength;     // 轮循区域数组长度

    int* cycleCameraIdArray;        // 轮循监控点数组
    int cycleCameraIdArrayLength;   // 轮循监控点数组长度

} CyclePlan;

//
// Summary:
//     CyclePlanArrayResponse
//
typedef struct cmsws_CyclePlanArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     轮循计划信息数组。
    //
    CyclePlan** cyclePlanArray;
    //
    // Summary:
    //     轮循计划信息数组长度。
    //
    int cyclePlanArrayLength;

} CyclePlanArrayResponse;


//
// Summary:
//     AudioOut
//
typedef struct cmsws_AudioOut
{
    int aoId;                   // 声音输出流水号
    int aoIndex;                // 声音输出通道索引
    const char* aoName;         // 声音输出通道名称
    short outFlag;              // 声音通道是否打开
    int decodeResId;            // 服务器ID号

    int operatorId;             // 操作人员 ID，如果是根用户则为 0
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} AudioOut;

//
// Summary:
//     AudioOutArrayResponse
//
typedef struct cmsws_AudioOutArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     声音输出通道数组
    //
    AudioOut** audioOutArray;
    //
    // Summary:
    //     声音输出通道数组长度
    //
    int audioOutArrayLength;

} AudioOutArrayResponse;


//
// Summary:
//     VoutArea
//
typedef struct cmsws_VoutArea
{
    int areaIndex;              // 输出区域索引
    const char* areaName;       // 输出区域名称
    int alarmFlag;              // 是否用于报警
    int decIndex;               // 关联解码通道
    int voId;                   // 输出区域流水号

    int voutAreaId;             // vout_area 表编号

    int operatorId;             // 操作人员 ID，如果是根用户则为 0
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} VoutArea;


//
// Summary:
//     VrmServer
//
typedef struct cmsws_VrmServer
{
    const char* ipAddr;         // 
    int ctrlPort;               // 控制端口

    int vrmId;                  // 服务器ID号
    const char* indexCode;      // 索引编号
    const char* name;           // 服务器名称
    int controlUnitId;          // 控制单元ID

    short maxRecordTask;        // 最大的同时录像任务数
    short maxTaskPerIpsan;      // 每台IP-SAN最多同时执行的录像任务数
    short maxVodPerIpsan;       // 

    int freeSpace;              // 未分配的存储空间
    int totalSpace;             // 存储空间总容量

    bool useSoftDog;            // 是否启用软件狗
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} VrmServer;

//
// Summary:
//     VrmServerArrayResponse
//
typedef struct cmsws_VrmServerArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     vrm 数组。
    //
    VrmServer** vrmServerArray;
    //
    // Summary:
    //     vrm 数组长度。
    //
    int vrmServerArrayLength;

} VrmServerArrayResponse;

//
// Summary:
//     StreamServer
//
typedef struct cmsws_StreamServer
{
    int streamSvId;             // 服务器ID号
    int controlUnitId;          // 控制单元ID
    const char* indexCode;      // 索引编号
    const char* name;           // 服务器名称
    const char* ipAddr;         // 
    int ctrlPort;               // 控制端口
    int rtspPort;               // RTSP侦听端口
    
    short shareFlag;            // 是否允许下级控制中心使用，1表示可以使用，0表示不允许使用
    const char* relativePath;   // 文件点播相对路径
    int sequenceIdx;            // 

    int netAgentPort;
    int rtpTcpBasePort;
    int rtpUdpBasePort;
    const char* secondIp;
    int udpPortCount;
    
    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} StreamServer;

//
// Summary:
//     StreamServerArrayResponse
//
typedef struct cmsws_StreamServerArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     StreamServer 数组。
    //
    StreamServer** streamServerArray;
    //
    // Summary:
    //     StreamServer 数组长度。
    //
    int streamServerArrayLength;

} StreamServerArrayResponse;

//
// Summary:
//     AlarmServer
//
typedef struct cmsws_AlarmServer
{
    int alarmSvId;              // 服务器ID号
    int controlUnitId;          // 控制单元ID
    const char* indexCode;      // 索引编号
    const char* name;           // 服务器名称
    const char* ipAddr;         // 
    int ctrlPort;               // 控制端口
    bool useSoftDog;            // 是否启用软件狗
    short workMode;             // 工作模式（0-监听，1-布防）
    int sequenceIdx;            // 

    int netAgentPort;
    const char* secondIp;
    const char* smsCom;
    int maListenPort;
    int notifyWay;

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} AlarmServer;

//
// Summary:
//     AlarmServerArrayResponse
//
typedef struct cmsws_AlarmServerArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     AlarmServer 数组。
    //
    AlarmServer** alarmServerArray;
    //
    // Summary:
    //     AlarmServer 数组长度。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} PcnvrServer;

//
// Summary:
//     PcnvrServerArrayResponse
//
typedef struct cmsws_PcnvrServerArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     PcnvrServer 数组。
    //
    PcnvrServer** pcnvrServerArray;
    //
    // Summary:
    //     PcnvrServer 数组长度。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间
    
} PtzServer;

//
// Summary:
//     PtzServerArrayResponse
//
typedef struct cmsws_PtzServerArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     PtzServer 数组。
    //
    PtzServer** ptzServerArray;
    //
    // Summary:
    //     PtzServer 数组长度。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

	int operatorId;             // 操作员ID
	cmsws_int64 createTime;     // 创建时间
	cmsws_int64 updateTime;     // 最后一次更新时间

} VrbServer;



//
// Summary:
//     AllVrbInfoArrayResponse
//
typedef struct cmsws_VrbServerArray_response
{
	//
	// Summary:
	//     true - 操作成功。
	//     false - 操作失败。
	//
	bool result;
	//
	// Summary:
	//     操作失败时返回错误代号。
	//     操作成功返回 0 。
	//
	int errorCode;
	//
	// Summary:
	//     PtzServer 数组。
	//
	VrbServer** vrbServerArray;
	//
	// Summary:
	//     PtzServer 数组长度。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     InterAreaServer 数组。
    //
    InterAreaServer** interAreaServerArray;
    //
    // Summary:
    //     InterAreaServer 数组长度。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     InterAreaServer 数组。
    //
    PAGServer** PAGServerArray;
    //
    // Summary:
    //     InterAreaServer 数组长度。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     AlarmServer 数组。
    //
    AlarmServer** alarmServerArray;
    //
    // Summary:
    //     AlarmServer 数组长度。
    //
    int alarmServerArrayLength;
	//
	// Summary:
	//     PcnvrServer 数组。
	//
	PcnvrServer** pcnvrServerArray;
	//
	// Summary:
	//     PcnvrServer 数组长度。
	//
	int pcnvrServerArrayLength;
    //
    // Summary:
    //     StreamServer 数组。
    //
    StreamServer** streamServerArray;
    //
    // Summary:
    //     StreamServer 数组长度。
    //
    int streamServerArrayLength;
    //
    // Summary:
    //     VrmServer 数组。
    //
    VrmServer** vrmServerArray;
    //
    // Summary:
    //     VrmServer 数组长度。
    //
    int vrmServerArrayLength;
    //
    // Summary:
    //     PtzServer 数组。
    //
    PtzServer** ptzServerArray;
    //
    // Summary:
    //     PtzServer 数组长度。
    //
    int ptzServerArrayLength;
    //
    // Summary:
    //     InterAreaServer 数组。
    //
    InterAreaServer** interAreaServerArray;
    //
    // Summary:
    //     InterAreaServer 数组长度。
    //
    int interAreaServerArrayLength;
    //
    // Summary:
    //     PAGServerArray 数组。
    //
    PAGServer** PAGServerArray;
    //
    // Summary:
    //     PAGServerArrayLength 数组长度。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} PresetInfo;

//
// Summary:
//     PresetInfoArrayResponse
//
typedef struct cmsws_PresetInfoArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    int groupId;                // 监视屏组流水号（代理服务器ID）
    const char* groupName;      // 监视屏组的名称
    const char* proxyIp;        // 代理服务器IP
    int proxyPort;              // 代理服务器端口

    int controlUnitId;

    int alarmTime;
    int configPort;
    int netAgentPort;
    const char* secondIp;

    int* privilegeCodeArray;
    int privilegeCodeArrayLength;

    int operatorId;             // 操作人员 ID，如果是根用户则为 0
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     监视屏组信息数组。
    //
    MonitorScreenGroupWithPrivilege** monitorScreenGroupArray;
    //
    // Summary:
    //     监视屏组信息数组长度。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    int typeCode;               // 类型编号
    const char* name;           // 设备名称
    int registerType;           // 注册类型,0-普通/1-私有域名/2-普通域名
    const char* networkAddr;    // 设备的IP地址
    int networkPort;            // 网络端口
    const char* userName;       // 设备登录的用户名
    const char* userPwd;        // 用户密码

    int deviceId;
    const char* indexCode;      // 索引编号
    int controlUnitId;          // 所属的控制单元
    const char* dnsAddr;        // dns的IP地址
    int dnsPort;                // dns的端口号
    const char* serialNo;       // 设备序列号,用来在使用IP-Server时查询
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     设备信息数组。
    //
    DeviceInfo** deviceInfoArray;
    //
    // Summary:
    //     设备信息数组长度。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} AlarmChannelInfo;

//
// Summary:
//     AlarmChannelInfoArrayResponse
//
typedef struct cmsws_AlarmChannelInfoArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} AlarmDevice;

//
// Summary:
//     AlarmDeviceArrayResponse
//
typedef struct cmsws_AlarmDeviceArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    int cameraId;                   // 通道ID
    int cameraType;                 // 监控点类型，0-枪机/1-半球/2-快球/3-云台
    int chanNum;                    // 通道号，从1开始
    int connectType;                // 监控点连接协议,0-TCP/1-UDP/2-MCAST/3-RTP
    int deviceId;                   // 设备ID
    const char* indexCode;          // 索引编号
    const char* name;               // 监控点名称
    int *privilegeCodeArray;        // 权限代码数组
    int privilegeCodeArrayLength;   // 权限代码数组长度

    int* recLacationArray;
    int recLacationArrayLength;

    int regionId;                   // 区域ID
    int sequenceIndex;              // 排队序号
    short shareFlag;                // 0表示不与其它共享，1表示与其它控制单元共享
    int streamType;                 // 0-主码流 1-子码流

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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    const char* indexCode;          // 索引编号
    const char* name;               // 设备名称
    int controlUnitId;              // 所属的控制单元

    int* privilegeCodeArray;             // 权限代码数组
    int privilegeCodeArrayLength;        // 权限代码数组长度

    int typeCode;                   // 类型编号
    const char* serialNo;           // 设备序列号,用来在使用IP-Server时查询

    int registerType;               // 注册类型,0-普通/1-私有域名/2-普通域名
    const char* networkAddr;        // 设备的IP地址
    int networkPort;                // 网络端口
    const char* dnsAddr;            // dns的IP地址
    int dnsPort;                    // dns的端口号

    const char* userName;           // 设备登录的用户名
    const char* userPwd;            // 用户密码

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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} CameraInfo;

//
// Summary:
//     CameraInfoArrayResponse
//
typedef struct cmsws_CameraInfoArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间

} DeviceLog;

//
// Summary:
//     DeviceLogPageResponse
//
typedef struct cmsws_DeviceLogPage_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间

} MonitorLog;

//
// Summary:
//     MonitorLogPageResponse
//
typedef struct cmsws_MonitorLogPage_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
	int alarmFlag;      // 是否用于报警
    int areaIndex;      // 输出区域索引
    int decIndex;       // 解码通道索引
    int decodeResId;    // 解码资源流水号 
    int outputIndex;    // 输出通道索引
    int voutAreaId;     // 区域流水号

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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
    //
    int errorCode;
    //
    // Summary:
    //     输出区域信息数组。
    //
    OutputArea** outputAreaArray;
    //
    // Summary:
    //     输出区域信息数组长度。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} ScreenLayout;

//
// Summary:
//     ScreenLayoutArrayResponse
//
typedef struct cmsws_ScreenLayoutArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} PreviewGroupResource;

//
// Summary:
//     PreviewGroupResourcePageResponse
//
typedef struct cmsws_PreviewGroupResourcePage_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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

    int operatorId;             // 操作员ID
    cmsws_int64 createTime;     // 创建时间
    cmsws_int64 updateTime;     // 最后一次更新时间

} PreviewGroup;

//
// Summary:
//     PreviewGroupArrayResponse
//
typedef struct cmsws_PreviewGroupArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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
    int cameraId;   // 监控点编号。
    int deviceCode; // 0 - 设备没有对该通道录像，否则其他值。
    int nvrCode;    // 0 - NVR没有对该通道录像，否则其他值。

} RecordState;

//
// Summary:
//     RecordStateArrayResponse
//
typedef struct cmsws_RecordStateArray_response
{
    //
    // Summary:
    //     true - 操作成功。
    //     false - 操作失败。
    //
    bool result;
    //
    // Summary:
    //     操作失败时返回错误代号。
    //     操作成功返回 0 。
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

	int operatorId;             // 操作员ID
	cmsws_int64 createTime;     // 创建时间
	cmsws_int64 updateTime;     // 最后一次更新时间

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
//     恢复结构体默认对齐方式。
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
//     检查 runtime environment 。
//
#define GET_SOAP_ENV(rtn) \
    cmsws_soap* soapEnv = SoapWrapper::GetSoapEnv(); \
    if (!soapEnv) \
    { \
        return (rtn); \
    }

//
// Summary:
//     申请空间，并拷贝 (char*)psz 内容。
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
//     检查参数是否符合条件，若否，则设置错误信息后返回。
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
//     为应对 gSoap 对空的指针数组序列化为具有一个空元素的数组，故对此种情况纠正数组的长度。
//
#define CHECK_ARRAY_SIZE(pointer_array) \
    if (!(pointer_array) || ((pointer_array ## Length) == 1 && !(*(pointer_array)))) \
    { \
        (pointer_array ## Length) = 0; \
    }

//
// Summary:
//     检查输入参数。
//
#define CHECK_PARAM(param, condition, pszFault, rtn) \
    CHECK_PARAM_AND_SET_ERROR_AND_RETURN(param, condition, CMSWS_SOAP_PARAM_ERROR, pszFault, NULL, rtn)

//
// Summary:
//     检查内存分配。
//
#define CHECK_MALLOC(param, pszFault, rtn) \
    CHECK_PARAM_AND_SET_ERROR_AND_RETURN(param, NULL, CMSWS_SOAP_MALLOC_ERROR, pszFault, NULL, rtn)

//
// Summary:
//     检查 axis2 webservice response 参数。
//
#define CHECK_RESPONSE(response, rtn) \
    CHECK_PARAM_AND_SET_ERROR_AND_RETURN(response->return_, NULL, CMSWS_SOAP_RESPONSE_NIL, NULL, NULL, rtn)

//
// Summary:
//     检查 NVR Web Service 入口。
//
#define CHECK_SERVICE_ENTRY(entry, pszFault, rtn) \
    CHECK_PARAM_AND_SET_ERROR_AND_RETURN(entry, NULL, CMSWS_SOAP_SKEL_NO_SERVICE_ENTRY, pszFault, NULL, rtn)


//
// Summary:
//     获取 service endpoint uri 。
//
#define GET_ENDPOINT_URI(newUri) \
    ((newUri) ? (newUri) : SoapWrapper::GetEndpointUri())


//
// Summary:
//     提取 string* 为 const char* 。
//
// Remarks:
//     不再使用 STL string ，改用 char* 。
//
//     需要对传递的字符串进行 UTF-8 到 MB 转码。
//
// #define GET_C_STR(string_pointer) ((string_pointer) ? (string_pointer)->c_str() : 0)
// #define GET_C_STR(string_pointer) ((const char*)(string_pointer))
#define GET_C_STR(string_pointer) (platform_u82mb((soapEnv), (const char*)(string_pointer)))

//
// Summary:
//     提取 *(std_type_pointer) 的 value 。
//
#define GET_STV_DEFAULT(std_type_pointer, default_value) \
    ((std_type_pointer) ? *(std_type_pointer) : (default_value))


//
// Summary:
//     申请空间，并拷贝 (char*)psz 内容。
//
// Remarks:
//     需要对获取的字符串进行 MB 到 UTF-8 转码。
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
//     申请空间，并拷贝 std_type 的 value 。
//
#define CHECK_COPY_STV(std_type_dst_pointer, std_type_size, std_type_src, pszFault, rtn) \
    soap_malloc((soapEnv), (std_type_size)); \
    CHECK_MALLOC((std_type_dst_pointer), (pszFault), (rtn)); \
    memcpy((std_type_dst_pointer), &(std_type_src), (std_type_size))

//
// Summary:
//     申请 n 个连续空间，并置 0 。
//
#define CHECK_AND_ZERO_MALLOC_N(dst_pointer, dst_type_size, n, pszFault, rtn) \
    soap_malloc((soapEnv), (dst_type_size) * (n)); \
    CHECK_MALLOC((dst_pointer), (pszFault), (rtn)); \
    ZeroMemory((dst_pointer), (dst_type_size) * (n))

//
// Summary:
//     申请空间，并置 0 。
#define CHECK_AND_ZERO_MALLOC(dst_pointer, dst_type_size, pszFault, rtn) \
    CHECK_AND_ZERO_MALLOC_N(dst_pointer, dst_type_size, 1, pszFault, rtn)

