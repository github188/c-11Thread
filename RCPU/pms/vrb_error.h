/*����д�Ĵ�������д����嶼�ڸ�ͷ�ļ�, by lzn[2012-06-14]*/
#ifndef vrb_project_vrb_error_h__
#define vrb_project_vrb_error_h__

typedef int VRB_ERROR_CODE;		        ///<����vrb�Ĵ�������
#define VRB_MAX_ERROR_MSG_LEN  512  ///<VRB������Ϣ����󳤶�

//����error code (ECΪ��error code��������ĸ��д)
#define BASE_ERROR_CODE							80000										///<����������
#define BASE_NET_ERROR_CODE                     (BASE_ERROR_CODE+1000)			///<�������Ļ��������� 
#define EC_OK												0												///<�����ɹ�
#define EC_ERROR										(-1)											///<����ʧ��

//������������
#define EC_INVALID_HANDLE							(BASE_ERROR_CODE + 1)				 ///<�����Ч
#define EC_NOT_FIND									(BASE_ERROR_CODE + 2)				 ///<�Ҳ���ָ������Ϣ
#define EC_INVALID_PARAM							(BASE_ERROR_CODE + 3)				///<��Ч����
#define EC_NEW_FAIL									(BASE_ERROR_CODE + 4)				///<�����ڴ�ʧ��
#define EC_INIT_FAIL									(BASE_ERROR_CODE + 5)				///<��ʼ��ʧ��
#define EC_RECV_ERROR_MSG                        (BASE_ERROR_CODE + 6)				///<�������˷��ش�����Ϣ
#define EC_BUF_TOO_SMALL							(BASE_ERROR_CODE + 7)				///<������̫С
#define EC_USER_STOP_OP							(BASE_ERROR_CODE + 8)				///<�û���ֹ����
#define EC_OPEN_FILE_FAIL							(BASE_ERROR_CODE + 9)				///<���ļ�ʧ��
#define EC_WRITE_FILE_FAIL							(BASE_ERROR_CODE + 10)				///<д�ļ�ʧ��
#define EC_READ_FILE_FAIL							(BASE_ERROR_CODE + 11)				///<���ļ�ʧ��
#define EC_GET_FILESIZE_FAIL						(BASE_ERROR_CODE + 12)				///<��ȡ�ļ�����ʧ��
#define EC_FILE_EXIST									(BASE_ERROR_CODE + 13)				///<ָ�����ļ��Ѿ�����
#define EC_CREATE_TIMER_FAIL 					(BASE_ERROR_CODE + 14)				///<����timerʧ��
#define EC_NOT_VRB_SERVER 					    (BASE_ERROR_CODE + 15)				///<����ͼƬ������
#define EC_NOT_ENOUGH_DATA                     (BASE_ERROR_CODE + 16)             ///<���ݲ���
#define EC_DLL_INIT_FAIL					           (BASE_ERROR_CODE + 17)		 ///<DLL���ʼ��ʧ��
#define EC_MEM_NOT_ENOUGH					(BASE_ERROR_CODE + 18)		        ///<�ڴ治��
#define EC_GET_DYN_PMS_FAIL                     (BASE_ERROR_CODE + 19)             ///<��̬PMS����ʧ��
#define EC_GET_GUID_FAIL                      (BASE_ERROR_CODE + 20)			   ///< URL���󣬻�ȡGUIDʧ��
#define EC_GET_PMS_BY_GUID                     (BASE_ERROR_CODE + 21)             ///< ����GUID��ȡPMSʧ��,���������ڵ��ȷ�������ͼƬ������������
#define EC_NOT_SUPPORT                             (BASE_ERROR_CODE + 22)             ///<��֧��

//�����������
#define EC_NET_CONNECT_TIMEOUT				(BASE_NET_ERROR_CODE + 0)		///<���ӳ�ʱ
#define EC_NET_CONNECT_FAIL						(BASE_NET_ERROR_CODE + 1)		///<����ʧ��
#define EC_NET_CREATE_SOCK_FAIL				(BASE_NET_ERROR_CODE + 2)		///<����sockʧ��
#define EC_NET_SEND_FAIL							(BASE_NET_ERROR_CODE + 3)		///<����ʧ��
#define EC_NET_RECV_TIMEOUT						(BASE_NET_ERROR_CODE + 4)		///<�������ݳ�ʱ

