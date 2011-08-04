#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_HISTORY_H_
#define FILE_SEARCH_HISTORY_H_

#include "env.h"

#define VIEW_HISTORY 15  //ʵ����ʾ����ʷ�ļ���¼

extern void history_add(const wchar_t *file);

/**
index��1��ʼ
*/
extern void history_delete(int index);

extern void history_pin(int index);
extern void history_unpin(int index);

extern wchar_t *history_get(int index);

extern BOOL history_save();

extern BOOL history_load();

extern void init_from_recent();

typedef void (*pHistoryVisitor)(wchar_t *file, void *context);

extern void HistoryIterator(pHistoryVisitor, void *context);

extern int history_to_json(wchar_t *buffer);

#endif  // FILE_SEARCH_HISTORY_H_

#ifdef __cplusplus
}
#endif
