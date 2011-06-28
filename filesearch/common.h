#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_COMMON_H_
#define FILE_SEARCH_COMMON_H_

/**
 * ����Ӧ�ó���ǰĿ¼
 */
extern BOOL setPWD();

/**
 * �������·���ļ����õ�����·����
 * @param name ����ڱ�ģ����ļ���
 * @param full_path ����·����
 */
extern BOOL get_abs_path(const WCHAR *name, WCHAR full_path[]);

extern BOOL WindowsVersionOK (DWORD MajorVerRequired, DWORD MinorVerRequired);


#endif  // FILE_SEARCH_COMMON_H_

#ifdef __cplusplus
}
#endif