#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_WIN_ICON_H_
#define FILE_SEARCH_WIN_ICON_H_

#include "env.h"

#define MAX_HISTORY 20

/**
* �����ļ�szFileName�����͵õ����ļ���SHIL_EXTRALARGE���͵�ͼ�꣬�����浽�ļ�iconFileName�С�
*/
extern void gen_icon_xlarge(LPCTSTR szFileName, LPCTSTR iconFileName);

/**
* �����ļ�szFileName�����͵õ����ļ���16*16Сͼ�꣬�����浽�ļ�iconFileName�С�
*/
extern void gen_icon_small(LPCTSTR szFileName, LPCTSTR iconFileName);

/**
* ��HICON���浽ICO��ʽ�ļ�iconFileName�С�
*/
extern void SaveIcon(HICON hico, LPCTSTR iconFileName, BOOL bAutoDelete);

/**
* ��HICON���浽BMP��ʽ�ļ�iconFileName�С�
*/
extern void SaveIconToBMP(HICON hico, LPCTSTR iconFileName);


#endif  // FILE_SEARCH_WIN_ICON_H_

#ifdef __cplusplus
}
#endif
