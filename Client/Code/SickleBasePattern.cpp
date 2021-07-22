#include "stdafx.h"
#include "SickleBasePattern.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "AttackBall.h"

CSickleBasePattern::CSickleBasePattern()
{
}

CSickleBasePattern::~CSickleBasePattern()
{
}

void CSickleBasePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_SickleC) fsm = pOwner->GetComponent<CFSM_SickleC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// ���� ����1 ���°� �ƴ϶�� ��� ����
	if (Name_Sickle_Attack_1 != fsm->GetCurStateString())
	{
		static_cast<CMO_Sickle*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Range */
	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� ����1 ���°� �����ٸ�
		if (Name_Sickle_Attack_1 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// �ڷ� �̵�
			fsm->ChangeState(Name_Sickle_Walk_Back);
		}
		// ���� ��� ���°� �����ٸ�
		else if (Name_Sickle_StandBy == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// ������ �̵�
			fsm->ChangeState(Name_Sickle_Walk_Forward);
		}
		// ���� �ڷ� �̵��� �����ٸ�
		else if (Name_Sickle_Walk_Back == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			true == m_walkReady)
		{
			// ������ �̵�
			fsm->ChangeState(Name_Sickle_Walk_Forward);
			pOwner->GetComponent<CPatternMachineC>()->SetOnBase(false);
		}
	}
	// ��밡 ���� ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵�, ��� ���°� �����ٸ�,
		if ((Name_Sickle_Walk_Forward == fsm->GetCurStateString() ||
			Name_Sickle_StandBy == fsm->GetCurStateString() ||
			Name_Sickle_Walk_Back == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// ����1 �� �ٿ� ���̶�� ���
			if (false == m_atkReady)
			{
				fsm->ChangeState(Name_Sickle_StandBy);
			}
			// ����1 �� �ٿ��� �����ٸ�
			else if (true == m_atkReady)
			{
				// ����1 ���·� ����
				fsm->ChangeState(Name_Sickle_Attack_1);
				m_atkReady = false;
				m_onSignEffect = false;
				m_onTrailEffect = false;
				PatternPlaySound(L"Sickle_Skill_0.wav", pOwner);
				static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(true);
				return;
			}
		}
		// ����1 ���°� �����ٸ�
		else if (Name_Sickle_Attack_1 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// �ڷ� �̵�
			fsm->ChangeState(Name_Sickle_Walk_Back);
			static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(false);
		}
	}

	/************************* AttackBall */
	// ���� ���� ���°�, ������ �� ���ú� �����
	if (Name_Sickle_Attack_1 == fsm->GetCurStateString() &&
		0.47f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMO_Sickle*>(pOwner)->UnActiveAttackBall();
	}
	// ���� ���� ���°�, ������ �� ���ú� ����
	else if (Name_Sickle_Attack_1 == fsm->GetCurStateString() &&
		0.37f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
		D3DXVec3Normalize(&look, &look);

		m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		m_atkMat._41 += (m_atkDis * look.x / 2.2f);
		m_atkMat._43 += (m_atkDis * look.z / 2.2f);

		static_cast<CMO_Sickle*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.28f);
	}

	/************************* Effect */
	if (Name_Sickle_Attack_1 == fsm->GetCurStateString() &&
		0.1f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onSignEffect)
	{
		m_spSignEffect
			= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MonsterAttackSign", true);		
		m_spSignEffect->GetTransform()->SetPosition(mPos);
		m_spSignEffect->GetTransform()->SetPositionY(mPos.y + 0.6f);
		m_onSignEffect = true;
	}

	if (Name_Sickle_Attack_1 == fsm->GetCurStateString() &&
		0.3f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onTrailEffect)
	{
		SP(Engine::CObject) spMeshEffect
			= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Sickle_Trail", true, (_int)Engine::ELayerID::Effect, L"MeshEffect0");
		spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(L"Sickle_Attack");
		spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::Effect);
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"BloomMask");
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"AttackTrail_01");
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Eff_Noise_08");
		spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::MeshTrailShader);
		//spMeshEffect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
		spMeshEffect->GetTransform()->SetRotation(pOwner->GetTransform()->GetRotation());
		spMeshEffect->GetTransform()->AddRotationY(PI);
		spMeshEffect->GetTransform()->SetPosition(mPos);
		spMeshEffect->GetTransform()->SetSize(0.6f, 0.6f, 0.6f);
		m_onTrailEffect = true;
	}
}

SP(CSickleBasePattern) CSickleBasePattern::Create()
{
	SP(CSickleBasePattern) spInstance(new CSickleBasePattern, Engine::SmartDeleter<CSickleBasePattern>);

	return spInstance;
}