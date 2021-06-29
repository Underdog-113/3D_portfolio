#include "EngineStdafx.h"
#include "AniCtrl.h"



USING(Engine)
CAniCtrl::CAniCtrl(LPD3DXANIMATIONCONTROLLER pAniCtrl)
	: m_pAniCtrl(pAniCtrl), m_pFakeAniCtrl(pAniCtrl)
{
}


CAniCtrl::~CAniCtrl()
{
	if (m_pLoopAnims)
		delete[] m_pLoopAnims;
}

CAniCtrl * CAniCtrl::Create(LPD3DXANIMATIONCONTROLLER pAniCtrl)
{
	CAniCtrl* pInstance = new CAniCtrl(pAniCtrl);
	pInstance->Awake();

	return pInstance;
}

void CAniCtrl::Free(void)
{
	OnDestroy();
	delete this;
}

CAniCtrl* CAniCtrl::MakeClone(void)
{
	CAniCtrl* pClone = new CAniCtrl(nullptr);
	LPD3DXANIMATIONCONTROLLER pAniCtrlForClone = NULL;

	m_pAniCtrl->CloneAnimationController(m_pAniCtrl->GetMaxNumAnimationOutputs(),
										 m_pAniCtrl->GetMaxNumAnimationSets(),
										 m_pAniCtrl->GetMaxNumTracks(),
										 m_pAniCtrl->GetMaxNumEvents(),
										 &pClone->m_pAniCtrl);

	m_pAniCtrl->CloneAnimationController(m_pAniCtrl->GetMaxNumAnimationOutputs(),
										 m_pAniCtrl->GetMaxNumAnimationSets(),
										 m_pAniCtrl->GetMaxNumTracks(),
										 m_pAniCtrl->GetMaxNumEvents(),
										 &pClone->m_pFakeAniCtrl);
	m_replay = true;

	//pClone->ChangeAniSet(0);

	LPD3DXANIMATIONSET pAS = NULL;

	m_pAniCtrl->GetAnimationSet(m_curIndex, &pAS);
	pClone->m_period = (_float)pAS->GetPeriod();

	pClone->m_fakePeriod = (_float)pAS->GetPeriod();

	pClone->CreateLoopAnimArray(m_pAniCtrl->GetMaxNumAnimationSets());

	return pClone;
}

void CAniCtrl::Awake(void)
{
}

void CAniCtrl::OnDestroy(void)
{
	m_pAniCtrl->Release();
}

void CAniCtrl::OnEnable(void)
{
}

void CAniCtrl::OnDisable(void)
{
}

