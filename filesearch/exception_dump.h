#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_EXCEPTION_DUMP_H_
#define FILE_SEARCH_EXCEPTION_DUMP_H_

/**
* ��ʼ��breakpad
*/
extern void breakpad_init();

/**
* �����쳣������һ��dump
*/
extern BOOL request_dump();


#endif  // FILE_SEARCH_EXCEPTION_DUMP_H_

#ifdef __cplusplus
}
#endif