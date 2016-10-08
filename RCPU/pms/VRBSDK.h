#ifndef VRBSDK_h__
#define VRBSDK_h__

#include "vrb_error.h"
#if (defined _WIN32 || defined _WIN64)
#   ifndef  VRBCLIENTSDK_EXPORTS
#       define VS_API __declspec(dllimport)
#   else
#       define VS_API  __declspec(dllexport)
#   endif
#	 define VS_CALLBACK __stdcall
#else
#   define VS_API 
#	define VS_CALLBACK 
#endif

//定义export函数的命名规则
#ifdef __cplusplus //c++
extern "C" {
#endif

typedef int VRB_HANDLE;

enum CALLBACK_STATUS{ CONTINE_RUN = 1,  /*继续执行*/
									STOP_RUN  /*终止执行*/};

#pragma pack(4)
struct DispathSvrInfo
{
    int dispath_svr_port;                  ///<调度服务器的端口
    char dispath_svr_ip[32];                 ///<调度服务器的ip
};
#pragma pack()

/** @fn CALLBACK_STATUS VS_CALLBACK (msg_fun*)(void* userdata, int progress)
 *  @brief 上传或者下载图片时使用的消息回调函数
 *  @param userdata[in] 用户自定义的数据
 *  @param progress[in] 执行进度
 *  @return CALLBACK_STATUS : 返回执行指令：是否需要继续执行
 */
typedef CALLBACK_STATUS (VS_CALLBACK *msg_fun)(void* userdata, int progress);

#define VRB_MAX_GUID_LEN		64    ///<GUID最长长度
#define VRB_MAX_PIC_URL_LEN		256	///<图片url的最长长度
#define VRB_MAX_GROUP_LEN		128	///<VRB中分组名的最大长度
#define VRB_MAX_GROUP_NUM		40		///<VRB中分组名的最大数量
#define VRB_MAX_DISK_LEN          64  ///<VRB中配置的存储磁盘的的最大长度
#define VRB_MAX_DISK_NUM			40    ///<VRB中配置的存储磁盘的最大数量

#define  VRB_INVALID_HANLDE 0 ///<无效的句柄值

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_init(  )
 *  @brief 初始化函数,内部启用日志模块时，需要使用到“log4cxx.properties”日志配置文件，如果当前目录下没有该文件，将会导致初始化失败
 *  @return VRB_ERROR_CODE : 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_init();

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_fini(  )
 *  @brief 反初始化函数
 *  @return VRB_ERROR_CODE : 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_fini();

/** @fn VS_API char* VS_CALLBACK vs_get_error_msg( VRB_ERROR_CODE error_id, char msg_bug[VRB_MAX_ERROR_MSG_LEN] )
 *  @brief 获取VRB中error id对应的错误内容
 *  @param error_id [in] VRB返回的，其他程序返回的均无效
 *  @param msg_buf [out] error id对应的错误内容
 *  @return char* : msg_bug的地址，方便调用。（注：不会返回NULL,除非msg_bug==NULL）
 */
VS_API char* VS_CALLBACK vs_get_error_msg(VRB_ERROR_CODE error_id, char msg_buf[VRB_MAX_ERROR_MSG_LEN]);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_set_timeout( int recv_timeout, int send_timeout )
 *  @brief 设置超时时间，不调用该函数，将使用默认的超时时间: 5秒
 *  @param recv_timeout [in] 接收超时时间，单位ms,取值范围： 1 - 30*1000 毫秒
 *  @param send_timeout [in] 发送超时时间，单位ms,取值范围： 1 - 30*1000 毫秒
 *  @return VRB_ERROR_CODE : 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_set_timeout(int recv_timeout, int send_timeout);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_conn_pms( const char* ip, int port, VRB_HANDLE* svr_handle )
 *  @brief 创建与图片服务器操作相关的对象，与图片服务器相关的函数都需要使用该句柄，长期有效，内部自动维护连接。
 *  @param ip [in] vrb的ip
 *  @param port [in] vrb的http 端口
 *  @param svr_handle [out] 与vrb服务器相关的句柄。
 *  @return VRB_ERROR_CODE : 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_conn_pms(const char* ip, int port, VRB_HANDLE* svr_handle);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_conn_clusters( DispathSvrInfo* dispath_svr_info, unsigned int elem_count, VRB_HANDLE* clusters_handle )
 *  @brief 创建连接集群的对象句柄，与集群相关的函数都需要使用该句柄，长期有效，内部自动维护连接
 *  @param dispath_svr_info [in] 调度服务器的信息数组
 *  @param elem_count [in] 数组的元素数量,最大为20
 *  @param clusters_handle [out] 集群的对象句柄，与集群相关的函数都需要使用该句柄
 *  @return VRB_ERROR_CODE: 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_conn_clusters(DispathSvrInfo* dispath_svr_info, unsigned int elem_count, VRB_HANDLE* clusters_handle );

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_disconn( VRB_HANDLE svr_handle )
 *  @brief 销毁由vs_conn_clusters、vs_conn_pms返回的句柄资源
 *  @param svr_handle [in] 由vs_conn_clusters、vs_conn_pms返回的句柄
 *  @return VRB_ERROR_CODE : 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_disconn(VRB_HANDLE svr_handle);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_upload_pic( VRB_HANDLE svr_handle, const char* data, int len, const char* group_name, char url[URL_PIC_MAX_LEN], msg_fun msg_fun_name, void* userdata )
 *  @brief 上传图片
 *  @param svr_handle[in] 与vrb服务器相关的句柄
 *  @param data [in] 数据缓冲区指针
 *  @param len [in] 数据长度
 *  @param group_name [in] 分组名，想使用默认分组时，该值为NULL或者空字符串即可
 *  @param url [out] 唯一标识该图片的url
 *  @param msg_fun_name [in] 消息回调函数，不使用填NULL即可
 *  @param userdata [in] 回调函数使用的用户自定义数据,没有填NULL即可
 *  @return VRB_ERROR_CODE : 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_upload_pic(VRB_HANDLE svr_handle, const char* data, int len, const char* group_name, char url[VRB_MAX_PIC_URL_LEN],char pms_id[VRB_MAX_GUID_LEN], msg_fun msg_fun_name=0, void* userdata=0);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_download_pic( VRB_HANDLE svr_handle, const char* url, char** data, int *data_len, msg_fun msg_fun_name, void* userdata )
 *  @brief 下载图片
 *  @param svr_handle[in] 与vrb服务器相关的句柄
 *  @param url[in] 图片的唯一标识符url
 *  @param data[out] 数据缓冲区，该资源需要由vs_free_buf函数释放
 *  @param data_len[out] 数据的长度
 *  @param msg_fun_name[in] 消息回调函数，不使用填NULL即可
 *  @param userdata[in] 回调函数使用的用户自定义数据,没有填NULL即可
 *  @return VRB_ERROR_CODE: 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_download_pic(VRB_HANDLE svr_handle, const char* url, char** data, int *data_len, msg_fun msg_fun_name=0, void* userdata=0);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_delete_pic( VRB_HANDLE svr_handle, const char* url )
 *  @brief 删除服务器上的图片数据
 *  @param svr_handle[in] 与vrb服务器相关的句柄
 *  @param url[in] 图片的唯一标识符url
 *  @return VRB_ERROR_CODE :成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_delete_pic(VRB_HANDLE svr_handle, const char* url);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_pic_group( VRB_HANDLE svr_handle, char group[VRB_MAX_GROUP_NUM][VRB_MAX_GROUP_LEN], int *group_num )
 *  @brief 获取VRB的存储配置里的分组名
 *  @param svr_handle [in] 与vrb服务器相关的句柄
 *  @param group [out] 存储分组名的二维数组
 *  @param group_num [out] 分组名的数量
 *  @return VRB_ERROR_CODE : 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_pic_group(VRB_HANDLE svr_handle, char group[VRB_MAX_GROUP_NUM][VRB_MAX_GROUP_LEN], int *group_num);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_disk_status( VRB_HANDLE svr_handle, char normal_disk[VRB_MAX_DISK_NUM][VRB_MAX_DISK_LEN], 
                                                     int *normal_disk_num , char bad_disk[VRB_MAX_DISK_NUM][VRB_MAX_DISK_LEN], int *bad_disk_num )
 *  @brief 获取配置存储图片的磁盘的可写状态
 *  @param svr_handle [in] 与vrb服务器相关的句柄
 *  @param normal_disk [out] 存储正常的磁盘分区名的二维数组
 *  @param normal_disk_num [out] 正常的磁盘分区的数量
 *  @param bad_disk [out] 存储异常的磁盘分区名的二维数组
 *  @param bad_disk_num [out] 异常的磁盘分区的数量
 *  @return VRB_ERROR_CODE : 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_disk_status(VRB_HANDLE svr_handle, char normal_disk[VRB_MAX_DISK_NUM][VRB_MAX_DISK_LEN], int *normal_disk_num,
																													char     bad_disk[VRB_MAX_DISK_NUM][VRB_MAX_DISK_LEN], int *bad_disk_num);

/****************************/
///<VRB以文件形式存储图片的相关函数，取图片时需要知道文件的绝对路径
/****************************/

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_upload_file( VRB_HANDLE svr_handle, const char* data, int len, const char* group_name, const char* full_path, msg_fun msg_fun_name=0, void* userdata=0 )
 *  @brief 以文件形式上传图片到VRB上，在vrb中该形式上传的图片存储模式不同，要比以图片形式上传的图片低很多
 *  @brief 适用场合:上传很多图片，但是只需要最近的一张照片的场景
 *  @param svr_handle [in] 与vrb服务器相关的句柄
 *  @param data [in] 数据缓冲区指针
 *  @param len [in] 数据长度
 *  @param group_name [in] 分组名，想使用默认分组时，该值为NULL即可
 *  @param full_path [in] 图片存储的路径，为linux格式
 *  @param msg_fun_name [in] 消息回调函数，不使用填NULL即可
 *  @param userdata [in] 回调函数使用的用户自定义数据,没有填NULL即可
 *  @return VRB_ERROR_CODE : 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_upload_file(VRB_HANDLE svr_handle, const char* data, int len, const char* group_name, const char* full_path, msg_fun msg_fun_name=0, void* userdata=0);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_download_file( VRB_HANDLE svr_handle, const char* full_path, char** data, int *data_len, msg_fun msg_fun_name=0, void* userdata=0 )
 *  @brief 下载以文件形式上传的图片
 *  @param svr_handle [in] 与vrb服务器相关的句柄
 *  @param full_path [in] 图片在服务器上的绝对路径
 *  @param data [out] 数据缓冲区指针, 该资源需要由vs_free_buf函数释放
 *  @param data_len [out] 数据长度
 *  @param msg_fun_name [in] 消息回调函数，不使用填NULL即可
 *  @param userdata [in] 回调函数使用的用户自定义数据,没有填NULL即可
 *  @return VRB_ERROR_CODE : 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_download_file(VRB_HANDLE svr_handle, const char* full_path, char** data, int *data_len, msg_fun msg_fun_name=0, void* userdata=0);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_delete_file( VRB_HANDLE svr_handle, const char* full_path )
 *  @brief 删除以文件形式上传的图片
 *  @param svr_handle [in] 与vrb服务器相关的句柄
 *  @param full_path [in] 图片在服务器上的绝对路径,为linux格式的路径
 *  @return VS_API VRB_ERROR_CODE: 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_delete_file(VRB_HANDLE svr_handle, const char* full_path);

/** @fn  VS_API int VS_CALLBACK vs_free_buf(char** buf)
*  @brief 释放缓冲区资源
*  @param buf[in] 函数vs_download_file、vs_download_pic、vs_read_file函数返回的资源
*  @return VRB_ERROR_CODE: 
*/
VS_API VRB_ERROR_CODE VS_CALLBACK vs_free_buf(char** buf);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_check_svr( bool is_check )
 *  @brief 是否校验连接的服务器为图片服务器，主要防止出现其他服务器IP和端口与图片服务器相同的情况。
 *  @brief 只有2012-11-16以后的版本支持校验。不调用该函数时，将默认为不校验。
 *  @param is_check [in] true校验；false不校验
 *  @return VRB_ERROR_CODE: 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_check_svr(bool is_check);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_pms( VRB_HANDLE svr_handle,char* pms_id,DispathSvrInfo* svr_info )
 *  @brief 获取图片服务器的相关信息
 *  @param svr_handle [in] 与vrb服务器相关的句柄
 *  @param pms_id [in] 图片服务器的标识符，上传图片时会获得该ID
 *  @param svr_info [in] 图片服务器的信息
 *  @return VRB_ERROR_CODE : 成功EC_OK；其他为错误码
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_pms(VRB_HANDLE svr_handle,char* pms_id,DispathSvrInfo* svr_info);

#ifdef __cplusplus //定义c++命名规则
}
#endif
#endif // VRBSDK_h__
