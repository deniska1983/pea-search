#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_HISTORY_H_
#define FILE_SEARCH_HISTORY_H_

#include "env.h"

#define VIEW_HISTORY 15  //��ҳ��ʾ����ʷ�ļ���¼
#define MAX_HISTORY 30  //��󱣴����ʷ�ļ���¼

/**
* ���ļ�file��ӵ���ʷ�ļ���¼�С����file����ҳ���Ѵ��ڣ����ظ���ӡ�
*/
extern void history_add(const wchar_t *file);

/**
* ɾ������indexλ�õ���ʷ�ļ���¼, ����һ��λ�õ���ʷ�ļ���¼���䵽��ɾ����λ��
*/
extern void history_delete(int index);

/**
* �̶�����indexλ�õ���ʷ�ļ���¼
*/
extern void history_pin(int index);
/**
* ȡ���̶�����indexλ�õ���ʷ�ļ���¼
*/
extern void history_unpin(int index);

/**
* ��ø���indexλ�õ���ʷ�ļ���¼
*/
extern wchar_t *history_get(int index);

/**
* ����ʷ�ļ���¼���浽����
*/
extern BOOL history_save();

/**
* �Ӵ����ļ��м�����ʷ�ļ���¼
*/
extern BOOL history_load();

/**
* ���ΰ�װʱ����windows��Recent�ļ��л�ȡ�����ĵ�����ʼ��
*/
extern void init_from_recent();

typedef void (*pHistoryVisitor)(wchar_t *file, int pin, void *context);

/**
* ������ҳ����ʷ�ļ���¼
*/
extern void HistoryIterator(pHistoryVisitor, void *context);

/**
* �������е���ʷ�ļ���¼
*/
extern void HistoryIteratorAll(pHistoryVisitor, void *context);

/**
* ������ʷ�ļ���¼��Ϣ����Ϊjson��ʽ
*/
extern int history_to_json(wchar_t *buffer);

#endif  // FILE_SEARCH_HISTORY_H_

#ifdef __cplusplus
}
#endif
