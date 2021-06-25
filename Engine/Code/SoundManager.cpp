#include "EngineStdafx.h"
#include "SoundManager.h"


USING(Engine)
IMPLEMENT_SINGLETON(CSoundManager)

void CSoundManager::Awake(void)
{
	FMOD_System_Create(&m_pSystem);

	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();

	SetVolume((_uint)EChannelID::BGM, 0.5f);
}

void CSoundManager::OnDestroy(void)
{
	for (auto& Mypair : m_mapSound)
	{
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear();
	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);

}



void CSoundManager::StartSound(TCHAR * pSoundKey, _uint ID)
{
	std::unordered_map<std::wstring, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
	{
		return !lstrcmp(pSoundKey, iter.first.c_str());
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;
	if (FMOD_Channel_IsPlaying(m_pChannelArr[ID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[ID]);
		m_fVolume[ID] = 1.f;
	}
	FMOD_Channel_SetMode(m_pChannelArr[ID], FMOD_LOOP_OFF);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::StartSound(TCHAR * pSoundKey, _uint ID, _float3 thisPosition, _float3 otherPosition)
{
	std::unordered_map<std::wstring, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
	{
		return !lstrcmp(pSoundKey, iter.first.c_str());
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;
	if (FMOD_Channel_IsPlaying(m_pChannelArr[ID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[ID]);
		m_fVolume[ID] = 1.f;
	}

	SetVolume(ID, thisPosition, otherPosition);
}

void CSoundManager::StartSound(TCHAR * pSoundKey, _uint ID, const float volume)
{
}

void CSoundManager::PlayBGM(TCHAR * pSoundKey)
{
	std::unordered_map<std::wstring, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
	{
		return !lstrcmp(pSoundKey, iter.first.c_str());
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[(_uint)EChannelID::BGM]);
	FMOD_Channel_SetMode(m_pChannelArr[(_uint)EChannelID::BGM], FMOD_LOOP_NORMAL);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::StopSound(_uint ID)
{
	FMOD_Channel_Stop(m_pChannelArr[ID]);
}

void CSoundManager::StopAll()
{
	for (int i = 0; i < (_uint)EChannelID::NumOfChannelID; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundManager::GetChannelFrequency(_uint ID, float * frequency)
{
	FMOD_Channel_GetFrequency(m_pChannelArr[ID], frequency);
}

void CSoundManager::SetChannelFrequency(_uint ID, float frequency)
{
	FMOD_Channel_SetFrequency(m_pChannelArr[ID], frequency);
}

_bool CSoundManager::IsPlaying(_uint ID)
{
	FMOD_BOOL bPlay = FALSE;
	if (FMOD_Channel_IsPlaying(m_pChannelArr[ID], &bPlay))
		return false;
	else
		return true;
}

void CSoundManager::SetVolume(_uint ID, _float3 thisPosition, _float3 otherPosition)
{
	_float3 dis = otherPosition - thisPosition;
	float disForVolume = D3DXVec3Length(&dis);

	if (1000.f <= disForVolume)
		m_fVolume[ID] = 0.f;

	float volume = 1.f - disForVolume / 1000.f;

	m_fVolume[ID] = volume;

	FMOD_Channel_SetVolume(m_pChannelArr[ID], m_fVolume[ID]);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::SetVolume(_uint ID, float fVolume)
{
	if (fVolume > 1.f)
		fVolume = 1.f;
	else if (fVolume < 0.f)
		fVolume = 0.f;
	else
		m_fVolume[ID] = fVolume;

	FMOD_Channel_SetVolume(m_pChannelArr[ID], m_fVolume[ID]);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::VolumeIncrease(_uint ID, float fVolume)
{
	m_fVolume[ID] += fVolume;

	if (m_fVolume[ID] > 1.f)
		m_fVolume[ID] = 1.f;
	else if (m_fVolume[ID] < 0.f)
		m_fVolume[ID] = 0.f;
	FMOD_Channel_SetVolume(m_pChannelArr[ID], m_fVolume[ID]);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::LoadSoundFile(const std::wstring & path)
{
	WIN32_FIND_DATA fd;
	std::wstring curDir = _SOLUTIONDIR L"Resource\\Sound\\";
	curDir += path;
	std::wstring fullFilePath, curFile;

	HANDLE handle = FindFirstFile((curDir + L"\\*").c_str(), &fd);

	if (handle == INVALID_HANDLE_VALUE)
	{
		MSG_BOX(__FILE__, L"Given path is wrong during getting handle in SoundManager");
		ABORT;
	}

	do
	{
		curFile = fd.cFileName;
		fullFilePath = curDir + L"\\" + curFile;

		if (curFile[0] == '.')
			continue;

		FMOD_SOUND* pSound = nullptr;
		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem,
			WStrToStr(fullFilePath).c_str(),
			FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			m_mapSound.emplace(curFile, pSound);
		}

	} while (FindNextFile(handle, &fd));

	FMOD_System_Update(m_pSystem);
}

void CSoundManager::LoadSoundFile()
{
	WIN32_FIND_DATA fileData;
	
	std::vector<std::wstring> dirNameVector;
	std::vector<std::wstring> fileNameVector;

	std::wstring sourcePath = _SOLUTIONDIR L"Resource\\Sound";
	std::wstring curDir;
	std::wstring fullFilePath, curFile;


	dirNameVector.push_back(sourcePath);

	do 
	{
		curDir = dirNameVector.back();
		dirNameVector.pop_back();

		//받은 디렉토리의 첫 파일을 찾아 fileData에 정보를 넣고 HANDLE을 반환
		HANDLE findHandle = FindFirstFile((curDir + L"\\*").c_str(), &fileData);
		if (findHandle == INVALID_HANDLE_VALUE)
		{
			MSG_BOX(__FILE__, L"Given path is wrong during getting handle in SoundManager");
			ABORT;
		}

		do
		{
			//찾은 fileData로부터 현재 보고있는 파일, 그리고 풀 패스를 설정
			curFile = fileData.cFileName;
			fullFilePath = curDir + L"\\" + curFile;

			//현재 보고있는 파일이 directory인지 아닌지 체크
			bool isItDir = ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) ? false : true;


			//파일 이름이 .으로 시작하면 시스템 파일이다, 넘김.
			if (curFile[0] == '.')
				continue;

			//디렉토리라면 디렉토리 벡터에 넣고 넘긴다.
			if (isItDir)
			{
				dirNameVector.push_back(fullFilePath);
				continue;
			}

			//디렉토리가 아닌 파일마다 함수 포인터에 담긴 함수를 호출한다.
			FMOD_SOUND* pSound = nullptr;
			FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem,
													   WStrToStr(fullFilePath).c_str(),
													   FMOD_HARDWARE, 0, &pSound);

			if (eRes == FMOD_OK)
				m_mapSound.emplace(curFile, pSound);

		} while (FindNextFile(findHandle, &fileData));
	} while (!dirNameVector.empty());

	FMOD_System_Update(m_pSystem);
}

void CSoundManager::GetChannelFrequency(_uint ID, float * frequency)
{
	FMOD_Channel_GetFrequency(m_pChannelArr[ID], frequency);
}

void CSoundManager::SetChannelFrequency(_uint ID, float frequency)
{
	FMOD_Channel_SetFrequency(m_pChannelArr[ID], frequency);
}