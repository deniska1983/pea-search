#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_UTIL_H_
#define FILE_SEARCH_UTIL_H_

#include "env.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>

/**
 * ����windowsϵͳ���ô���
 */
#define WIN_ERROR fprintf(stderr,"error code : %d , line %d in '%s'\n",GetLastError(), __LINE__, __FILE__);
#define MEM_ERROR fprintf(stderr,"insufficient memory, line %d in '%s'\n", __LINE__, __FILE__);
#define CPP_ERROR fprintf(stderr,"c++ exception, line %d in '%s'\n", __LINE__, __FILE__);

/**
 * ����debugģʽ�µ���assert
 * @param exp ����Ϊ��ı��ʽ
 */
extern void assert_debug(int exp);

/**
 * ���̲��˳����Զ���assert
 * @param exp ����Ϊ��ı��ʽ
 * @param ret ������ֵ
 */
#define my_assert(exp,ret) \
	if(!(exp)){\
		fprintf(stderr,"error assert, line %d in '%s'\n",  __LINE__, __FILE__);\
		assert_debug(exp);\
		return ret;\
	}


/**
* ��������f���޲��޷���ֵ��ִ������ĺ�����
**/
extern int time_passed(void (*f)());
/**
* ��������f����һ��������ִ������ĺ�����
**/
extern int time_passed_p1(void (*f)(void *),void *);
/**
* ��������f����������������ִ������ĺ�����
**/
extern int time_passed_p2(void (*f)(void *,void *),void *,void *);
/**
* ��������f���з���ֵ��ִ������ĺ�����
**/
extern int time_passed_ret(int (*f)(),int *ret_data);


#define WCHAR_TO_UTF8_LEN(wstr, wstrlen) WideCharToMultiByte(CP_UTF8, 0, (wstr), (wstrlen), NULL, 0, NULL, NULL)

#define WCHAR_TO_UTF8(wstr, wstrlen, ustr, ustrlen) WideCharToMultiByte(CP_UTF8, 0, (wstr), (wstrlen), (ustr), (ustrlen), NULL, NULL)

extern pUTF8 wchar_to_utf8(const WCHAR *in, int insize, int *out_size);

extern WCHAR* utf8_to_wchar(const pUTF8 in, int insize, int *out_size);

//��������Ƴ���
#define BYTE_BIN(n) ( \
((0n%0100000000/010000000>0)<<7)| \
((0n%010000000 /01000000 >0)<<6)| \
((0n%01000000 /0100000 >0)<<5)| \
((0n%0100000   /010000   >0)<<4)| \
((0n%010000    /01000    >0)<<3)| \
((0n%01000     /0100     >0)<<2)| \
((0n%0100      /010      >0)<<1)| \
((0n%010       /01       >0)<<0))

#define WORD_BIN(n) ( \
(BYTE_BIN(0n/0100000000)<<8)|BYTE_BIN(0n%0100000000) \
)

#define DWORD_BIN(highword,lowword) ( \
(WORD_BIN(0highword)<<16)|WORD_BIN(0lowword) \
)


extern BOOL WindowsVersionOK (DWORD MajorVerRequired, DWORD MinorVerRequired);

#endif  // FILE_SEARCH_UTIL_H_

#ifdef __cplusplus
}
#endif
