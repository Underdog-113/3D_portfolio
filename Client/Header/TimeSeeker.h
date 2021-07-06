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
	GETTOR	(_bool, m_perfectEvadeMode, false, IsPerfectEvadeMode)
	_bool	m_slowAll = false;
	_float	m_slowTimer = 0.f;
};
