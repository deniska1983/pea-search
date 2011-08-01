#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_GLOBAL_H_
#define FILE_SEARCH_GLOBAL_H_

#include "env.h"
#include <windows.h>
#include "drive.h"
#include "ntfs.h"

#define DIRVE_COUNT 26
#define DIRVE_COUNT_OFFLINE DIRVE_COUNT*3

extern UTF8 rootNames[26][3];//��������������

extern BOOL		g_bVols[];//��Ӧ�������Ƿ����
extern BOOL		g_loaded[];//��Ӧ�������Ĵ������ݿ��Ƿ��Ѽ���
extern BOOL		g_expires[];//��Ӧ�������Ĵ������ݿ��Ƿ��ѹ���
extern DriveInfo	g_VolsInfo[]; //����������Ϣ
extern HANDLE      g_hVols[];//����A~Z�Ķ�Ӧ�ľ���

extern pFileEntry g_rootVols[];//�������������FileEntry�ṹ

extern USN         g_curFirstUSN[];
extern USN         g_curNextUSN[];
extern DWORDLONG   g_curJournalID[];
extern HANDLE      g_hThread[];//ÿ����һ�������߳�
extern DWORD       g_BytesPerCluster[];//ÿ���ֽ���
extern DWORD       g_FileRecSize[];//MFT�ļ���¼��С���ƺ���û���õ���
extern PBYTE       g_pOutBuffer[];//ÿ���̵��ļ����¼��ַ ��ʼʱ���� ����ʱ��

extern unsigned int ALL_FILE_COUNT; //��ǰ�����ļ�������

extern unsigned char FILE_SEARCH_MAJOR_VERSION ;
extern unsigned char FILE_SEARCH_MINOR_VERSION ;











#endif  // FILE_SEARCH_GLOBAL_H_

#ifdef __cplusplus
}
#endif
