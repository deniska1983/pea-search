#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_WRITE_H_
#define FILE_SEARCH_WRITE_H_

#include "fs_common.h"

/**
 * �������������������ļ���Ϣд��Ӳ��
 * @param i ���������
 */
extern BOOL save_db(int i);

/**
 * ����ǰ�������ļ���Ϣд��Ӳ��
 */
extern void save_db_all();

/**
 * ��Ӳ���ж�ȡ�������������ļ����ݿ�
 * @param i ���������
 */
extern BOOL load_db(int i);

extern int load_offline_dbs();

#endif  // FILE_SEARCH_WRITE_H_

#ifdef __cplusplus
}
#endif