#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_DRIVE_CHANGE_H_
#define FILE_SEARCH_DRIVE_CHANGE_H_

#include "env.h"
#include <windows.h>

/**
 * �ɲ�δ��̱䶯������
 * @param drive �������
 * @param isadd �ǲ�����̻��ǰγ�����
 */
typedef void (*pDriveChangeListener)(int drive, BOOL isadd);


/**
 * �����ɲ�δ��̱䶯�����̡߳����߳�ֻ�ܱ�����һ�Ρ�
 * @param pDriveChangeListener �䶯������
 */
extern BOOL StartDriveChangeMonitorThread( pDriveChangeListener );

/**
 * ֹͣ�ɲ�δ��̱䶯�����߳�
 */
extern BOOL StopDriveChangeMonitorThread(void);


#endif  // FILE_SEARCH_DRIVE_CHANGE_H_

#ifdef __cplusplus
}
#endif