#include "SharedTexture2D.h"
#include "AVDirector.h"

SharedTexture2D::SharedTexture2D(void)
{
}


SharedTexture2D::~SharedTexture2D(void)
{
}

SharedTexture2D* SharedTexture2D::GetsharedTexture2D()
{
	if( _sharedTexture == NULL ) _sharedTexture = new SharedTexture2D;
	return _sharedTexture;
}

void SharedTexture2D::Delete()
{
	if(_sharedTexture) delete _sharedTexture;
	_sharedTexture = NULL;
}

bool SharedTexture2D::addFile(wchar_t *path, int id)
{
	std::vector<TEXTURE*>::iterator iter;

	for(iter = m_textureList.begin() ; iter != m_textureList.end() ; iter++)
		if( (*iter)->id == id || ( wcscmp((*iter)->path, path) == 0) )		return false;

	m_textureList.push_back(CreateTexture(path, id));
	return true;
}

TEXTURE* SharedTexture2D::CreateTexture(wchar_t *path, int &id)
{
	TEXTURE *tex = new TEXTURE;
	tex->texture2D = new AVTexture2D;
	tex->texture2D->CreateTexture(path);

	tex->id = id;

	wcscpy(tex->path, path);

	return tex;
}

void SharedTexture2D::deleteAllTexture()
{
	for(int i = 0; i < m_textureList.size(); i++)
		SAFE_DELETE(m_textureList[i]);

	m_textureList.clear();
}

AVTexture2D* SharedTexture2D::GetTexture2D(wchar_t *path)
{
	std::vector<TEXTURE*>::iterator iter;

	for(iter = m_textureList.begin() ; iter != m_textureList.end() ; iter++)
	{
		if( wcscmp((*iter)->path, path) == 0 )
		{
			return (*iter)->texture2D;
		}
	}

	return NULL;
}

AVTexture2D* SharedTexture2D::GetTexture2D(int id)
{
	std::vector<TEXTURE*>::iterator iter;

	for(iter = m_textureList.begin() ; iter != m_textureList.end() ; iter++)
	{
		if( (*iter)->id == id )
		{
			return (*iter)->texture2D;
		}
	}

	return NULL;
}

bool SharedTexture2D::deleteTexture(wchar_t *path)
{
	for(int i = 0; i < m_textureList.size(); i++ )
	{
		if(wcscmp(m_textureList[i]->path, path) == 0)
		{
			SAFE_DELETE(m_textureList[i]);
			m_textureList.erase(m_textureList.begin() + i);
			return true;
		}
	}

	return false;
}

bool SharedTexture2D::deleteTexture(int id)
{
	for(int i = 0; i < m_textureList.size(); i++ )
	{
		if( m_textureList[i]->id == id )
		{
			SAFE_DELETE(m_textureList[i]);
			m_textureList.erase(m_textureList.begin() + i);
			return true;
		}
	}

	return false;
}