#pragma once

#include "AVTexture2D.h"
#include <stdarg.h>
#include <vector>

typedef struct TEXTURE{

	AVTexture2D		*texture2D;
	wchar_t			path[MAX_PATH];
	int				id;

}TEXTURE;

class SharedTexture2D
{
	std::vector<TEXTURE*> m_textureList;

private:
	SharedTexture2D();
	TEXTURE* CreateTexture(wchar_t *path, int &id);
	
public:
	~SharedTexture2D(void);

	static SharedTexture2D* GetsharedTexture2D();
	void Delete();

public:
	bool addFile(wchar_t *path, int id);
	void deleteAllTexture();

	bool deleteTexture(wchar_t *path);
	bool deleteTexture(int id);

	AVTexture2D* GetTexture2D(wchar_t *path);
	AVTexture2D* GetTexture2D(int id);
};

static SharedTexture2D *_sharedTexture = NULL;