#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_ENV_H_
#define FILE_SEARCH_ENV_H_

#ifdef _MSC_VER
  #define INLINE __forceinline /* use __forceinline (VC++ specific) */
#else
	#ifdef __GNUC__
		#define INLINE __inline__
	#else
		#define INLINE inline        /* use standard inline */
	#endif
#endif

#if !defined(_WIN32_WINNT) || _WIN32_WINNT< 0x0501
#define _WIN32_WINNT 0x0501
#endif

#pragma warning(disable:4996)

//#define USE_ZIP

#define MY_DEBUG

#include <windows.h>

#include "GIGASOConfig.h"

#ifdef HAVE_64_BIT
	typedef unsigned long KEY; //NTFS�ļ���FileReferenceNumber���ͣ�Ψһ��ʶһ���ļ���
#else
	typedef unsigned int KEY; //NTFS�ļ���FileReferenceNumber���ͣ�Ψһ��ʶһ���ļ���
#endif

typedef unsigned char FILE_NAME_LEN; //�ļ�����������
typedef unsigned int MINUTE; //�Է��ӱ�ʾ��ʱ������
typedef unsigned short FSIZE; //�ļ���С����
typedef unsigned char UTF8, *pUTF8; //UTF8���͵��ַ���


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
	BOOL offline; //��ѯoffline�ļ�����online�ļ�
	int path_len; //���ָ����������·������·�������ַ�����
	WCHAR path_name[MAX_PATH]; ////ָ��������·��
	WCHAR user_name[MAX_PATH]; ////ִ�������ĵ�ǰ�û���
};
typedef struct searchEnv SearchEnv, *pSearchEnv;

#define SearchWindowTitle L"�㶹���� -- ��õ��ļ��������"
#define SearchWindowClass L"PeaSearch"
#define ListenerWindowClass L"PeaSearch_Listener"

#define WM_SET_HOTKEY WM_USER+1


#define UPDATE_CHECH_FILE "gigaso_update"
#define UPDATE_CHECH_DONE -1
#define UPDATE_CHECH_UNKNOWN 0
#define UPDATE_CHECH_NEW 1

#endif  // FILE_SEARCH_ENV_H_

#ifdef __cplusplus
}
#endif
