#include "SoundPlayer.h"

SoundPlayer::SoundPlayer(void)
{
	m_graphBuilder = NULL;
	m_mediaControl = NULL; m_mediaPosition = NULL;
	m_basicAudio = NULL;

	m_sndLoop		= false;
	m_isPlay		= false;
	m_isSoundLoad	= false;

	CoInitialize(NULL);
}


SoundPlayer::~SoundPlayer(void)
{
	Destroy();
	CoUninitialize();
}

bool SoundPlayer::Create(wchar_t* filename)
{
	Destroy();

	if(FAILED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_graphBuilder)))
		return false;

	if(FAILED(m_graphBuilder->RenderFile(filename, NULL)))
	{ Destroy(); return false; }

	if(FAILED(m_graphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_mediaControl)))
	{ Destroy(); return false; }

	if(FAILED(m_graphBuilder->QueryInterface(IID_IMediaPosition, (void**)&m_mediaPosition)))
	{ Destroy(); return false; }

	if(FAILED(m_graphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_basicAudio)))
	{ Destroy(); return false; }

	m_isSoundLoad = true;

	

	return true;
}

void SoundPlayer::Destroy()
{
	m_isSoundLoad = false;

	SafeRelease(m_basicAudio);
	SafeRelease(m_mediaPosition);
	SafeRelease(m_mediaControl);
	SafeRelease(m_graphBuilder);
}

bool SoundPlayer::Play(bool loopMode)
{
	if( GetisSoundLoad() == false )
	{
		MessageBox(NULL, L"사운드 파일을 로딩하지 않았습니다", 
			L"Error", MB_OK);

		return false;
	}

	m_mediaControl->Run();

	return m_isPlay = true;
}

void SoundPlayer::Pause()
{
	m_mediaControl->Pause();
}

void SoundPlayer::Stop()
{
	if( GetisSoundLoad() == false )
	{
		MessageBox(NULL, L"사운드 파일을 로딩하지 않았습니다", 
			L"Error", MB_OK);

		return;
	}

	m_mediaControl->StopWhenReady();
	m_mediaPosition->put_CurrentPosition(0);
	m_isPlay = false;
}

REFTIME SoundPlayer::GetPosition()
{
	REFTIME temp = 0; m_mediaPosition->get_CurrentPosition(&temp);
	return temp;
}

void SoundPlayer::SetPosition(REFTIME pos)
{
	if(m_mediaPosition==NULL)
	{
		MessageBox(NULL, L"사운드가 로드되지 않았습니다", L"오류", MB_OK);
		return;
	}

	m_mediaPosition->put_CurrentPosition(pos);
}

REFTIME SoundPlayer::GetDuration()
{
	REFTIME temp = 0; m_mediaPosition->get_Duration(&temp);
	unsigned ms = (unsigned)(temp / 1000000);
	return ms;
}

REFTIME SoundPlayer::GetEndTime()
{
	REFTIME temp = 0; m_mediaPosition->get_StopTime(&temp);
	return temp;
}

int SoundPlayer::GetVolume()
{
	LONG temp = 0; m_basicAudio->get_Volume(&temp);
	return temp;
}

void SoundPlayer::SetVolume(int vol)
{
	m_basicAudio->put_Volume(vol);
}

int SoundPlayer::GetBalance()
{
	LONG temp = 0; m_basicAudio->get_Balance(&temp);
	return temp;
}

void SoundPlayer::SetBalance(int bal)
{
	m_basicAudio->put_Balance(bal);
}

bool SoundPlayer::GetisSoundEnd()
{
	if( this->GetEndTime() == this->GetPosition() )
	{
		m_isPlay = false;
		return true;
	}

	return false;
}