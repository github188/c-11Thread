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

//����export��������������
#ifdef __cplusplus //c++
extern "C" {
#endif

typedef int VRB_HANDLE;

enum CALLBACK_STATUS{ CONTINE_RUN = 1,  /*����ִ��*/
									STOP_RUN  /*��ִֹ��*/};

#pragma pack(4)
struct DispathSvrInfo
{
    int dispath_svr_port;                  ///<���ȷ������Ķ˿�
    char dispath_svr_ip[32];                 ///<���ȷ�������ip
};
#pragma pack()

/** @fn CALLBACK_STATUS VS_CALLBACK (msg_fun*)(void* userdata, int progress)
 *  @brief �ϴ���������ͼƬʱʹ�õ���Ϣ�ص�����
 *  @param userdata[in] �û��Զ��������
 *  @param progress[in] ִ�н���
 *  @return CALLBACK_STATUS : ����ִ��ָ��Ƿ���Ҫ����ִ��
 */
typedef CALLBACK_STATUS (VS_CALLBACK *msg_fun)(void* userdata, int progress);

#define VRB_MAX_GUID_LEN		64    ///<GUID�����
#define VRB_MAX_PIC_URL_LEN		256	///<ͼƬurl�������
#define VRB_MAX_GROUP_LEN		128	///<VRB�з���������󳤶�
#define VRB_MAX_GROUP_NUM		40		///<VRB�з��������������
#define VRB_MAX_DISK_LEN          64  ///<VRB�����õĴ洢���̵ĵ���󳤶�
#define VRB_MAX_DISK_NUM			40    ///<VRB�����õĴ洢���̵��������

#define  VRB_INVALID_HANLDE 0 ///<��Ч�ľ��ֵ

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_init(  )
 *  @brief ��ʼ������,�ڲ�������־ģ��ʱ����Ҫʹ�õ���log4cxx.properties����־�����ļ��������ǰĿ¼��û�и��ļ������ᵼ�³�ʼ��ʧ��
 *  @return VRB_ERROR_CODE : �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_init();

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_fini(  )
 *  @brief ����ʼ������
 *  @return VRB_ERROR_CODE : �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_fini();

/** @fn VS_API char* VS_CALLBACK vs_get_error_msg( VRB_ERROR_CODE error_id, char msg_bug[VRB_MAX_ERROR_MSG_LEN] )
 *  @brief ��ȡVRB��error id��Ӧ�Ĵ�������
 *  @param error_id [in] VRB���صģ��������򷵻صľ���Ч
 *  @param msg_buf [out] error id��Ӧ�Ĵ�������
 *  @return char* : msg_bug�ĵ�ַ��������á���ע�����᷵��NULL,����msg_bug==NULL��
 */
VS_API char* VS_CALLBACK vs_get_error_msg(VRB_ERROR_CODE error_id, char msg_buf[VRB_MAX_ERROR_MSG_LEN]);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_set_timeout( int recv_timeout, int send_timeout )
 *  @brief ���ó�ʱʱ�䣬�����øú�������ʹ��Ĭ�ϵĳ�ʱʱ��: 5��
 *  @param recv_timeout [in] ���ճ�ʱʱ�䣬��λms,ȡֵ��Χ�� 1 - 30*1000 ����
 *  @param send_timeout [in] ���ͳ�ʱʱ�䣬��λms,ȡֵ��Χ�� 1 - 30*1000 ����
 *  @return VRB_ERROR_CODE : �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_set_timeout(int recv_timeout, int send_timeout);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_conn_pms( const char* ip, int port, VRB_HANDLE* svr_handle )
 *  @brief ������ͼƬ������������صĶ�����ͼƬ��������صĺ�������Ҫʹ�øþ����������Ч���ڲ��Զ�ά�����ӡ�
 *  @param ip [in] vrb��ip
 *  @param port [in] vrb��http �˿�
 *  @param svr_handle [out] ��vrb��������صľ����
 *  @return VRB_ERROR_CODE : �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_conn_pms(const char* ip, int port, VRB_HANDLE* svr_handle);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_conn_clusters( DispathSvrInfo* dispath_svr_info, unsigned int elem_count, VRB_HANDLE* clusters_handle )
 *  @brief �������Ӽ�Ⱥ�Ķ��������뼯Ⱥ��صĺ�������Ҫʹ�øþ����������Ч���ڲ��Զ�ά������
 *  @param dispath_svr_info [in] ���ȷ���������Ϣ����
 *  @param elem_count [in] �����Ԫ������,���Ϊ20
 *  @param clusters_handle [out] ��Ⱥ�Ķ��������뼯Ⱥ��صĺ�������Ҫʹ�øþ��
 *  @return VRB_ERROR_CODE: �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_conn_clusters(DispathSvrInfo* dispath_svr_info, unsigned int elem_count, VRB_HANDLE* clusters_handle );

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_disconn( VRB_HANDLE svr_handle )
 *  @brief ������vs_conn_clusters��vs_conn_pms���صľ����Դ
 *  @param svr_handle [in] ��vs_conn_clusters��vs_conn_pms���صľ��
 *  @return VRB_ERROR_CODE : �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_disconn(VRB_HANDLE svr_handle);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_upload_pic( VRB_HANDLE svr_handle, const char* data, int len, const char* group_name, char url[URL_PIC_MAX_LEN], msg_fun msg_fun_name, void* userdata )
 *  @brief �ϴ�ͼƬ
 *  @param svr_handle[in] ��vrb��������صľ��
 *  @param data [in] ���ݻ�����ָ��
 *  @param len [in] ���ݳ���
 *  @param group_name [in] ����������ʹ��Ĭ�Ϸ���ʱ����ֵΪNULL���߿��ַ�������
 *  @param url [out] Ψһ��ʶ��ͼƬ��url
 *  @param msg_fun_name [in] ��Ϣ�ص���������ʹ����NULL����
 *  @param userdata [in] �ص�����ʹ�õ��û��Զ�������,û����NULL����
 *  @return VRB_ERROR_CODE : �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_upload_pic(VRB_HANDLE svr_handle, const char* data, int len, const char* group_name, char url[VRB_MAX_PIC_URL_LEN],char pms_id[VRB_MAX_GUID_LEN], msg_fun msg_fun_name=0, void* userdata=0);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_download_pic( VRB_HANDLE svr_handle, const char* url, char** data, int *data_len, msg_fun msg_fun_name, void* userdata )
 *  @brief ����ͼƬ
 *  @param svr_handle[in] ��vrb��������صľ��
 *  @param url[in] ͼƬ��Ψһ��ʶ��url
 *  @param data[out] ���ݻ�����������Դ��Ҫ��vs_free_buf�����ͷ�
 *  @param data_len[out] ���ݵĳ���
 *  @param msg_fun_name[in] ��Ϣ�ص���������ʹ����NULL����
 *  @param userdata[in] �ص�����ʹ�õ��û��Զ�������,û����NULL����
 *  @return VRB_ERROR_CODE: �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_download_pic(VRB_HANDLE svr_handle, const char* url, char** data, int *data_len, msg_fun msg_fun_name=0, void* userdata=0);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_delete_pic( VRB_HANDLE svr_handle, const char* url )
 *  @brief ɾ���������ϵ�ͼƬ����
 *  @param svr_handle[in] ��vrb��������صľ��
 *  @param url[in] ͼƬ��Ψһ��ʶ��url
 *  @return VRB_ERROR_CODE :�ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_delete_pic(VRB_HANDLE svr_handle, const char* url);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_pic_group( VRB_HANDLE svr_handle, char group[VRB_MAX_GROUP_NUM][VRB_MAX_GROUP_LEN], int *group_num )
 *  @brief ��ȡVRB�Ĵ洢������ķ�����
 *  @param svr_handle [in] ��vrb��������صľ��
 *  @param group [out] �洢�������Ķ�ά����
 *  @param group_num [out] ������������
 *  @return VRB_ERROR_CODE : �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_pic_group(VRB_HANDLE svr_handle, char group[VRB_MAX_GROUP_NUM][VRB_MAX_GROUP_LEN], int *group_num);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_disk_status( VRB_HANDLE svr_handle, char normal_disk[VRB_MAX_DISK_NUM][VRB_MAX_DISK_LEN], 
                                                     int *normal_disk_num , char bad_disk[VRB_MAX_DISK_NUM][VRB_MAX_DISK_LEN], int *bad_disk_num )
 *  @brief ��ȡ���ô洢ͼƬ�Ĵ��̵Ŀ�д״̬
 *  @param svr_handle [in] ��vrb��������صľ��
 *  @param normal_disk [out] �洢�����Ĵ��̷������Ķ�ά����
 *  @param normal_disk_num [out] �����Ĵ��̷���������
 *  @param bad_disk [out] �洢�쳣�Ĵ��̷������Ķ�ά����
 *  @param bad_disk_num [out] �쳣�Ĵ��̷���������
 *  @return VRB_ERROR_CODE : �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_disk_status(VRB_HANDLE svr_handle, char normal_disk[VRB_MAX_DISK_NUM][VRB_MAX_DISK_LEN], int *normal_disk_num,
																													char     bad_disk[VRB_MAX_DISK_NUM][VRB_MAX_DISK_LEN], int *bad_disk_num);

/****************************/
///<VRB���ļ���ʽ�洢ͼƬ����غ�����ȡͼƬʱ��Ҫ֪���ļ��ľ���·��
/****************************/

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_upload_file( VRB_HANDLE svr_handle, const char* data, int len, const char* group_name, const char* full_path, msg_fun msg_fun_name=0, void* userdata=0 )
 *  @brief ���ļ���ʽ�ϴ�ͼƬ��VRB�ϣ���vrb�и���ʽ�ϴ���ͼƬ�洢ģʽ��ͬ��Ҫ����ͼƬ��ʽ�ϴ���ͼƬ�ͺܶ�
 *  @brief ���ó���:�ϴ��ܶ�ͼƬ������ֻ��Ҫ�����һ����Ƭ�ĳ���
 *  @param svr_handle [in] ��vrb��������صľ��
 *  @param data [in] ���ݻ�����ָ��
 *  @param len [in] ���ݳ���
 *  @param group_name [in] ����������ʹ��Ĭ�Ϸ���ʱ����ֵΪNULL����
 *  @param full_path [in] ͼƬ�洢��·����Ϊlinux��ʽ
 *  @param msg_fun_name [in] ��Ϣ�ص���������ʹ����NULL����
 *  @param userdata [in] �ص�����ʹ�õ��û��Զ�������,û����NULL����
 *  @return VRB_ERROR_CODE : �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_upload_file(VRB_HANDLE svr_handle, const char* data, int len, const char* group_name, const char* full_path, msg_fun msg_fun_name=0, void* userdata=0);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_download_file( VRB_HANDLE svr_handle, const char* full_path, char** data, int *data_len, msg_fun msg_fun_name=0, void* userdata=0 )
 *  @brief �������ļ���ʽ�ϴ���ͼƬ
 *  @param svr_handle [in] ��vrb��������صľ��
 *  @param full_path [in] ͼƬ�ڷ������ϵľ���·��
 *  @param data [out] ���ݻ�����ָ��, ����Դ��Ҫ��vs_free_buf�����ͷ�
 *  @param data_len [out] ���ݳ���
 *  @param msg_fun_name [in] ��Ϣ�ص���������ʹ����NULL����
 *  @param userdata [in] �ص�����ʹ�õ��û��Զ�������,û����NULL����
 *  @return VRB_ERROR_CODE : �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_download_file(VRB_HANDLE svr_handle, const char* full_path, char** data, int *data_len, msg_fun msg_fun_name=0, void* userdata=0);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_delete_file( VRB_HANDLE svr_handle, const char* full_path )
 *  @brief ɾ�����ļ���ʽ�ϴ���ͼƬ
 *  @param svr_handle [in] ��vrb��������صľ��
 *  @param full_path [in] ͼƬ�ڷ������ϵľ���·��,Ϊlinux��ʽ��·��
 *  @return VS_API VRB_ERROR_CODE: �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_delete_file(VRB_HANDLE svr_handle, const char* full_path);

/** @fn  VS_API int VS_CALLBACK vs_free_buf(char** buf)
*  @brief �ͷŻ�������Դ
*  @param buf[in] ����vs_download_file��vs_download_pic��vs_read_file�������ص���Դ
*  @return VRB_ERROR_CODE: 
*/
VS_API VRB_ERROR_CODE VS_CALLBACK vs_free_buf(char** buf);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_check_svr( bool is_check )
 *  @brief �Ƿ�У�����ӵķ�����ΪͼƬ����������Ҫ��ֹ��������������IP�Ͷ˿���ͼƬ��������ͬ�������
 *  @brief ֻ��2012-11-16�Ժ�İ汾֧��У�顣�����øú���ʱ����Ĭ��Ϊ��У�顣
 *  @param is_check [in] trueУ�飻false��У��
 *  @return VRB_ERROR_CODE: �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_check_svr(bool is_check);

/** @fn VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_pms( VRB_HANDLE svr_handle,char* pms_id,DispathSvrInfo* svr_info )
 *  @brief ��ȡͼƬ�������������Ϣ
 *  @param svr_handle [in] ��vrb��������صľ��
 *  @param pms_id [in] ͼƬ�������ı�ʶ�����ϴ�ͼƬʱ���ø�ID
 *  @param svr_info [in] ͼƬ����������Ϣ
 *  @return VRB_ERROR_CODE : �ɹ�EC_OK������Ϊ������
 */
VS_API VRB_ERROR_CODE VS_CALLBACK vs_get_pms(VRB_HANDLE svr_handle,char* pms_id,DispathSvrInfo* svr_info);

#ifdef __cplusplus //����c++��������
}
#endif
#endif // VRBSDK_h__
