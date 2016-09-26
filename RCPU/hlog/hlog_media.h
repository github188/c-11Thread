/** @file   hlog1.h
 *  @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief  日智库旧接口
 *          
 *  @note   create file
 *  @author wangjingyf@hikvision.com
 *  @date   2012/09/05 15:30:44
 *
 *  @change log
 *
 */
#ifndef __HLOG_MEDIA_H__
#define __HLOG_MEDIA_H__

#include "hlogconfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void (HLOG_API *HLOG_CB)(HLOG_LEVEL level, const char* message);

    /** @fn void hlog_init(const char* name, char async = false)
    *   @brief 兼容旧接口，不执行任何操作
    */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async);
#endif

    /** @fn void hlog_ocx_init(const char* name, const char* path, char async = false)
    *   @brief 兼容旧接口，不执行任何操作
    */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async);
#endif

    /** @fn void hlog_fini()
    *   @brief 兼容旧接口，不执行任何操作
    */
    HLOG_DECLARE int HLOG_API hlog_fini();

    /** @fn void hlog_set_callback(HLOG_CB callback)
    *   @brief 设置日志的回调函数
    *   @param callback 用于处理日志信息的回调函数
    */
    HLOG_DECLARE int HLOG_API hlog_set_callback(HLOG_CB callback);

    /** @fn void hlog_level(HLOG_LEVEL level)
    *   @brief 兼容旧接口，不执行任何操作
    */
    HLOG_DECLARE int HLOG_API hlog_level(HLOG_LEVEL level);

    /** @fn void hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...)
    *   @brief 写日志格式化数据
    *   @param level 日志级别
    *   @param module 日志模块
    *   @param format 日志格式化字符串，后接可变参数
    *   @note hlog_format会调用hlog_set_callback传入的回调函数
    */
    HLOG_DECLARE int HLOG_API hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...) LOG_CHECK_FMT(3, 4);

    /** @fn void hlog_message(HLOG_LEVEL level, const char* module, const char* message)
    *   @brief 写日志字符串
    *   @param level 日志级别
    *   @param module 日志模块
    *   @param message 日志字符串
    *   @note hlog_message不会调用hlog_set_callback传入的回调函数
    */
    HLOG_DECLARE int HLOG_API hlog_message(HLOG_LEVEL level, const char* module, const char* message);

    /*
    *   多进程共享一个配置文件时会出现日志文件滚动错误，为了规避这一错误，特加上此接口
    *   不建议用这个接口，如果仅是一个进程，则最好用一个配置文件
    */
    HLOG_DECLARE void HLOG_API hlog_set_configfile_name(const char* config_file_name);

#ifdef __cplusplus
}
#endif

// 考虑兼容性，特增加log_printf_def和log_printf_dst
#if (defined _WIN32 || defined _WIN64)
#define log_printf_def(level, format, ...)      hlog_format(level, "", format, ##__VA_ARGS__)
#else
#define log_printf_def(level, format, args...)  hlog_format(level, "", format, ##args)
#endif
#define log_printf_dst hlog_format

// for HPP module
#ifdef _WIN32
#define MEDIA_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "MEDIA", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define MEDIA_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "MEDIA", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define MEDIA_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "MEDIA", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define MEDIA_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "MEDIA", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define MEDIA_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "MEDIA", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
#define MEDIA_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "MEDIA", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define MEDIA_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "MEDIA", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define MEDIA_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "MEDIA", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define MEDIA_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "MEDIA", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define MEDIA_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "MEDIA", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#define LOG_ERROR         MEDIA_ERROR
#define LOG_WARN          MEDIA_WARN
#define LOG_INFO          MEDIA_INFO
#define LOG_DEBUG         MEDIA_DEBUG  
#define LOG_TRACE         MEDIA_TRACE    

#endif
