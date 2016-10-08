/*本人写的代码的所有错误定义都在该头文件, by lzn[2012-06-14]*/
#ifndef vrb_project_vrb_error_h__
#define vrb_project_vrb_error_h__

typedef int VRB_ERROR_CODE;		        ///<返回vrb的错误类型
#define VRB_MAX_ERROR_MSG_LEN  512  ///<VRB错误信息的最大长度

//定义error code (EC为“error code”的首字母缩写)
#define BASE_ERROR_CODE							80000										///<基础错误码
#define BASE_NET_ERROR_CODE                     (BASE_ERROR_CODE+1000)			///<网络错误的基础错误码 
#define EC_OK												0												///<操作成功
#define EC_ERROR										(-1)											///<操作失败

//基础错误类型
#define EC_INVALID_HANDLE							(BASE_ERROR_CODE + 1)				 ///<句柄无效
#define EC_NOT_FIND									(BASE_ERROR_CODE + 2)				 ///<找不到指定的信息
#define EC_INVALID_PARAM							(BASE_ERROR_CODE + 3)				///<无效参数
#define EC_NEW_FAIL									(BASE_ERROR_CODE + 4)				///<申请内存失败
#define EC_INIT_FAIL									(BASE_ERROR_CODE + 5)				///<初始化失败
#define EC_RECV_ERROR_MSG                        (BASE_ERROR_CODE + 6)				///<服务器端返回错误信息
#define EC_BUF_TOO_SMALL							(BASE_ERROR_CODE + 7)				///<缓冲区太小
#define EC_USER_STOP_OP							(BASE_ERROR_CODE + 8)				///<用户终止操作
#define EC_OPEN_FILE_FAIL							(BASE_ERROR_CODE + 9)				///<打开文件失败
#define EC_WRITE_FILE_FAIL							(BASE_ERROR_CODE + 10)				///<写文件失败
#define EC_READ_FILE_FAIL							(BASE_ERROR_CODE + 11)				///<读文件失败
#define EC_GET_FILESIZE_FAIL						(BASE_ERROR_CODE + 12)				///<获取文件长度失败
#define EC_FILE_EXIST									(BASE_ERROR_CODE + 13)				///<指定的文件已经存在
#define EC_CREATE_TIMER_FAIL 					(BASE_ERROR_CODE + 14)				///<创建timer失败
#define EC_NOT_VRB_SERVER 					    (BASE_ERROR_CODE + 15)				///<不是图片服务器
#define EC_NOT_ENOUGH_DATA                     (BASE_ERROR_CODE + 16)             ///<数据不足
#define EC_DLL_INIT_FAIL					           (BASE_ERROR_CODE + 17)		 ///<DLL库初始化失败
#define EC_MEM_NOT_ENOUGH					(BASE_ERROR_CODE + 18)		        ///<内存不够
#define EC_GET_DYN_PMS_FAIL                     (BASE_ERROR_CODE + 19)             ///<动态PMS调度失败
#define EC_GET_GUID_FAIL                      (BASE_ERROR_CODE + 20)			   ///< URL错误，获取GUID失败
#define EC_GET_PMS_BY_GUID                     (BASE_ERROR_CODE + 21)             ///< 根据GUID获取PMS失败,可能是由于调度服务器、图片服务器不在线
#define EC_NOT_SUPPORT                             (BASE_ERROR_CODE + 22)             ///<不支持

//网络错误类型
#define EC_NET_CONNECT_TIMEOUT				(BASE_NET_ERROR_CODE + 0)		///<连接超时
#define EC_NET_CONNECT_FAIL						(BASE_NET_ERROR_CODE + 1)		///<连接失败
#define EC_NET_CREATE_SOCK_FAIL				(BASE_NET_ERROR_CODE + 2)		///<创建sock失败
#define EC_NET_SEND_FAIL							(BASE_NET_ERROR_CODE + 3)		///<发送失败
#define EC_NET_RECV_TIMEOUT						(BASE_NET_ERROR_CODE + 4)		///<接收数据超时

////异常告警的错误码
//错误等级代码；数值越高，错误越严重
#define W_LVL_NORMAL                      1         ///<正常等级，主要报告一些提示性的东西
#define W_LVL_WARN                         2         ///<正常等级，主要报告一些提示性的东西
#define W_LVL_INFO                          3         ///<正常等级，主要报告一些提示性的东西
#define W_LVL_ERROR                        4         ///<正常等级，主要报告一些提示性的东西

//具体的消息错误码定义
#define BASE_WARN_ERROR_CODE            0          ///<异常告警的基础错误码
#define W_SVR_INIT_SUCC                                    (BASE_WARN_ERROR_CODE + 1)     ///<服务器启动成功
#define W_SVR_INIT_FAIL                                     (BASE_WARN_ERROR_CODE + 2)     ///<服务器启动失败
#define W_SVR_EXIT                                            (BASE_WARN_ERROR_CODE + 3)     ///<服务器退出
#define W_SVR_RESTART                                      (BASE_WARN_ERROR_CODE + 4)     ///<服务器正在重启
#define W_DISK_WRITE_FAIL                                 (BASE_WARN_ERROR_CODE + 5)     ///<磁盘不可写(会说明是哪个磁盘，以及不可写的原因)
#define W_FS_ERROR                                           (BASE_WARN_ERROR_CODE + 6)     ///<文件系统损坏(会说明是哪个磁盘，以及损坏的原因)
#define W_FS_RECOVER                                        (BASE_WARN_ERROR_CODE + 7)     ///<损坏的文件系统恢复成功
#define W_FS_RECOVER_FAIL                                 (BASE_WARN_ERROR_CODE + 8)     ///<损坏的文件系统恢复失败
#define W_RUN_OVER                                           (BASE_WARN_ERROR_CODE + 9)     ///<图片服务器压力过大
#define W_NO_USEFUL_FILE                                   (BASE_WARN_ERROR_CODE + 10)     ///<图片服务器没有可用的文件(如没有配置磁盘、IP-SAN异常导致)
#define W_NOT_CREATE_GROUP                              (BASE_WARN_ERROR_CODE + 11)     ///<图片服务器没有创建分组，一般是没有配置磁盘所致
#define W_GROUP_NO_DISK                                    (BASE_WARN_ERROR_CODE + 12)     ///<创建分组的分组没有配置磁盘
#define W_DISK_IN_MORE_DISK                               (BASE_WARN_ERROR_CODE + 13)     ///<一个磁盘分配给多个分组
#define W_FS_RECOVER_RUN                                  (BASE_WARN_ERROR_CODE + 14)     ///<文件系统正在修复中
#define W_MEM_NOT_ENOUGH                                (BASE_WARN_ERROR_CODE + 15)     ///<内存不够
#define W_CMS_MODULE_OFF                                 (BASE_WARN_ERROR_CODE + 16)    ///<CMS模块未设置启动
#define W_CLUSTER_MODULE_OFF                           (BASE_WARN_ERROR_CODE + 17)    ///<集群模块未设置启动
#define W_CLUSTER_PMS_OFFLINE                           (BASE_WARN_ERROR_CODE + 18)    ///<集群模块中PMS服务器离线
#define W_CLUSTER_PMS_NO_SPACE                       (BASE_WARN_ERROR_CODE + 19)    ///<集群模块中PMS服务器空间不足，70%节点没空间
#define W_FMT_BAD                                                 (BASE_WARN_ERROR_CODE + 20)    ///<盘损坏，需要修复后才能使用

#endif // vrb_project_vrb_error_h__
