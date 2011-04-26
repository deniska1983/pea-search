#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_FAT_H_
#define FILE_SEARCH_FAT_H_

#include "env.h"
#include "fs_common.h"

/**
 * ɨ��һ��������
 * @param root ������
 */
extern int scanRoot(pFileEntry root, int i);

/**
 * ��һ������������Ա�����ļ��䶯
 * @param i ���������
 */
extern void OpenFatHandle(int i);

/**
 * ����FAT�ļ�ϵͳ�䶯�����̡߳����߳�ֻ�ܱ�����һ�Ρ�
 * @param i ���������
 */
extern BOOL StartMonitorThreadFAT(int i);

#endif  // FILE_SEARCH_FAT_H_

#ifdef __cplusplus
}
#endif
