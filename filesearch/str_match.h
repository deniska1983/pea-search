#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_STR_MATCH_H_
#define FILE_SEARCH_STR_MATCH_H_

#include "env.h"
#include <windows.h>

#define ASIZE 256  //�ļ����ַ�����С
#define XSIZE 256  //��ѯ���ַ�����С

/**
 * ʹ��quick-search or KMP�㷨�ж�x�Ƿ���y���Ӵ�
 * @param x ģʽ��
 * @param m x�ĳ���
 * @param y ��ƥ�䴮
 * @param n y�ĳ���
 * @param case_sensitive �Ƿ��Сд����
 */
extern  BOOL SUBSTR(pUTF8 x, int m, pUTF8 y, int n, int preNext[], BOOL case_sensitive);
extern  void preProcessPattern(pUTF8 x, int m, int preNext[], BOOL case_sensitive);

extern void pre_bndm_hz_multi(pUTF8 x, int m, int *prestr);
extern int bndm_hz_multi(pUTF8 x, int m, pUTF8 y, int n, int *preNext);

/**
 * ʹ�ñ����㷨�ж�x�Ƿ���y���Ӵ�
 */
extern brute_force(pUTF8 x, int m, pUTF8 y, int n, BOOL case_sensitive);

/**
 * �ж�y�����Ƿ���������ĵ���x
 */
extern  BOOL word_match(pUTF8 x, int m, pUTF8 y, int n, BOOL case_sensitive);

/**
 * �ж�y�����Ƿ���x��ͷ
 */
extern BOOL begin_match(pUTF8 x, int m, pUTF8 y, int n, BOOL case_sensitive);
/**
 * �ж�y�����Ƿ���x��β
 */
extern BOOL end_match(pUTF8 x, int m, pUTF8 y, int n, BOOL case_sensitive);

#endif  // FILE_SEARCH_STR_MATCH_H_

#ifdef __cplusplus
}
#endif
