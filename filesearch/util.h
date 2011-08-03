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

/**
 * ��unicode������ַ���inת��Ϊutf-8������ַ���
 * @param insize_c��ʾThe number of Unicode (16-bit) characters in the string
 * @param out_size_b��ʾ��byteͳ�Ƶ��ַ�������
 * 
 */
extern pUTF8 wchar_to_utf8(const WCHAR *in, int insize_c, int *out_size_b);

extern WCHAR* utf8_to_wchar(const pUTF8 in, int insize_b, int *out_size_c);

extern wchar_t *wcsrchr_me(const wchar_t *S, int len, wchar_t C);

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
extern void * malloc_safe(size_t len);
extern void * realloc_safe(void *ptr, size_t len);
/**
 * �ͷ���malloc_safe����Ŀռ�
 * @param ptr ָ����ͷŵ��ڴ��ָ��
 */
extern void free_safe(void *ptr);


/**
 * ����ϵͳ�����л�õ��ļ���Сת��Ϊ�ڲ�����Ĵ�С
 */
extern FSIZE file_size_shorten(ULONGLONG size);

/**
 * �ļ�FSIZE�Ķ�����λ��byte\KB\MB\GB��,����λ����������ʾ
 */
extern int file_size_unit(FSIZE size);

/**
 * �ļ�FSIZE�Ĵ�С��0-1000֮��
 */
extern int file_size_amount(FSIZE size);


#endif  // FILE_SEARCH_UTIL_H_

#ifdef __cplusplus
}
#endif
