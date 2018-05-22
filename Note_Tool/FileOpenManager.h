#pragma once

#include <Windows.h>

#define NOTEFILE  0
#define SOUNDFILE 1

class FileOpenManager
{
private:
	HDC				m_hdc;
	PAINTSTRUCT		m_ps;
	OPENFILENAME	m_OFN;

public:
	bool			m_isSoundLoad;

private:
	FileOpenManager(void);

public:
	~FileOpenManager(void);

	static FileOpenManager* GetFOM();
	void deleteFOM();

	bool OpenToDialog(int buttonID, HWND hWnd);

	wchar_t* GetPath();
	wchar_t* GetName();
	bool	 GetisSoundLoad() { return m_isSoundLoad; }
	void	 SetisSoundLoad(bool is) { m_isSoundLoad = is; }
};

//satic member
static FileOpenManager *_sharedFOM = NULL;