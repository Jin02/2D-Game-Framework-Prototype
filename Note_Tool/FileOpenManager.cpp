#include "FileOpenManager.h"
#include "resource.h"

FileOpenManager::FileOpenManager(void)
{
	memset( &m_OFN, 0, sizeof(OPENFILENAME) );
	m_isSoundLoad = false;
}

FileOpenManager::~FileOpenManager(void)
{
}

FileOpenManager* FileOpenManager::GetFOM()
{
	if(_sharedFOM == NULL) 
		_sharedFOM = new FileOpenManager;

	return _sharedFOM;
}

void FileOpenManager::deleteFOM()
{
	if(_sharedFOM) 
		delete _sharedFOM;
	
	_sharedFOM = NULL;
}

bool FileOpenManager::OpenToDialog(int buttonID, HWND hWnd)
{
//	DWORD result;
	static wchar_t tempFileName[256] = L"";
	static wchar_t tempFile[256]	=  L"";

	memset( &m_OFN, 0, sizeof(OPENFILENAME) );

	if( buttonID == ID_SOUND_LOAD || buttonID == IDC_BUT_SOUND_LOAD )
	{
		m_OFN.lpstrDefExt		= L"mp3";
		m_OFN.lpstrFilter		= L"mp3 파일 .mp3\0*.mp3\0wav 파일\0*.wav\0모든 파일\0*.*\0";

		m_isSoundLoad			= true;
	}
	
	else
	{
		m_OFN.lpstrDefExt		= L"notedat";
		m_OFN.lpstrFilter		= L"노트 파일 .notedat\0*.notedat\0모든 파일\0*.*\0";
	}

	m_OFN.lStructSize		= sizeof(OPENFILENAME);
	m_OFN.hwndOwner			= hWnd;

	m_OFN.lpstrTitle = NULL;

	m_OFN.lpstrFile			= tempFileName;
	m_OFN.nMaxFile			= MAX_PATH;
	m_OFN.lpstrFileTitle	= tempFile;
	m_OFN.nMaxFileTitle		= MAX_PATH;

	if( buttonID == ID_SOUND_LOAD || buttonID == IDC_BUT_SOUND_LOAD )
		return GetOpenFileName(&m_OFN);
	else return GetSaveFileName(&m_OFN);
}

wchar_t* FileOpenManager::GetPath()
{ 
	return m_OFN.lpstrFile; 
}

wchar_t* FileOpenManager::GetName()
{
	return m_OFN.lpstrFileTitle;
}