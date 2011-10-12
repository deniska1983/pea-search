﻿#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_COMMON_H_
#define FILE_SEARCH_COMMON_H_

/**
 * 设置应用程序当前目录
 */
extern BOOL setPWD(char *lpModuleName);

/**
 * 根据相对路径文件名得到绝对路径名
 * @param name 相对于本模块的文件名
 * @param full_path 绝对路径名
 */
extern BOOL get_abs_path(const WCHAR *name, WCHAR full_path[]);

extern void print_debug(WCHAR *fmt, ...);

extern BOOL WindowsVersionOK();


extern void get_prop(const wchar_t  *key, wchar_t  *out, DWORD nSize);
extern void get_prop2(const wchar_t  *key, wchar_t  *out, DWORD nSize,const wchar_t  * deft);
extern void set_prop(const wchar_t  *key, wchar_t  *str);

extern int get_hotkey();
extern BOOL set_hotkey(int key);



extern BOOL get_os(wchar_t *osbuf);

extern BOOL get_cpu(wchar_t *cpubuf);

extern BOOL get_disk(wchar_t *diskbuf);

extern BOOL get_ver(wchar_t *verbuf);

extern BOOL get_user(wchar_t *userbuf);

extern BOOL is_admin(void);

extern BOOL passed_one_day(time_t last);

extern BOOL file_passed_one_day(char *filename);

#endif  // FILE_SEARCH_COMMON_H_

#ifdef __cplusplus
}
#endif
