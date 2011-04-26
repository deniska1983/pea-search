#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_SHARELIB_H_
#define FILE_SEARCH_SHARELIB_H_

#include <windows.h>

#ifndef SHARELIB_API
#define SHARELIB_API __declspec(dllimport)
#endif

typedef unsigned int KEY; //NTFS�ļ���FileReferenceNumber���ͣ�Ψһ��ʶһ���ļ���

typedef unsigned char FILE_NAME_LEN; //�ļ�����������

typedef unsigned int MINUTE; //�Է��ӱ�ʾ��ʱ������

typedef unsigned short FSIZE; //�ļ���С����

typedef unsigned char UTF8, *pUTF8; //UTF8���͵��ַ���

struct fileEntry{  //��ʾһ���ļ�
	KEY FileReferenceNumber;  //NTFS�ĵ�ǰ�ļ�FileReferenceNumber
	union {
		KEY ParentFileReferenceNumber;  //NTFS�ĸ�Ŀ¼�ļ�FileReferenceNumber
		struct fileEntry *parent; //��Ŀ¼
	} up;
	void *children; //���ļ��б�, pointer to std::vector<pFileEntry>
	union {
		unsigned int value;
		struct {
			unsigned char readonly:1; //�Ƿ�ֻ��
			unsigned char hidden:1; //�Ƿ�����
			unsigned char system:1; //�Ƿ�ϵͳ�ļ�
			unsigned char dir:1;    //�Ƿ���Ŀ¼
			unsigned char size1:4;  //size�ĸ�4λ
			unsigned char size2:8;  //size�ĵ�8λ
			FILE_NAME_LEN FileNameLength:8; //�ļ����ֽڳ���
			FILE_NAME_LEN StrLen:8; //�ļ������ַ�����
		} v;
	} us;
	union {
		unsigned int value;
		struct {
			unsigned char time1; //ʱ����ֽ�
			unsigned char time2; //ʱ�����ֽ�
			unsigned char time3; //ʱ����ֽ�
			unsigned char suffixType; //�ļ���׺����������
		} v;
	} ut;
    UTF8  FileName[2]; //�ļ�����������\0������C���Է����ַ�����Unicode����
};
typedef struct fileEntry FileEntry, *pFileEntry;

#define IsReadonly(pFileEntry) (pFileEntry->us.v.readonly==1)
#define IsHidden(pFileEntry) (pFileEntry->us.v.hidden==1)
#define IsSystem(pFileEntry) (pFileEntry->us.v.system==1)
#define IsDir(pFileEntry) (pFileEntry->us.v.dir==1)



SHARELIB_API extern MINUTE GET_TIME(pFileEntry file);
SHARELIB_API extern FSIZE GET_SIZE(pFileEntry file);

/**
 * ����ϵͳ�����л�õ��ļ���Сת��Ϊ�ڲ�����Ĵ�С
 */
SHARELIB_API extern FSIZE file_size_shorten(ULONGLONG size);

/**
 * �ļ�FSIZE�Ķ�����λ��byte\KB\MB\GB��,����λ����������ʾ
 */
SHARELIB_API extern int file_size_unit(FSIZE size);

/**
 * �ļ�FSIZE�Ĵ�С��0-1000֮��
 */
SHARELIB_API extern int file_size_amount(FSIZE size);

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
	WCHAR *path_name; ////ָ��������·��
};
typedef struct searchEnv SearchEnv, *pSearchEnv;

/**
 * ����һ���������ڶ��Ϸ���ռ�
 * type ��������
 * var  ����ָ����
 */
#define NEW(type,var) type *var = (type *)malloc_safe(sizeof(type))
/**
 * ����һ���������ڶ��Ϸ���ռ䣬ͬʱ�����ڴ��������㡣
 * type ��������
 * var  ����ָ����
 */
#define NEW0(type,var) NEW(type,var); memset(var,0,sizeof(type));

/**
 * �ڶ��Ϸ����СΪlen�Ŀռ�
 * @param len ��byte�������ڴ�ռ��С
 */
SHARELIB_API extern void * malloc_safe(size_t len);
SHARELIB_API extern void * realloc_safe(void *ptr, size_t len);
/**
 * �ͷ���malloc_safe����Ŀռ�
 * @param ptr ָ����ͷŵ��ڴ��ָ��
 */
SHARELIB_API extern void free_safe(void *ptr);

/**
* ���ݲ�ѯҪ���������з���Ҫ����ļ�
* @param str ��ѯ�����ַ���
* @param env �����Ļ�������
* @param result ���ص������ļ����б�ĵ�ַ
*/
SHARELIB_API extern DWORD search(WCHAR *str, pSearchEnv env,OUT pFileEntry **result);
/**
* �����ļ������ҵ���Ӧ��pFileEntry���Ǿ�ȷ·��ƥ�䣬֧�ֲ���ģ����ѯ��
* @param name �������ļ���ȫ·����
* @len ·������byte����
*/
SHARELIB_API extern pFileEntry find_file(WCHAR *name, int len);

SHARELIB_API extern void print_full_path(pFileEntry file);

SHARELIB_API extern BOOL gigaso_init();
SHARELIB_API extern BOOL gigaso_destory();

#endif  // FILE_SEARCH_SHARELIB_H_

#ifdef __cplusplus
}
#endif