void CAniCtrl::ChangeAniSet(_uint index, _bool fixTillEnd, _double smoothTime, _float changeWeight)
{
	if (index > m_pAniCtrl->GetMaxNumAnimationSets() - 1)
		index = 0;

	if (m_curIndex == index)
		return;


	_int newTrack = m_curTrack == 0 ? 1 : 0;

	LPD3DXANIMATIONSET pAS = NULL;

	m_pAniCtrl->GetAnimationSet(index, &pAS);

	m_pAniCtrl->SetTrackAnimationSet(newTrack, pAS);
	m_pAniCtrl->UnkeyAllTrackEvents(m_curTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(newTrack);

	_double blendTime;

	blendTime = m_period - m_timer;
	while (blendTime < 0.f)
	{
		blendTime += m_period;
	}

	if (blendTime > 0.2f || m_pLoopAnims[index])
		blendTime = 0.2f;

	m_period = (_float)pAS->GetPeriod();

	m_pAniCtrl->KeyTrackEnable(m_curTrack, FALSE, m_timer + blendTime);
	m_pAniCtrl->KeyTrackSpeed(m_curTrack, 1.f, m_timer, blendTime, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_curTrack, 0.1f, m_timer, blendTime, D3DXTRANSITION_LINEAR);
	

	m_pAniCtrl->SetTrackEnable(newTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(newTrack, 1.f, m_timer, blendTime, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(newTrack, 0.9f, m_timer, blendTime, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->ResetTime();
	m_timer = 0.f;

	m_pAniCtrl->SetTrackPosition(newTrack, 0.0);
	m_curIndex = index;
	m_curTrack = newTrack;
	m_fixTillEnd = fixTillEnd;

	ChangeFakeAniSet();
}

void CAniCtrl::ChangeAniSet(std::string name, _bool fixTillEnd, _double smoothTime, _float changeWeight)
{
	_int newTrack = m_curTrack == 0 ? 1 : 0;
	LPD3DXANIMATIONSET pAS = NULL;
	m_pAniCtrl->GetAnimationSet(m_curIndex, &pAS);

	if (pAS->GetName() == name)
		return;

	//이거하던중
	m_pAniCtrl->GetAnimationSetByName(name.c_str(), &pAS);

	m_curIndex = FindIndexByName(name, pAS);

	m_pAniCtrl->SetTrackAnimationSet(newTrack, pAS);
	m_pAniCtrl->UnkeyAllTrackEvents(m_curTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(newTrack);

	_double blendTime;
	blendTime = m_period - m_timer;
	while (blendTime < 0.f)
	{
		blendTime += m_period;
	}

	if (blendTime > 0.2f || m_pLoopAnims[m_curIndex])
		blendTime = 0.2f;

	m_period = (_float)pAS->GetPeriod();

	//현재 트랙을 끈다.
	m_pAniCtrl->KeyTrackEnable(m_curTrack, FALSE, m_timer + blendTime);
	//꺼지는 동안 키 속도 세팅
	m_pAniCtrl->KeyTrackSpeed(m_curTrack, 1.f, m_timer, blendTime, D3DXTRANSITION_LINEAR);
	//꺼지는 동안 가중치
	m_pAniCtrl->KeyTrackWeight(m_curTrack, 0.1f, m_timer, blendTime, D3DXTRANSITION_LINEAR);
	
	//새 트랙 활성화
	m_pAniCtrl->SetTrackEnable(newTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(newTrack, 1.f, m_timer, blendTime, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(newTrack, 0.9f, m_timer, blendTime, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->ResetTime();
	m_timer = 0.f;

	m_pAniCtrl->SetTrackPosition(newTrack, 0.0);

	m_curTrack = newTrack;
	m_fixTillEnd = fixTillEnd;

	ChangeFakeAniSet();
}

void CAniCtrl::ChangeFakeAniSet()
{
	//if (m_fakeIndex == m_curIndex)
	//	return;

	LPD3DXANIMATIONSET	pAnimationSet = nullptr;

	m_pFakeAniCtrl->GetAnimationSet(m_curIndex, &pAnimationSet);


	_int newTrack = m_fakeTrack == 0 ? 1 : 0;

	m_pFakeAniCtrl->SetTrackAnimationSet(newTrack, pAnimationSet);

	m_pFakeAniCtrl->UnkeyAllTrackEvents(m_fakeTrack);
	m_pFakeAniCtrl->UnkeyAllTrackEvents(newTrack);
	
	_double blendTime;
	blendTime = m_fakePeriod - m_fakeTimer;
	while (blendTime < 0.f)
	{
		blendTime += m_period;
	}
	
	if (blendTime > 0.01f || m_pLoopAnims[m_curIndex])
		blendTime = 0.01f;

	m_fakePeriod = (_float)pAnimationSet->GetPeriod();


	m_pFakeAniCtrl->KeyTrackEnable(m_fakeTrack, FALSE, m_fakeTimer + blendTime);
	//m_pFakeAniCtrl->SetTrackEnable(m_fakeTrack, FALSE);
	//m_pFakeAniCtrl->SetTrackPosition(m_fakeTrack, m_fakePeriod);

	////꺼지는 동안 키 속도 세팅
	m_pFakeAniCtrl->KeyTrackSpeed(m_fakeTrack, 1.f, m_fakeTimer, blendTime, D3DXTRANSITION_LINEAR);
	////꺼지는 동안 가중치
	m_pFakeAniCtrl->KeyTrackWeight(m_fakeTrack, 0.01f, m_fakeTimer, blendTime, D3DXTRANSITION_LINEAR);

	m_pFakeAniCtrl->SetTrackEnable(newTrack, TRUE);

	////꺼지는 동안 키 속도 세팅
	m_pFakeAniCtrl->KeyTrackSpeed(m_curTrack, 1.f, m_fakeTimer, blendTime, D3DXTRANSITION_LINEAR);
	////꺼지는 동안 가중치
	m_pFakeAniCtrl->KeyTrackWeight(m_curTrack, 0.99f, m_fakeTimer, blendTime, D3DXTRANSITION_LINEAR);

	m_pFakeAniCtrl->ResetTime();
	m_fakeTimer = 0.f;

	m_pFakeAniCtrl->SetTrackPosition(newTrack, 0.0);

	m_fakeIndex = m_curIndex;
	m_fakeTrack = newTrack;


	m_isFakeAniChange = true;
}


void CAniCtrl::Play(void)
{
	_float deltaTime = GET_DT;
	m_timer += deltaTime * m_speed;
	if (m_replay == false && m_timer > m_period)
	{
		m_timer = (_float)m_period;
		return;
	}

	m_pAniCtrl->AdvanceTime(deltaTime * m_speed, NULL);
}


void CAniCtrl::PlayFake()
{
	_float deltaTime = GET_DT;
	m_fakeTimer += deltaTime * m_speed;
	if (m_fakeTimer / m_fakePeriod >= 0.99)
	{
		m_isFakeAniEnd = true;

		m_pFakeAniCtrl->SetTrackPosition(m_fakeTrack, m_fakePeriod * 0.99);
		m_pFakeAniCtrl->AdvanceTime(0, NULL);
		return;
	}

	m_pFakeAniCtrl->AdvanceTime(deltaTime * m_speed, NULL);
}

void CAniCtrl::ChangeFakeAnimState_EndToStart(void)
{
	m_isFakeAniEnd = false;

	m_fakeTimer = m_fakePeriod * 0.01;
	m_pFakeAniCtrl->SetTrackPosition(m_fakeTrack, m_fakeTimer);
	m_pFakeAniCtrl->AdvanceTime(0, NULL);
}

_bool CAniCtrl::IsItEnd(void)
{
	D3DXTRACK_DESC	TrackInfo;
	ZeroMemory(&TrackInfo, sizeof(D3DXTRACK_DESC));

	m_pAniCtrl->GetTrackDesc(m_curTrack, &TrackInfo);


	if (TrackInfo.Position >= m_period - 0.25)
		return true;


	return false;
}

double CAniCtrl::GetTimeline_Blend(void)
{
	return (double)m_timer / m_period;
}

double CAniCtrl::GetTimeline(void)
{
	return (double)m_fakeTimer / m_fakePeriod;
}

void CAniCtrl::ResetTimers(void)
{
	m_timer = 0.f;
	m_fakeTimer = 0.f;
}

void CAniCtrl::ResetAnimation(void)
{
	m_pAniCtrl->SetTrackPosition(0, m_period * 0.01);
	m_pAniCtrl->SetTrackPosition(1, m_period * 0.01);
	m_timer = m_period * 0.01f;
}

_uint CAniCtrl::FindIndexByName(std::string const & name, LPD3DXANIMATIONSET pAS)
{
	for (_uint i = 0; i < m_pAniCtrl->GetNumAnimationSets(); ++i)
	{
		LPD3DXANIMATIONSET compareAS;
		m_pAniCtrl->GetAnimationSet(i, &compareAS);
		if (compareAS == pAS)
			return i;
	}

	MSG_BOX(__FILE__, L"Failed to find animationSet by name in FindIndexByName");
	ABORT;
	return UNDEFINED;
}

void CAniCtrl::CreateLoopAnimArray(_uint size)
{
	m_pLoopAnims = new bool[size];

	for (_uint i = 0; i < size; ++i)
	{
		m_pLoopAnims[i] = false;
	}
}

void CAniCtrl::SetLoopAnim(_uint animIndex)
{
	m_pLoopAnims[animIndex] = true;
}
