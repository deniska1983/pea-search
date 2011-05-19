#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_SEARCH_H_
#define FILE_SEARCH_SEARCH_H_

#include "env.h"
#include "fs_common.h"


/**
* ���ݲ�ѯҪ���������з���Ҫ����ļ�
* @param str ��ѯ�����ַ���
* @param env �����Ļ�������
* @param result ���ص������ļ����б�ĵ�ַ
*/
extern DWORD search(WCHAR *str, pSearchEnv env,OUT pFileEntry **result);
extern void free_search(pFileEntry *p);

extern int * stat(WCHAR *str, pSearchEnv env);
extern int print_stat(int * stats, char *p);

/**
* �����ļ������ҵ���Ӧ��pFileEntry���Ǿ�ȷ·��ƥ�䣬֧�ֲ���ģ����ѯ��
* @param name �������ļ���ȫ·����
* @len ·������byte����
*/
extern pFileEntry find_file(WCHAR *name, int len);

#endif  // FILE_SEARCH_SEARCH_H_

#ifdef __cplusplus
}
#endif
