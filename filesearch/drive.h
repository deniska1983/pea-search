#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_DRIVE_H_
#define FILE_SEARCH_DRIVE_H_

#include "env.h"
#include <windows.h>

/**
 * �Ƿ��ǹ̶���������
 * @param i ���������
 */
extern BOOL is_fix_drive(int i);
/**
 * �Ƿ��ǹ��̵�������
 * @param i ���������
 */
extern BOOL is_cdrom_drive(int i);
/**
 * �Ƿ��ǿ��ƶ���������
 * @param i ���������
 */
extern BOOL is_removable_drive(int i);

struct driveInfo{
	UINT type;  // Determines whether a disk drive is a removable, fixed, CD-ROM, RAM disk, or network drive.
	DWORD serialNumber;  //the volume serial number.
	WCHAR volumeName[32];  //A pointer to a buffer that receives the name of a specified volume. The maximum buffer size is MAX_PATH+1.
	WCHAR fsName[8];  //the name of the file system, for example, the FAT file system or the NTFS file system
};
typedef struct driveInfo DriveInfo, *pDriveInfo;

/**
 * ��ʼ��������Ч���������������������Ƿ���Ч�����������ͺ����кŵ���Ϣ��
 */
extern void InitDrives();

/**
 * ��ʼ��������������
 * @param i ���������
 */
extern void InitDrive(int i);

/**
 * ���ʸ�����������
 * @param i  ���������
 */
typedef void (*pDriveVisitor)(int i);

/**
 * �������д��ڵ���������û�в�����̵Ĺ���Ҳ�Ǵ��ڵ���������
 */
extern void DrivesIterator(pDriveVisitor);

/**
 * ����������Ч����������û�в�����̵Ĺ���������Ч����������
 */
extern void ValidDrivesIterator(pDriveVisitor);

/**
 * �������������Ƿ���NTFS���͵�
 * @param i  ���������
 */
extern BOOL IsNtfs(int i);

/**
 * ����������Ч��NTFS���͵���������
 */
extern void NtfsDrivesIterator(pDriveVisitor);
extern void FatDrivesIterator(pDriveVisitor);

/**
 * ��ӡ����������������ϸ��Ϣ
 * @param i  ���������
 */
extern void PrintDriveDetails(int);

#endif  // FILE_SEARCH_DRIVE_H_

#ifdef __cplusplus
}
#endif
