﻿#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_DESKTOP_H_
#define FILE_SEARCH_DESKTOP_H_

#include "env.h"
#include "fs_common.h"


/**
 * 扫描Shell命名空间，从根位置Desktop开始，并保存到文件中。
 */
extern pFileEntry scan_desktop();

extern pFileEntry get_desktop(wchar_t *user_name);

extern void put_desktop(wchar_t *user_name, pFileEntry desktop);

#endif  // FILE_SEARCH_DESKTOP_H_

#ifdef __cplusplus
}
#endif
