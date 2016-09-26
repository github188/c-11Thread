/** @file   hlog1.h
 *  @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief  ���ǿ�ɽӿ�
 *          
 *  @note   create file
 *  @author wangjingyf@hikvision.com
 *  @date   2012/09/05 15:30:44
 *
 *  @change log
 *
 */
#ifndef __HLOG1_H__
#define __HLOG1_H__

#include "hlogconfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void (HLOG_API *HLOG_CB)(HLOG_LEVEL level, const char* message);

    /** @fn void hlog_init(const char* name, char async = false)
    *   @brief ���ݾɽӿڣ���ִ���κβ���
    */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async);
#endif

    /** @fn void hlog_ocx_init(const char* name, const char* path, char async = false)
    *   @brief ���ݾɽӿڣ���ִ���κβ���
    */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async);
#endif

    /** @fn void hlog_fini()
    *   @brief ���ݾɽӿڣ���ִ���κβ���
    */
    HLOG_DECLARE int HLOG_API hlog_fini();

    /** @fn void hlog_set_callback(HLOG_CB callback)
    *   @brief ������־�Ļص�����
    *   @param callback ���ڴ�����־��Ϣ�Ļص�����
    */
    HLOG_DECLARE int HLOG_API hlog_set_callback(HLOG_CB callback);

    /** @fn void hlog_level(HLOG_LEVEL level)
    *   @brief ���ݾɽӿڣ���ִ���κβ���
    */
    HLOG_DECLARE int HLOG_API hlog_level(HLOG_LEVEL level);

    /** @fn void hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...)
    *   @brief д��־��ʽ������
    *   @param level ��־����
    *   @param module ��־ģ��
    *   @param format ��־��ʽ���ַ�������ӿɱ����
    *   @note hlog_format�����hlog_set_callback����Ļص�����
    */
    HLOG_DECLARE int HLOG_API hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...) LOG_CHECK_FMT(3, 4);

    /** @fn void hlog_message(HLOG_LEVEL level, const char* module, const char* message)
    *   @brief д��־�ַ���
    *   @param level ��־����
    *   @param module ��־ģ��
    *   @param message ��־�ַ���
    *   @note hlog_message�������hlog_set_callback����Ļص�����
    */
    HLOG_DECLARE int HLOG_API hlog_message(HLOG_LEVEL level, const char* module, const char* message);

    /*
    *   ����̹���һ�������ļ�ʱ�������־�ļ���������Ϊ�˹����һ�����ؼ��ϴ˽ӿ�
    *   ������������ӿڣ��������һ�����̣��������һ�������ļ�
    */
    HLOG_DECLARE void HLOG_API hlog_set_configfile_name(const char* config_file_name);

#ifdef __cplusplus
}
#endif

// ���Ǽ����ԣ�������log_printf_def��log_printf_dst
#if (defined _WIN32 || defined _WIN64)
#define log_printf_def(level, format, ...)      hlog_format(level, "", format, ##__VA_ARGS__)
#else
#define log_printf_def(level, format, args...)  hlog_format(level, "", format, ##args)
#endif
#define log_printf_dst hlog_format

// for HPP module
#ifdef _WIN32
#define RCPU_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "RCPU", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define RCPU_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "RCPU", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define RCPU_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "RCPU", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define RCPU_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "RCPU", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define RCPU_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "RCPU", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)  
#define OPERATE_ERROR(fmt, ...)      hlog_format(HLOG_LEVEL_ERROR, "OPERATE", fmt"  [%s]", __FUNCTION__, ##__VA_ARGS__)  
#else
#define RCPU_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "RCPU", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define RCPU_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "RCPU", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define RCPU_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "RCPU", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define RCPU_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "RCPU", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define RCPU_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "RCPU", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#define LOG_ERROR         RCPU_ERROR
#define LOG_WARN          RCPU_WARN
#define LOG_INFO          RCPU_INFO
#define LOG_DEBUG         RCPU_DEBUG  
#define LOG_TRACE         RCPU_TRACE   

#endif
