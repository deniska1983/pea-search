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

#if !defined(_WIN32_WINNT) || _WIN32_WINNT< 0x0500
#define _WIN32_WINNT 0x0500
#endif

#pragma warning(disable:4996)

//#define USE_ZIP

#define MY_DEBUG

#define WORD_SIZE 4

#include <windows.h>

typedef unsigned int KEY; //NTFS文件的FileReferenceNumber类型，唯一标识一个文件。
typedef unsigned char FILE_NAME_LEN; //文件名长度类型
typedef unsigned int MINUTE; //以分钟表示的时间类型
typedef unsigned short FSIZE; //文件大小类型
typedef unsigned char UTF8, *pUTF8; //UTF8类型的字符串


//排序方式常量定义
#define NO_ORDER 0
#define NAME_ORDER_ASC 1
#define NAME_ORDER_DESC 2
#define PATH_ORDER_ASC 3
#define PATH_ORDER_DESC 4
#define SIZE_ORDER_ASC 5
#define SIZE_ORDER_DESC 6
#define DATE_ORDER_ASC 7
#define DATE_ORDER_DESC 8

struct searchEnv{ //搜索的环境配置
	unsigned char order; //排序方式，缺省按名称排序
	BOOL case_sensitive; //是否大小写敏感，缺省不敏感
	unsigned char file_type;//指定搜索的类型
	BOOL offline; //查询offline文件还是online文件
	int path_len; //如果指定了搜索的路径，该路径名的字符长度
	WCHAR path_name[MAX_PATH]; ////指定搜索的路径
};
typedef struct searchEnv SearchEnv, *pSearchEnv;

#define SearchWindowTitle L"记佳搜索 -- 最好的文件搜索软件"
#define SearchWindowClass L"Gigaso_Search"

#endif  // FILE_SEARCH_ENV_H_

#ifdef __cplusplus
}
#endif
