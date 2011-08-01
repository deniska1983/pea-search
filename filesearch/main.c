#include "env.h"
#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "util.h"
#include "ntfs.h"
#include "fat.h"
#include "drive.h"
#include "search.h"
#include "write.h"
#include "suffix.h"
#include "fs_common.h"
#include "drive_change.h"
#include "chinese.h"
#include "serverNP.h"
//TODO: log�⡢�Զ�������win64��ֲ��linux��ֲ��langchy�����������ȫ�ļ������ʼ�����
//TODO: �����ļ����������壬���ݿ����ʱ�첽���¡��ļ�ϵͳ���Ӵ����Ŵ�
//TODO: ֧��ѹ���ļ������̾����е��ļ���ѯ
//TODO: ����windowsϵͳ���ò鿴����ֵ
//TODO: �ļ�����Դ����������״���


BOOL read_build_check(int i){
	BOOL flag = load_db(i);
	if(!flag) return 0;
	build_dir(i);
	FilesIterate(g_rootVols[i],check_file_entry,&flag);
	return 1;
}

void after_build(int i){
	FilesIterate(g_rootVols[i],FileRemoveFilter,NULL);
	FilesIterate(g_rootVols[i],SuffixProcess,NULL);
}

void load_online_db(int i){
	//if(i!=2) return;
	if(IsNtfs(i)){
		OpenNtfsHandle(i);
		InitVolumeData(i);
		initUSN(i);
	}
	if(read_build_check(i)){
		after_build(i);
		g_loaded[i]=1;
		//TODO: ���;����¼�֪ͨ
	}
}

void scan(int i){
	if(g_loaded[i]) return;
	resetMap(i);
	if(IsNtfs(i)){
		ScanMFT(i);
		add2Map(genRootFileEntry(i), i);
		build_dir(i);
		{
			HANDLE h = CreateThread(NULL,0,init_size_time_all,g_rootVols[i],0,0);
			SetThreadPriority(h,THREAD_PRIORITY_BELOW_NORMAL);
			ResumeThread(h);
			CloseHandle(h);
		}
		after_build(i);
	}else{
		scanRoot(genRootFileEntry(i),i);
		after_build(i);
		save_db(i);
	}
	g_loaded[i]=1;
	printf("Scan drive %c finished.\n",i+'A');
}

void DriveChangeListener(int i, BOOL add){
	if(add){
		printf(" new drive %c \n",i+'A');
		InitDrive(i);
		load_online_db(i);
		scan(i);
	}else{
		printf(" remove drive %c \n",i+'A');
		StopMonitorThread(i);
		CloseVolumeHandle(i);
		g_bVols[i]=0;
	}
}

DWORD WINAPI  ScanAll(PVOID pParam){
	NtfsDrivesIterator(scan);
	FatDrivesIterator(scan);
	StartDriveChangeMonitorThread(DriveChangeListener);
	ValidFixDrivesIterator(StartMonitorThread);
	return 0;
}

extern void breakpad_init();

BOOL gigaso_init(){
	breakpad_init();
	init_chinese();
	setlocale (LC_ALL, "");
	my_assert(24 == sizeof(FileEntry), 0);
	my_assert(WORD_SIZE == sizeof(void *), 0);
	InitDrives();
	//DrivesIterator(PrintDriveDetails);
	ValidDrivesIterator(load_online_db);
	CreateThread(NULL,0,ScanAll,NULL,0,0);
	return 1;
}

BOOL gigaso_destory(){
	save_db_all();
	ValidFixDrivesIterator(StopMonitorThread);
	StopDriveChangeMonitorThread();
	ValidDrivesIterator(CloseVolumeHandle);
	return 1;
}

static void print_all_stat(WCHAR *str){
	char buffer[1024];
	print_stat(stat(str,NULL),buffer);
	printf("%s\n",buffer);
}

