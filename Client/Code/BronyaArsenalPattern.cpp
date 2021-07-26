#include "stdafx.h"
#include "BronyaArsenalPattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"
#include "BronyaBullet.h"
#include "Bronya_Ult_Range.h"
#include "Bronya_Ult_Ring.h"
#include "Bronya_Weapon.h"

#include "Bronya_Teleport_Ring.h"
#include "Bronya_Teleport_Laser.h"

CBronyaArsenalPattern::CBronyaArsenalPattern()
{
}

CBronyaArsenalPattern::~CBronyaArsenalPattern()
{
}

void CBronyaArsenalPattern::Pattern(Engine::CObject* pOwner)
{
	InitEffect();

	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);

	// 1. 센터로 escape
	// 2. 구석으로 escape
	// 3. 패턴 실행

	/************************* Fast Idle */
	if (Name_IDLE == fsm->GetCurStateString())
	{
		if (fsm->GetDM()->IsAnimationEnd())
		{
			fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		}
		else
		{
			fsm->GetDM()->GetAniCtrl()->SetSpeed(1.7f);
		}
	}

	/************************* Move Center */
	if (false == m_movedCenter)
	{
		static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(true);
		_float3 endPos = { 186.04f, mPos.y, -8.94f };
		EscapePos(pOwner, fsm, mPos, endPos, m_movedCenter);
	}

	/************************* Move Corner */
	if (true == m_movedCenter && false == m_movedCorner)
	{
		pOwner->GetTransform()->SetForward(_float3(0, 0, 1));

		_float3 endPos = { 186.21f, mPos.y, -17.06f };
		EscapePos(pOwner, fsm, mPos, endPos, m_movedCorner);
	}

	/************************* Sound */
	if (Name_Arsenal_Charge == fsm->GetCurStateString() &&
		0.75f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onArsenalReadySound)
	{
		// sound
		PatternPlaySound(L"Bronya_Ult_Ready.wav", pOwner);
		m_onArsenalReadySound = true;
	}

	/************************* Arsenal */
	// 내가 대기 상태가 끝났고, corner로 이동했으면
	if (Name_IDLE == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onArsenal)
	{
		// Arsenal Charge 상태로 변경
		fsm->ChangeState(Name_Arsenal_Charge);
	}
	// 내가 Arsenal Charge 상태가 끝났다면
	else if (Name_Arsenal_Charge == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		

		// Arsenal Loop 상태로 변경
		fsm->ChangeState(Name_Arsenal_Loop);
		m_atkReady = false;

		return;
	}
	// 내가 Arsenal Loop가 끝났고, 쿨타임도 끝났다면
	else if (Name_Arsenal_Loop == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		true == m_atkReady)
	{
		// Arsenal End 상태로 변경
		fsm->ChangeState(Name_Arsenal_End);

		// 어택볼 끄고, range 이펙트 지우기
		_int cnt = static_cast<CMB_Bronya*>(pOwner)->GetMaxArsenalEffectCnt();
		for (_int i = 0; i < cnt; ++i)
		{
			// attackball 끄기
			static_cast<CMB_Bronya*>(pOwner)->GetExplosions()[i]->SetIsEnabled(false);
			static_cast<CMB_Bronya*>(pOwner)->GetExplosions()[i]->UnActiveAttackBall();
			// range 이펙트 지우기
			m_vRangeEffect[i]->SetDeleteThis(true);
			// ring, cannon 이펙트 지우기
			m_vRingEffect[i]->SetDisappear(true);
		}
		m_vRingEffect.clear();
		m_vRangeEffect.clear();
	}
	// 내가 Arsenal End 상태가 끝났다면
	else if (Name_Arsenal_End == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// 대기 상태로 변경
		fsm->ChangeState(Name_IDLE);
		m_movedCenter = m_movedCorner = m_onRingEffect = m_onRangeEffect = false;
		m_effectIndex = 0;
		m_accTime = 0.f;
		m_onArsenalReadySound = false;
		m_onArsenalShotSound = false;
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(false);
	}

	/************************* Effect */
	// ring 이펙트를 순차적으로 생성한다.
	if (Name_Arsenal_Loop == fsm->GetCurStateString() &&
		0.25f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onRingEffect)
	{
		m_accTime += GET_DT;

		if (m_accTime >= 0.1f)
		{
			_int cnt = static_cast<CMB_Bronya*>(pOwner)->GetMaxArsenalEffectCnt();

			if (m_effectIndex < cnt)
			{
				SP(Engine::CObject) effect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Ult_Ring", true);
				effect->GetTransform()->SetPosition(static_cast<CMB_Bronya*>(pOwner)->GetRingEffectPos()[m_effectIndex]);
				m_vRingEffect.emplace_back(std::dynamic_pointer_cast<CBronya_Ult_Ring>(effect));
				++m_effectIndex;
			}
			else
			{
				m_onRingEffect = true;
				m_effectIndex = 0;
			}

			m_accTime = 0.f;
		}
	}

	// 모든 ring 이펙트를 생성 후 range 이펙트를 생성한다
	if (Name_Arsenal_Loop == fsm->GetCurStateString() &&
		true == m_onRingEffect &&
		false == m_onRangeEffect)
	{
		m_accTime += GET_DT;

		if (m_accTime >= 0.16f)
		{
			_int cnt = static_cast<CMB_Bronya*>(pOwner)->GetMaxArsenalEffectCnt();

			if (m_effectIndex < cnt)
			{
				SP(Engine::CObject) effect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Ult_Range", true);
				effect->GetTransform()->SetPosition(static_cast<CMB_Bronya*>(pOwner)->GetRangeEffectPos()[m_effectIndex]);
				effect->GetTransform()->SetSize(_float3(0.3f, 0.3f, 0.3f));
				m_vRangeEffect.emplace_back(std::dynamic_pointer_cast<CBronya_Ult_Range>(effect));
				++m_effectIndex;
			}
			else
			{
				m_onRangeEffect = true;
				m_effectIndex = 0;
			}

			m_accTime = 0.f;
		}
	}

	// 모든 이펙트가 생성된 후에 어택볼을 생성한다
	if (Name_Arsenal_Loop == fsm->GetCurStateString() &&
		true == m_onRangeEffect &&
		true == m_onRingEffect)
	{
		_int cnt = static_cast<CMB_Bronya*>(pOwner)->GetMaxArsenalEffectCnt();

		for (_int i = 0; i < cnt; ++i)
		{
			static_cast<CMB_Bronya*>(pOwner)->GetExplosions()[i]->SetIndex(i);
			static_cast<CMB_Bronya*>(pOwner)->GetExplosions()[i]->SetIsEnabled(true);
		}
	}

	if (true == m_onRingEffect &&
		true == m_onRangeEffect &&
		false == m_onArsenalShotSound)
	{
		// sound
		Engine::CSoundManager::GetInstance()->StopSound((_uint)EChannelID::OBJECT);
		Engine::CSoundManager::GetInstance()->StartSound(L"Bronya_Ult_Shot.wav", (_uint)EChannelID::OBJECT);
		m_onArsenalShotSound = true;
	}
} 

