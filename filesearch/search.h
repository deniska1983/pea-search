#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_SEARCH_H_
#define FILE_SEARCH_SEARCH_H_

#include "env.h"
#include "fs_common.h"

//����ʽ��������
#define NO_ORDER 0
#define NAME_ORDER_ASC 1
#define NAME_ORDER_DESC 2
#define PATH_ORDER_ASC 3
#define PATH_ORDER_DESC 4
#define SIZE_ORDER_ASC 5
#define SIZE_ORDER_DESC 6
#define DATE_ORDER_ASC 7
#define DATE_ORDER_DESC 8

struct searchEnv{ //�����Ļ�������
	unsigned char order; //����ʽ��ȱʡ����������
	BOOL case_sensitive; //�Ƿ��Сд���У�ȱʡ������
	unsigned char file_type;//ָ������������
	int path_len; //���ָ����������·������·������byte����
	WCHAR path_name[MAX_PATH]; ////ָ��������·��
};
typedef struct searchEnv SearchEnv, *pSearchEnv;


/**
* ���ݲ�ѯҪ���������з���Ҫ����ļ�
* @param str ��ѯ�����ַ���
* @param env �����Ļ�������
* @param result ���ص������ļ����б�ĵ�ַ
*/
extern DWORD search(WCHAR *str, pSearchEnv env,OUT pFileEntry **result);
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
