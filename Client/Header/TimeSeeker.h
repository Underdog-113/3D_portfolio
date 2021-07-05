#pragma once
class CTimeSeeker
{
public:
	CTimeSeeker();
	~CTimeSeeker();

	void UpdateTimeSeeker();

	void OnPerfectEvadeMode();
	void PlayPerfectEvadeMode();
	_float GetPlayerDeltaTime();

private:
	_bool	m_perfectEvadeMode = false;
	_bool	m_slowAll = false;
	_float	m_slowTimer = 0.f;
};

