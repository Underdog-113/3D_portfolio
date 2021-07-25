#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CSoundManager final : public CEngine
{
public:
	DECLARE_SINGLETON(CSoundManager)
public:
	void		Awake(void) override;
	void		Start(_int numOfSoundChannel);
	void		OnDestroy(void);
public:
	void StartSound(TCHAR* pSoundKey, _uint ID);
	void StartSound(TCHAR* pSoundKey, _uint ID, _float3 thisPosition, _float3 otherPosition);
	void StartSound(TCHAR* pSoundKey, _uint ID, const float volume);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(_uint ID);
	void StopAll();

	void GetChannelFrequency(_uint ID, float* frequency);
	void SetChannelFrequency(_uint ID, float frequency);

	// �������̸� true
	_bool IsPlaying(_uint eID);
	// 0.f ~ 1.f 
	void SetVolume(_uint ID, _float3 thisPosition, _float3 otherPosition);
	void SetVolume(_uint ID, float fVolume);
	// 0.f ~ 1.f 
	void VolumeIncrease(_uint ID, float fVolume);

	void LoadSoundFile(const std::wstring& path);
private:
	void LoadSoundFile();

public:
	GETTOR(_TCHAR*, m_pBGMSoundKey, L"", BGMSoundKey)

private:

	// ���� ���ҽ� ������ ���� ��ü 
	std::unordered_map<std::wstring, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[100];
	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem;
	//
	float m_fVolume[100];
};

END
#endif	