SP(CBronyaArsenalPattern) CBronyaArsenalPattern::Create()
{
	SP(CBronyaArsenalPattern) spInstance(new CBronyaArsenalPattern, Engine::SmartDeleter<CBronyaArsenalPattern>);

	return spInstance;
}

void CBronyaArsenalPattern::EscapePos(Engine::CObject* pOwner, SP(CFSM_BronyaC) spFSM, _float3 monPos, _float3 endPos, _bool& moved)
{
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos

	// 이스케이프 외 애니메이션이 종료되었다면
	if (Name_Escape_In != spFSM->GetCurStateString() &&
		Name_Escape_Out != spFSM->GetCurStateString() &&
		spFSM->GetDM()->IsAnimationEnd())
	{
		// escape in 실행
		spFSM->ChangeState(Name_Escape_Out);

		// effect
		SP(CBronya_Teleport_Ring) effect = std::dynamic_pointer_cast<CBronya_Teleport_Ring>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Teleport_Ring", true));
		effect->GetTransform()->SetPosition(mPos);
		effect->GetTransform()->AddPositionY(0.5f);


		m_vLaserOutEffect = std::dynamic_pointer_cast<CBronya_Teleport_Laser>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Teleport_Laser", true));
		m_vLaserOutEffect->GetTransform()->AddSizeX(-0.5f);
		m_vLaserOutEffect->GetTransform()->SetPosition(mPos);
		defaultEscapeEffectSizeX = m_vLaserOutEffect->GetTransform()->GetSize().x;
		m_onLaserOutEffect = true;

		// sound
		PatternPlaySound(L"Bronya_Teleport_Up.wav", pOwner);
	}
	// escape in 상태 중 적절한 위치로 올라왔다면
	else if (Name_Escape_Out == spFSM->GetCurStateString() &&
		0.76f <= spFSM->GetDM()->GetAniTimeline() &&
		0.f >= m_lerpCurTimer &&
		false == m_onEscape)
	{
		// 애니메이션 정지
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(0.05f);
		m_onEscape = true;

		// 센터로 이동
		m_lerpStartPos = monPos;
		m_lerpEndPos = _float3(endPos);
		m_lerpCurTimer = 0.f;
	}
	// escape in 상태 중 목표 위치로 이동 중이라면
	else if (Name_Escape_Out == spFSM->GetCurStateString() &&
		0.05f >= spFSM->GetDM()->GetAniCtrl()->GetSpeed() &&
		m_lerpCurTimer < m_lerpMaxTimer)
	{
		m_lerpCurTimer += GET_DT;

		if (m_lerpCurTimer >= m_lerpMaxTimer)
		{
			m_lerpCurTimer = m_lerpMaxTimer;
		}

		_float3 currentPos = GetLerpPosition(m_lerpStartPos, m_lerpEndPos, m_lerpCurTimer, 0.3f);
		pOwner->GetTransform()->SetPosition(currentPos);
	}
	// escape in 상태 중이면서 이동이 끝났다면
	else if (Name_Escape_Out == spFSM->GetCurStateString() &&
		m_lerpCurTimer <= m_lerpMaxTimer &&
		true == m_onEscape)
	{
		// 애니메이션 재생
		spFSM->ChangeState(Name_Escape_In);
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_onEscape = false;

		m_vLaserInEffect = std::dynamic_pointer_cast<CBronya_Teleport_Laser>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Teleport_Laser", true));
		m_vLaserInEffect->GetTransform()->AddSizeX(-0.5f);
		m_vLaserInEffect->GetTransform()->SetPosition(mPos);
		m_onLaserInEffect = true;

		// sound
		PatternPlaySound(L"Bronya_Teleport_Down.wav", pOwner);
	}
	// escape in 상태가 끝났다면
	else if (Name_Escape_In == spFSM->GetCurStateString() &&
		spFSM->GetDM()->IsAnimationEnd())
	{
		static_cast<CMB_Bronya*>(pOwner)->SetAlpha(1.f);
		std::dynamic_pointer_cast<CBronya_Weapon>(m_spWeapon)->SetAlpha(1.f);
		// 대기 상태로 변경
		spFSM->ChangeState(Name_IDLE);
		m_lerpCurTimer = 0.f;
		moved = true;

		pOwner->GetTransform()->SetRotationY(D3DXToRadian(180));
	}

	/************************* Effect */
	if (true == m_onLaserOutEffect)
	{
		_float sizeX = m_vLaserOutEffect->GetTransform()->GetSize().x - (1.5f * GET_DT);

		if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() > 0)
		{
			m_spWeapon = static_cast<CMB_Bronya*>(pOwner)->GetWeapon();
			static_cast<CMB_Bronya*>(pOwner)->SetAlpha(-5.3f * GET_DT);
			std::dynamic_pointer_cast<CBronya_Weapon>(m_spWeapon)->SetAlpha(-5.3f * GET_DT);

			if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() <= 0.f)
			{
				static_cast<CMB_Bronya*>(pOwner)->SetAlpha(0.f);
				std::dynamic_pointer_cast<CBronya_Weapon>(m_spWeapon)->SetAlpha(0.f);

			}

			_float alpha = static_cast<CMB_Bronya*>(pOwner)->GetAlpha();
		}

		if (0.f >= sizeX)
		{
			m_vLaserOutEffect->GetTransform()->SetSizeX(0.f);
		}
		else
		{
			m_vLaserOutEffect->GetTransform()->SetSizeX(sizeX);
		}

		if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() <= 0.f &&
			m_vLaserOutEffect->GetTransform()->GetSize().x <= 0.f)
		{
			m_onLaserOutEffect = false;
			m_vLaserOutEffect->SetDeleteThis(true);
		}
	}

	if (true == m_onLaserInEffect)
	{
		_float sizeX = m_vLaserInEffect->GetTransform()->GetSize().x - (3.5f * GET_DT);

		if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() <= 0.f)
		{
			static_cast<CMB_Bronya*>(pOwner)->SetAlpha(1.3f * GET_DT);

			if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() >= 1.f)
			{
				static_cast<CMB_Bronya*>(pOwner)->SetAlpha(1.f);
			}

			_float alpha = static_cast<CMB_Bronya*>(pOwner)->GetAlpha();
		}

		if (0.f >= sizeX)
		{
			m_vLaserInEffect->GetTransform()->SetSizeX(0.f);
		}
		else
		{
			m_vLaserInEffect->GetTransform()->SetSizeX(sizeX);
		}

		if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() >= 1.f &&
			m_vLaserOutEffect->GetTransform()->GetSize().x <= 0.f)
		{
			m_onLaserOutEffect = false;
			m_vLaserOutEffect->SetDeleteThis(true);
		}
	}
}

void CBronyaArsenalPattern::InitEffect()
{
	if (true == m_initEffect)
	{
		return;
	}

	//for (_int i = 0; i < m_maxRingCnt; ++i)
	//{
	//	m_vRingEffect.emplace_back(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Ult_Ring", true));
	//	m_vRingEffect[i]->GetTransform()->SetPosition(_float3(91.9447f, 0.5f, -8.55992f));
	//}

	//m_initEffect = false;
}
