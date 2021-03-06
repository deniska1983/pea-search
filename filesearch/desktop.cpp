﻿#include "env.h"
#include <stdio.h>
#include <string.h>
#include "suffix.h"
#include "search.h"
#include "global.h"
#include "util.h"
#include "fs_common.h"
#include "write.h"

#include <shlobj.h>
#include <shlwapi.h>
#include <iostream>

#include <google/sparse_hash_map>

static int depth=0;

enum FileType { LOCAL, NETWORK, VIRTUAL };

extern "C" {

static pFileEntry genDesktopFileEntry(){
	NEW0(FileEntry, ret);
	ret->FileReferenceNumber = ROOT_NUMBER;
	ret->up.ParentFileReferenceNumber = 0;
	ret->us.v.FileNameLength = 0;
	ret->us.v.StrLen = 0;
	ret->us.v.dir = 1;
	ret->ut.v.suffixType = SF_DIR;
	ret->up.parent = NULL;
	ret->children = NULL;
	return ret;
}
static pFileEntry initDesktopFile(WCHAR *name, pFileEntry parent,BOOL dir){
	int str_len = (int)wcslen(name);
	int len = wchar_to_utf8_len(name,str_len);
	NEW0_FILE(ret,len);
	ret->us.v.FileNameLength = len;
	ret->us.v.StrLen = str_len;
	wchar_to_utf8_nocheck(name,str_len,ret->FileName,len);
	if(dir){
		ret->ut.v.suffixType = SF_DIR;
		ret->us.v.dir = 1;
	}else{
		ret->ut.v.suffixType = SF_LNK;
	}
	ret->us.v.system = 1;
	addChildren(parent,ret);
	//set_time(ret, &pfd->ftLastWriteTime);
	SET_SIZE(ret,0);
	ALL_FILE_COUNT +=1;
	return ret;
}


static void get_name(IShellFolder *f, LPITEMIDLIST pidlItems, SHGDNF flag, WCHAR *name){
	STRRET strDispName;
	f->GetDisplayNameOf(pidlItems, flag, &strDispName);
	StrRetToBuf(&strDispName, pidlItems, name, MAX_PATH);
}

static FileType get_type(IShellFolder *f, LPITEMIDLIST pidlItems){
	STRRET strDispName;
	char pszDisplayName[MAX_PATH];
	f->GetDisplayNameOf(pidlItems, SHGDN_FORPARSING, &strDispName);
	StrRetToBufA(&strDispName, pidlItems, pszDisplayName, MAX_PATH);
#ifdef MY_DEBUG
	printf("%s\n",pszDisplayName);
#endif
	if( strncmp(pszDisplayName+1,":\\",2)==0 ) return LOCAL;
	if( strncmp(pszDisplayName,"\\\\",2)==0 ) return NETWORK;
	if( strncmp(pszDisplayName,"::",2)==0 ) return VIRTUAL;
	return VIRTUAL;
}

static BOOL isFolder(IShellFolder *f, LPITEMIDLIST pidlItems){
    SFGAOF uAttr = SFGAO_FOLDER;
    f->GetAttributesOf(1, (LPCITEMIDLIST *) &pidlItems, &uAttr);
	return uAttr & SFGAO_FOLDER;
}

static void scan_desktop0(IShellFolder *f, LPITEMIDLIST pidlComplete, pFileEntry dir){
	HRESULT hr;
	LPENUMIDLIST ppenum = NULL;
	LPITEMIDLIST pidlItems = NULL;
	ULONG celtFetched;
    hr = f->EnumObjects(NULL,SHCONTF_FOLDERS | SHCONTF_NONFOLDERS | SHCONTF_INCLUDEHIDDEN, &ppenum);
	if(hr!=S_OK) return;
    while( hr = ppenum->Next(1,&pidlItems, &celtFetched) == S_OK && (celtFetched) == 1){
		FileType ft = get_type(f,pidlItems);
		if(ft!=LOCAL){
			BOOL isDir = isFolder(f,pidlItems);
			WCHAR name[MAX_PATH];
			get_name(f,pidlItems,SHGDN_NORMAL,name);
			pFileEntry file = initDesktopFile(name,dir,isDir);
            if(isDir && ft==VIRTUAL){
				IShellFolder *psfFirstFolder = NULL;
                hr = f->BindToObject(pidlItems, NULL, IID_IShellFolder, (LPVOID *) &psfFirstFolder);
				LPITEMIDLIST	pidlComplete2 = ILCombine(pidlComplete,pidlItems);			
				scan_desktop0(psfFirstFolder,pidlComplete2,file);
				CoTaskMemFree(pidlComplete2);	
				psfFirstFolder->Release();
            }
        }
	}
	CoTaskMemFree(pidlItems);
	ppenum->Release();
}



pFileEntry scan_desktop(){
	pFileEntry desktop=NULL;
    IShellFolder *root = NULL;
    CoInitialize( NULL );
	if(SHGetDesktopFolder(&root) != S_OK) return 0;
	desktop = genDesktopFileEntry();
	scan_desktop0(root, NULL, desktop);
    root->Release();
    CoUninitialize();
	return desktop;
}

typedef google::sparse_hash_map<WCHAR *, pFileEntry> user_desktop;
user_desktop ud;

pFileEntry get_desktop(WCHAR *user_name){
	pFileEntry desktop = ud[user_name];
	if(desktop!=NULL) return desktop;
	load_desktop(user_name);
	return ud[user_name];
}

void put_desktop(WCHAR *user_name, pFileEntry desktop){
	ud[user_name] = desktop;
}


}// extern "C"