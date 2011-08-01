#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_WIN_ICON_H_
#define FILE_SEARCH_WIN_ICON_H_

#include "env.h"


/**
* �����ļ�szFileName�����͵õ����ļ���SHIL_EXTRALARGE���͵�ͼ�꣬�����浽�ļ�iconFileName�С�
*/
extern void gen_icon_xlarge(LPCTSTR szFileName, LPCTSTR iconFileName);

/**
* �����ļ�szFileName�����͵õ����ļ���16*16Сͼ�꣬�����浽�ļ�iconFileName�С�
*/
extern BOOL gen_icon_small(LPCTSTR szFileName, LPCTSTR iconFileName);

/**
* ��HICON���浽ICO��ʽ�ļ�iconFileName�С�
*/
extern void saveicon(HICON hico, LPCTSTR iconFileName, BOOL bAutoDelete);

/**
* ��HICON���浽ͼ���ļ�iconFileName�С�
*/
extern void save_icon_to_photo(HICON hico, LPCTSTR iconFileName);


#endif  // FILE_SEARCH_WIN_ICON_H_

#ifdef __cplusplus
}
#endif
