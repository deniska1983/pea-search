#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_ENV_H_
#define FILE_SEARCH_ENV_H_

#if !defined(_WIN32_WINNT) || _WIN32_WINNT< 0x0500
#define _WIN32_WINNT 0x0500
#endif

#define UNICODE
#define _UNICODE

#pragma warning(disable:4996)

//#define USE_ZIP

#define MY_DEBUG

#define WORD_SIZE 4

#include <windows.h>

typedef unsigned int KEY; //NTFS�ļ���FileReferenceNumber���ͣ�Ψһ��ʶһ���ļ���
typedef unsigned char FILE_NAME_LEN; //�ļ�����������
typedef unsigned int MINUTE; //�Է��ӱ�ʾ��ʱ������
typedef unsigned short FSIZE; //�ļ���С����
typedef unsigned char UTF8, *pUTF8; //UTF8���͵��ַ���




#endif  // FILE_SEARCH_ENV_H_

#ifdef __cplusplus
}
#endif
