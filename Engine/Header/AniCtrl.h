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
													 _double smoothTime = 0.2,
													 _float changeWeight = 0.9f);

					void		ChangeAniSet		(std::string name,
													 _bool fixTillEnd = false,
													 _double smoothTime = 0.2,
													 _float changeWeight = 0.9f);

					
					void		RepeatAniSet		(_uint index,
													 _bool fixTillEnd = false,
													 _double smoothTime = 0.2,
													 _float changeWeight = 0.9f);

					void		ChangeFakeAniSet	(void);

					void		Play				(void);
					void		PlayFake			(void);
					void		ChangeFakeAnimState_EndToStart(void);
					_bool		IsItEnd				(void);
					
					void		ResetTimers			(void);
					void		ResetAnimation		(void);

					void		CreateLoopAnimArray(_uint size);
					void		SetLoopAnim(_uint animIndex);

					void		ChangeAniSet_NoBlend(_uint index);
private:
					_uint		FindIndexByName		(std::string const& name, LPD3DXANIMATIONSET pAS);
					
private:
	GETTOR			(LPD3DXANIMATIONCONTROLLER,		m_pAniCtrl,		nullptr,	AniCtrl)
	GETTOR			(_uint,							m_curTrack,		0,			CurTrack)
	GETTOR			(_uint,							m_oldTrack,		0,			OldTrack)
	GETTOR			(_uint,							m_curIndex,		0,			CurIndex)
	GETTOR			(_float,						m_timer,		0.f,		Timer)
	GETTOR_SETTOR	(_float,						m_speed,		1.f,		Speed)
	GETTOR			(_float,						m_period,		0,			Period)
	GETTOR			(double,						m_timeline,		0,			AniTimeline)
	GETTOR_SETTOR	(_bool,							m_replay,		true,		Replay)	
	GETTOR_SETTOR	(_bool,							m_fixTillEnd,	false,		FixTillEnd)
		
	GETTOR_SETTOR	(_bool,							m_isAdvanceByPure,	false,	IsAdvanceByPure)
		
	GETTOR			(_bool*,						m_pLoopAnims,	nullptr,	LoopAnims)


	_float m_oldWeight = 0.f;
	_float m_curWeight = 0.f;

	_float m_prevLerpWeight = 0.f;
	double m_blendTimer = 0;
	double m_blendDuration = 0;
	_bool m_isBlending = false;

private:
	GETTOR			(LPD3DXANIMATIONCONTROLLER,		m_pFakeAniCtrl,			nullptr,	FakeAniCtrl)
	GETTOR			(_uint,							m_fakeTrack,			0,			FakeTrack)
	GETTOR			(_uint,							m_fakeIndex,			0,			FakeIndex)
	GETTOR			(double,						m_fakeTimer,			0.f,		FakeTimer)
	GETTOR			(_double,						m_fakePeriod,			0,			FakePeriod)
	GETTOR			(double,						m_fakeTimeline,			0,			Timeline)
	GETTOR			(double,						m_savedFakeAniTime,		0.f,		SavedDeltaTime)
	GETTOR_SETTOR	(_bool,							m_isFakeAniEnd,			false,		IsFakeAniEnd)
	GETTOR_SETTOR	(_bool,							m_isFakeAniChange,		false,		IsFakeAniChange)
};
END

#endif
