#ifndef ANICTRL_H
#define ANICTRL_H


BEGIN(Engine)
class ENGINE_DLL CAniCtrl final
{
private:
	explicit					CAniCtrl			(LPD3DXANIMATIONCONTROLLER pAniCtrl);
							   ~CAniCtrl			(void);

public:
	static			CAniCtrl*	Create				(LPD3DXANIMATIONCONTROLLER pAniCtrl);
					void		Free				(void);

					CAniCtrl*	MakeClone			(void);

					void		Awake				(void);
					void		OnDestroy			(void);

					void		OnEnable			(void);
					void		OnDisable			(void);

public:
					void		ChangeAniSet		(_uint index, 
													 _bool fixTillEnd = false, 
													 _double smoothTime = 0.25,
													 _float changeWeight = 0.9f);
					void		ChangeAniSet		(std::string name, 
													 _bool fixTillEnd = false, 
													 _double smoothTime = 0.25,
													 _float changeWeight = 0.9f);

					void		ChangeFakeAniSet	(void);

					void		Play				(void);
					void		PlayFake			(void);
					_bool		IsItEnd				(void);



private:
					_uint		FindIndexByName		(std::string const& name, LPD3DXANIMATIONSET pAS);
private:
	GETTOR			(LPD3DXANIMATIONCONTROLLER,		m_pAniCtrl,		nullptr,	AniCtrl)
	GETTOR			(_uint,							m_curTrack,		0,			CurTrack)
	GETTOR			(_uint,							m_curIndex,		0,			CurIndex)
	GETTOR			(_float,						m_timer,		0.f,		Timer)
	GETTOR_SETTOR	(_float,						m_speed,		1.f,		Speed)
	GETTOR			(_float,						m_period,		0,			Period)
	GETTOR_SETTOR	(_bool,							m_replay,		true,		Replay)
	
	GETTOR_SETTOR	(_bool,							m_fixTillEnd,	false,		FixTillEnd)
	
private:	
	GETTOR			(LPD3DXANIMATIONCONTROLLER,		m_pFakeAniCtrl,	nullptr,	FakeAniCtrl)
	GETTOR			(_uint,							m_fakeTrack,	0,			FakeOldTrack)
	GETTOR			(_uint,							m_fakeIndex,	0,			FakeIndex)
	GETTOR			(_float,						m_fakeTimer,	0.f,		FakeTimer)
	GETTOR			(_float,						m_fakeTimerLastFrame,	0.f,		FakeTimerLastFrame)
	GETTOR			(_double,						m_fakePeriod,	0,			FakePeriod)
	GETTOR_SETTOR	(_bool,							m_isBlending,	false,		IsBlending)
	GETTOR			(double,						m_savedDT,	0.f,			SavedDeltaTime)
	GETTOR_SETTOR	(_bool,							m_isFakeAniEnd,	false,		IsFakeAniEnd)
	//GETTOR_SETTOR	(_bool,							m_isFakeAniStart,	false,		IsFakeAniStart)
};
END

#endif