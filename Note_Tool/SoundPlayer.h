#pragma once

#include <DShow.h>

#pragma comment (lib, "strmiids.lib")


#define SafeRelease(X)\
	if(X!=NULL) X->Release(); X=NULL

class SoundPlayer
{
	IGraphBuilder *m_graphBuilder;
	IMediaControl *m_mediaControl;
	IMediaPosition *m_mediaPosition;
	IBasicAudio *m_basicAudio;

	bool m_sndLoop;

	bool m_isPlay;
	bool m_isSoundLoad;

public:
	SoundPlayer(void);
	~SoundPlayer(void);


	bool Create(wchar_t* filename);
	void Destroy();

	bool Play(bool loopMode);
	void Pause();
	void Stop();

	REFTIME GetPosition();
	void SetPosition(REFTIME pos);
	REFTIME GetDuration();

	int GetVolume();
	void SetVolume(int vol);

	int GetBalance();
	void SetBalance(int bal);

	REFTIME GetEndTime();

	bool GetisPlay() { return m_isPlay; }
	void SetisPlay(bool is) { m_isPlay = is; } 

	bool GetisSoundLoad() { return m_isSoundLoad; }
	bool GetisSoundEnd();
};

