#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SEARCH_FS_COMMON_H_
#define FILE_SEARCH_FS_COMMON_H_

#include "env.h"

struct fileEntry{  //��ʾһ���ļ�
	KEY FileReferenceNumber;  //NTFS�ĵ�ǰ�ļ�FileReferenceNumber
	union {
		KEY ParentFileReferenceNumber;  //NTFS�ĸ�Ŀ¼�ļ�FileReferenceNumber
		struct fileEntry *parent; //��Ŀ¼
	} up;
	void *children; //���ļ��б�, pointer to std::vector<pFileEntry>
	union {
		unsigned int value;
		struct {
			unsigned char readonly:1; //�Ƿ�ֻ��
			unsigned char hidden:1; //�Ƿ�����
			unsigned char system:1; //�Ƿ�ϵͳ�ļ�
			unsigned char dir:1;    //�Ƿ���Ŀ¼
			unsigned char size1:4;  //size�ĸ�4λ
			unsigned char size2:8;  //size�ĵ�8λ
			FILE_NAME_LEN FileNameLength:8; //�ļ����ֽڳ���
			FILE_NAME_LEN StrLen:8; //�ļ������ַ�����
		} v;
	} us;
	union {
		unsigned int value;
		struct {
			unsigned char time1; //ʱ����ֽ�
			unsigned char time2; //ʱ�����ֽ�
			unsigned char time3; //ʱ����ֽ�
			unsigned char suffixType; //�ļ���׺����������
		} v;
	} ut;
    UTF8  FileName[2]; //�ļ�����������\0������C���Է����ַ�����Unicode����
};
typedef struct fileEntry FileEntry, *pFileEntry;

#define IsReadonly(pFileEntry) (pFileEntry->us.v.readonly==1)
#define IsHidden(pFileEntry) (pFileEntry->us.v.hidden==1)
#define IsSystem(pFileEntry) (pFileEntry->us.v.system==1)
#define IsDir(pFileEntry) (pFileEntry->us.v.dir==1)


#define FILE_ENTRY_SIZE_(name_len_bytes) (sizeof(FileEntry)+(name_len_bytes)-sizeof(int))
#define FILE_ENTRY_SIZE(file) FILE_ENTRY_SIZE_(file->us.v.FileNameLength)


#define NEW0_FILE(file,name_len_bytes) \
		pFileEntry file = (pFileEntry) malloc_safe(FILE_ENTRY_SIZE_(name_len_bytes)); \
		memset(file,0,FILE_ENTRY_SIZE_(name_len_bytes));

#define SET_ROOT_NAME(root,name) memcpy_s(root->FileName,2,name,2)

#define FERROR(file)  fprintf(stderr,"error: %s , line %d in '%s'\n",((file==NULL || file->FileName ==NULL)? "null":file->FileName), __LINE__, __FILE__);

/*
 * �õ����ļ����������̱��
 */
extern int getDrive(pFileEntry file);
/*
 * ��MultiByte�����ӡ���ļ����ļ���
 */
extern void PrintFilenameMB(pFileEntry file);
/*
 * ��ӡ���ļ���ȫ·��
 */

/*
 * ��ӡ���ļ�������
 */
extern void print_time(pFileEntry file);

#define is_readonly(x) x->FileAttributes&FILE_ATTRIBUTE_READONLY
#define is_hidden(x)  x->FileAttributes&FILE_ATTRIBUTE_HIDDEN
#define is_system(x)  x->FileAttributes&FILE_ATTRIBUTE_SYSTEM
#define is_dir(x)     x->FileAttributes&FILE_ATTRIBUTE_DIRECTORY

#define is_readonly_ffd(find_data) find_data->dwFileAttributes&FILE_ATTRIBUTE_READONLY
#define is_hidden_ffd(find_data)  find_data->dwFileAttributes&FILE_ATTRIBUTE_HIDDEN
#define is_system_ffd(find_data)  find_data->dwFileAttributes&FILE_ATTRIBUTE_SYSTEM
#define is_dir_ffd(find_data)     find_data->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY

extern MINUTE ConvertSystemTimeToMinute(SYSTEMTIME sysTime);

extern void ConvertMinuteToSystemTime(SYSTEMTIME *sysTime,IN MINUTE time32);

