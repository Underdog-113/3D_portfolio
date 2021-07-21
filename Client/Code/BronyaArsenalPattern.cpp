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

	// 1. ���ͷ� escape
	// 2. �������� escape
	// 3. ���� ����

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
		_float3 endPos = { 186.04f, mPos.y, -8.94f };
		EscapePos(pOwner, fsm, mPos, endPos, m_movedCenter);
	}

	/************************* Move Corner */
	if (true == m_movedCenter && false == m_movedCorner)
	{
		_float3 endPos = { 186.21f, mPos.y, -17.06f };
		EscapePos(pOwner, fsm, mPos, endPos, m_movedCorner);
	}

	/************************* Arsenal */
	// ���� ��� ���°� ������, corner�� �̵�������
	if (Name_IDLE == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onArsenal)
	{
		// Arsenal Charge ���·� ����
		fsm->ChangeState(Name_Arsenal_Charge);
	}
	// ���� Arsenal Charge ���°� �����ٸ�
	else if (Name_Arsenal_Charge == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// Arsenal Loop ���·� ����
		fsm->ChangeState(Name_Arsenal_Loop);
		m_atkReady = false;
		return;
	}
	// ���� Arsenal Loop�� ������, ��Ÿ�ӵ� �����ٸ�
	else if (Name_Arsenal_Loop == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		true == m_atkReady)
	{
		// Arsenal End ���·� ����
		fsm->ChangeState(Name_Arsenal_End);

		// ���ú� ����, range ����Ʈ �����
		_int cnt = static_cast<CMB_Bronya*>(pOwner)->GetMaxArsenalEffectCnt();
		for (_int i = 0; i < cnt; ++i)
		{
			// attackball ����
			static_cast<CMB_Bronya*>(pOwner)->GetExplosions()[i]->SetIsEnabled(false);
			static_cast<CMB_Bronya*>(pOwner)->GetExplosions()[i]->UnActiveAttackBall();
			// range ����Ʈ �����
			m_vRangeEffect[i]->SetDeleteThis(true);
			// ring, cannon ����Ʈ �����
			m_vRingEffect[i]->SetDisappear(true);
		}
		m_vRingEffect.clear();
		m_vRangeEffect.clear();
	}
	// ���� Arsenal End ���°� �����ٸ�
	else if (Name_Arsenal_End == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// ��� ���·� ����
		fsm->ChangeState(Name_IDLE);
		m_movedCenter = m_movedCorner = m_onRingEffect = m_onRangeEffect = false;
		m_effectIndex = 0;
		m_accTime = 0.f;
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}

	/************************* Effect */
	// ring ����Ʈ�� ���������� �����Ѵ�.
	if (Name_Arsenal_Loop == fsm->GetCurStateString() &&
		0.25f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onRingEffect)
	{
		m_accTime += GET_DT;

		if (m_accTime >= 0.12f)
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

	// ��� ring ����Ʈ�� ���� �� range ����Ʈ�� �����Ѵ�
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

	// ��� ����Ʈ�� ������ �Ŀ� ���ú��� �����Ѵ�
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
} 

SP(CBronyaArsenalPattern) CBronyaArsenalPattern::Create()
{
	SP(CBronyaArsenalPattern) spInstance(new CBronyaArsenalPattern, Engine::SmartDeleter<CBronyaArsenalPattern>);

	return spInstance;
}

void CBronyaArsenalPattern::EscapePos(Engine::CObject* pOwner, SP(CFSM_BronyaC) spFSM, _float3 monPos, _float3 endPos, _bool& moved)
{
	// �̽������� �� �ִϸ��̼��� ����Ǿ��ٸ�
	if (Name_Escape_In != spFSM->GetCurStateString() &&
		Name_Escape_Out != spFSM->GetCurStateString() &&
		spFSM->GetDM()->IsAnimationEnd())
	{
		// escape in ����
		spFSM->ChangeState(Name_Escape_Out);
	}
	// escape in ���� �� ������ ��ġ�� �ö�Դٸ�
	else if (Name_Escape_Out == spFSM->GetCurStateString() &&
		0.76f <= spFSM->GetDM()->GetAniTimeline() &&
		0.f >= m_lerpCurTimer &&
		false == m_onEscape)
	{
		// �ִϸ��̼� ����
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(0.05f);
		m_onEscape = true;

		// ���ͷ� �̵�
		m_lerpStartPos = monPos;
		m_lerpEndPos = _float3(endPos);
		m_lerpCurTimer = 0.f;
	}
	// escape in ���� �� ��ǥ ��ġ�� �̵� ���̶��
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
	// escape in ���� ���̸鼭 �̵��� �����ٸ�
	else if (Name_Escape_Out == spFSM->GetCurStateString() &&
		m_lerpCurTimer <= m_lerpMaxTimer &&
		true == m_onEscape)
	{
		// �ִϸ��̼� ���
		spFSM->ChangeState(Name_Escape_In);
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_onEscape = false;
	}
	// escape in ���°� �����ٸ�
	else if (Name_Escape_In == spFSM->GetCurStateString() &&
		spFSM->GetDM()->IsAnimationEnd())
	{
		// ��� ���·� ����
		spFSM->ChangeState(Name_IDLE);
		m_lerpCurTimer = 0.f;
		moved = true;

		pOwner->GetTransform()->SetRotationY(D3DXToRadian(180));
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