////�쳣�澯�Ĵ�����
//����ȼ����룻��ֵԽ�ߣ�����Խ����
#define W_LVL_NORMAL                      1         ///<�����ȼ�����Ҫ����һЩ��ʾ�ԵĶ���
#define W_LVL_WARN                         2         ///<�����ȼ�����Ҫ����һЩ��ʾ�ԵĶ���
#define W_LVL_INFO                          3         ///<�����ȼ�����Ҫ����һЩ��ʾ�ԵĶ���
#define W_LVL_ERROR                        4         ///<�����ȼ�����Ҫ����һЩ��ʾ�ԵĶ���

//�������Ϣ�����붨��
#define BASE_WARN_ERROR_CODE            0          ///<�쳣�澯�Ļ���������
#define W_SVR_INIT_SUCC                                    (BASE_WARN_ERROR_CODE + 1)     ///<�����������ɹ�
#define W_SVR_INIT_FAIL                                     (BASE_WARN_ERROR_CODE + 2)     ///<����������ʧ��
#define W_SVR_EXIT                                            (BASE_WARN_ERROR_CODE + 3)     ///<�������˳�
#define W_SVR_RESTART                                      (BASE_WARN_ERROR_CODE + 4)     ///<��������������
#define W_DISK_WRITE_FAIL                                 (BASE_WARN_ERROR_CODE + 5)     ///<���̲���д(��˵�����ĸ����̣��Լ�����д��ԭ��)
#define W_FS_ERROR                                           (BASE_WARN_ERROR_CODE + 6)     ///<�ļ�ϵͳ��(��˵�����ĸ����̣��Լ��𻵵�ԭ��)
#define W_FS_RECOVER                                        (BASE_WARN_ERROR_CODE + 7)     ///<�𻵵��ļ�ϵͳ�ָ��ɹ�
#define W_FS_RECOVER_FAIL                                 (BASE_WARN_ERROR_CODE + 8)     ///<�𻵵��ļ�ϵͳ�ָ�ʧ��
#define W_RUN_OVER                                           (BASE_WARN_ERROR_CODE + 9)     ///<ͼƬ������ѹ������
#define W_NO_USEFUL_FILE                                   (BASE_WARN_ERROR_CODE + 10)     ///<ͼƬ������û�п��õ��ļ�(��û�����ô��̡�IP-SAN�쳣����)
#define W_NOT_CREATE_GROUP                              (BASE_WARN_ERROR_CODE + 11)     ///<ͼƬ������û�д������飬һ����û�����ô�������
#define W_GROUP_NO_DISK                                    (BASE_WARN_ERROR_CODE + 12)     ///<��������ķ���û�����ô���
#define W_DISK_IN_MORE_DISK                               (BASE_WARN_ERROR_CODE + 13)     ///<һ�����̷�����������
#define W_FS_RECOVER_RUN                                  (BASE_WARN_ERROR_CODE + 14)     ///<�ļ�ϵͳ�����޸���
#define W_MEM_NOT_ENOUGH                                (BASE_WARN_ERROR_CODE + 15)     ///<�ڴ治��
#define W_CMS_MODULE_OFF                                 (BASE_WARN_ERROR_CODE + 16)    ///<CMSģ��δ��������
#define W_CLUSTER_MODULE_OFF                           (BASE_WARN_ERROR_CODE + 17)    ///<��Ⱥģ��δ��������
#define W_CLUSTER_PMS_OFFLINE                           (BASE_WARN_ERROR_CODE + 18)    ///<��Ⱥģ����PMS����������
#define W_CLUSTER_PMS_NO_SPACE                       (BASE_WARN_ERROR_CODE + 19)    ///<��Ⱥģ����PMS�������ռ䲻�㣬70%�ڵ�û�ռ�
#define W_FMT_BAD                                                 (BASE_WARN_ERROR_CODE + 20)    ///<���𻵣���Ҫ�޸������ʹ��

#endif // vrb_project_vrb_error_h__