extern void SET_TIME(pFileEntry file, MINUTE time);
extern MINUTE GET_TIME(pFileEntry file);
extern FSIZE GET_SIZE(pFileEntry file);
extern void SET_SIZE(pFileEntry file, FSIZE size);

extern void print_full_path(pFileEntry file);

/**
 * �����ļ�ϵͳ�л�õ�ʱ��ת��ΪMINUTE��ֵ���ļ�
 */
extern void set_time(pFileEntry file, PFILETIME time);

/**
 * �������������ļ���pFileEntry�ṹ
 * @param i ���������
 */
extern pFileEntry genRootFileEntry(int i);
/**
 * ���ļ��ҵ��丸Ŀ¼�����ļ��б��У�����file��ʼ����
 * ע�⣺ֻ�г�ʼ����ʱ�򣬲���Ҫ�ṩpFileEntry�ṹ����������ţ���ʼ����ɺ�pFileEntry���������������Ϣ���������ҵ���Ŀ¼����
 * @param i ���������
 */
extern BOOL attachParent(pFileEntry file, int i);
/**
 * ��������Ŀ¼���˫��ָ������
 */
extern void addChildren(pFileEntry parent, pFileEntry file, int i);

extern pFileEntry findFile(KEY frn,KEY pfrn,int i);

/**
 * �ļ�ɾ��ʱ��ͬʱɾ����Ӧ���ڴ�ṹ
 */
extern void deleteFile(pFileEntry file);

/**
 * �����ļ�ϵͳ�䶯�����̡߳����߳�ֻ�ܱ�����һ�Ρ�
 * @param i ���������
 */
extern BOOL StartMonitorThread(int i);

/**
 * ֹͣ�ļ�ϵͳ�䶯�����̡߳�
 * @param i ���������
 */
extern BOOL StopMonitorThread(int i);

extern BOOL CloseVolumeHandle(int i);

/**
 * �����ļ���Keyֵ��Map���ҵ����ļ�
 * @param frn ����NTFS���ļ���FileReferenceNumber,����FAT��pFileEntry���ڴ��ֵַ
 * @param i ���������
 */
extern pFileEntry findDir(KEY frn,int i);

/**
 * ��ʼ��ʱ���ļ�����Map�С�
 */
extern void add2Map(pFileEntry file,int i);
/**
 * ��Map������գ����ڳ�ʼ��ʱ���Զ����˴�������ݿ��ļ�
 */
extern void resetMap(int i);

/**
 * ���ݸ�Ŀ¼KEYֵ����Ŀ¼����
 * @param i ���������
 */
extern void build_dir(int i);

/**
 * �ڵ����з���һ���ļ�
 * @param file �����ʵ��ļ�
 * @param data ��������
 */
typedef void (*pFileVisitor)(pFileEntry file, void *data);
typedef void (*pFileVisitor_p3)(pFileEntry file, WCHAR *full_name, int name_len, int i);
typedef BOOL (*pFileVisitorB)(pFileEntry file, void *data);

/**
 * ����һ��Ŀ¼�µ����е��ļ���ִ�и����ķ��ʺ���
 * @param file ��������Ŀ¼
 * @param visitor ���ʺ���
 * @param data ��������
 */
extern void SubDirIterate(pFileEntry dir, pFileVisitor visitor, void *data);
extern void SubDirIterate_p3(pFileEntry dir, pFileVisitor_p3 visitor, WCHAR *full_name, int name_len, int i);
extern pFileEntry SubDirIterateB(pFileEntry dir, pFileVisitorB visitor, void *data);
/**
 * �ݹ��������һ��Ŀ¼�Լ���Ŀ¼�µ����е��ļ���ִ�и����ķ��ʺ���
 * @param file ��������Ŀ¼
 * @param visitor ���ʺ���
 * @param data ��������
 */
extern void FilesIterate(pFileEntry file,pFileVisitor visitor, void *data);
/**
 * �ݹ�������ʵ�ǰ�ļ�ϵͳ�������ļ���ִ�и����ķ��ʺ�����
 * @param visitor ���ʺ���
 * @param data ��������
 */
extern void AllFilesIterate(pFileVisitor visitor, void *data);

extern void FileRemoveFilter(pFileEntry file, void *data);

extern BOOL check_file_entry(pFileEntry file, void *data);

#endif  // FILE_SEARCH_FS_COMMON_H_

#ifdef __cplusplus
}
#endif
