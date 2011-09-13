#ifndef FILEOPERATIONS_INCLUDED
#define FILEOPERATIONS_INCLUDED

typedef enum
{
	OVERWRITE_ONEPASS	= 1,
	OVERWRITE_THREEPASS	= 2
} OVERWRITE_METHODS;

/* Renaming. */
int		RenameFile(TCHAR *NewFileName,TCHAR *OldFileName);

/* Deletion. */
int		DeleteFiles(HWND,TCHAR *,BOOL);
int		DeleteFilesToRecycleBin(HWND hwnd,TCHAR *FileNameList);
int		DeleteFilesPermanently(HWND hwnd,TCHAR *FileNameList);
void	DeleteFileSecurely(TCHAR *szFileName,UINT uOverwriteMethod);

/* Copy and cut. */
HRESULT CopyFilesToClipboard(TCHAR *FileNameList,size_t iListSize,BOOL bMove,IDataObject **pClipboardDataObject);
HRESULT	CopyFiles(TCHAR *szFileNameList,int iListSize,IDataObject **pClipboardDataObject);
HRESULT	CutFiles(TCHAR *szFileNameList,int iListSize,IDataObject **pClipboardDataObject);


#endif