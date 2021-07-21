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

	void OnAttackImpactSlow();
	void PlayAttackImpactSlow();

	void OnSlowExceptPlayer();
	void OffSlowExceptPlayer();
	void PlaySlowExceptPlayer();

private:
	GETTOR	(_bool, m_perfectEvadeMode, false, IsPerfectEvadeMode)
	_bool	m_slowAll = false;
	_float	m_slowTimer = 0.f;

	_uint m_prevColoring = 0;
	
	GETTOR	(_bool, m_isAttackImpactSlow, false, IsAttackImpactSlow)

		
	GETTOR	(_bool, m_isSlowExceptPlayer, false, IsSlowExceptPlayer)
};

