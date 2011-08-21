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
 * ��Ӳ���ж�ȡ�������������ļ����ݿ�
 * @param i ���������
 */
extern BOOL load_db(int i);


/**
 * �������е����ߵ�db�ļ�
 */
extern int load_offline_dbs();

extern void del_offline_db(int i);

/**
 * ���ʸ�����db�ļ�
 * @param db_name  db�ļ���
 * @return �Ƿ��������
 */
typedef BOOL (*pDbVisitor)(char *db_name, void *data);

/**
 * �������е�db�ļ���
 */
extern void DbIterator(pDbVisitor, void *data);


#endif  // FILE_SEARCH_WRITE_H_

#ifdef __cplusplus
}
#endif