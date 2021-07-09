#include "stdafx.h"
#include "RobotBasePattern.h"

#include "FSM_RobotC.h"
#include "FSMDefine_Robot.h"
#include "MO_Robot.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "AttackBall.h"
#include "AniCtrl.h"

CRobotBasePattern::CRobotBasePattern()
{
}

CRobotBasePattern::~CRobotBasePattern()
{
}

void CRobotBasePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_RobotC) fsm = pOwner->GetComponent<CFSM_RobotC>();

	if (nullptr == fsm || false == fsm->GetDM())
		return;

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	if (Name_Attack_1_Left != fsm->GetCurStateString())
	{
		static_cast<CMO_Robot*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Range */
	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
 		// ���� ����1 ���°� �����ٸ�
 		if (Name_Attack_1_Left == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
 		{
 			fsm->ChangeState(Name_Walk_Backward);
 		}
		// ���� ��� ���°� �����ٸ�
		else if (Name_StandBy == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Forward);
		}
		// ���� �̵� ���̶��
		else if (Name_Walk_Forward == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// ���� �ڷ� �̵� ���̶��
		else if (Name_Walk_Backward == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			false == m_walkReady)
		{
			_float3 dir = tPos - mPos;

			mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// ���� �ڷ� �̵��� �����ٸ�
		else if (Name_Walk_Backward == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			true == m_walkReady)
		{
			fsm->ChangeState(Name_Walk_Forward);
			pOwner->GetComponent<CPatternMachineC>()->SetOnBase(false);
		}
	}
	// ��밡 ���� ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵�, ��� ���°� �����ٸ�
		if ((Name_Walk_Forward == fsm->GetCurStateString() ||
			Name_StandBy == fsm->GetCurStateString()) &&
			/*0.9f <= fsm->GetDM()->GetAniTimeline()*/
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Attack_1_Left);
			m_onEffect = false;
			m_onAttackball = false;
			return;
		}
		// ���� ����1 ���°� �����ٸ�
		else if (Name_Attack_1_Left == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Backward);
			m_walkReady = false;
		}
	}

	/************************* AttackBall */
	// ���� ���� ���°�, ������ �� ���ú� �����
	if (Name_Attack_1_Left == fsm->GetCurStateString() &&
		0.47f <= fsm->GetDM()->GetAniTimeline() &&
		0.49f > fsm->GetDM()->GetAniTimeline() &&
		true == m_onAttackball)
	{
		static_cast<CMO_Robot*>(pOwner)->UnActiveAttackBall();
	}
	// ���� ���� ���°�, ������ �� ���ú� ����
	else if (Name_Attack_1_Left == fsm->GetCurStateString() &&
		0.37f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onAttackball)
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
		D3DXVec3Normalize(&look, &look);

		m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		m_atkMat._41 += (m_atkDis * look.x / 1.7f);
		m_atkMat._43 += (m_atkDis * look.z / 1.7f);

		static_cast<CMO_Robot*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.4f);

		m_onAttackball = true;
	}
	
	/************************* Effect */
	// ���� attack_1_left �� ������ ����
	if (Name_Attack_1_Left == fsm->GetCurStateString() &&
		0.32f <= fsm->GetDM()->GetAniTimeline() &&
		0.34f > fsm->GetDM()->GetAniTimeline() &&
		false == m_onEffect)
	{
		m_spHookEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"RobotHookEff", true);
		m_spHookEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"RobotHook");
		m_spHookEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"RobotHook");
		m_spHookEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
		m_spHookEffect->GetTransform()->SetSize(2.f, 2.f, 2.f);

		// �ָ� �� ã��
		m_pLeftUpperArm = &fsm->GetDM()->GetFrameByName("Bip001_L_Hand")->CombinedTransformMatrix;

		m_onEffect = true;
	}
	// ���� attack_1_left ���� ���̶��
	else if (Name_Attack_1_Left == fsm->GetCurStateString() &&
		true == m_onEffect)
	{
		_mat combMat = *m_pLeftUpperArm;
		_float3 rootMotionPos = pOwner->GetComponent<Engine::CMeshC>()->GetRootMotionPos();
		combMat._41 -= rootMotionPos.x;
		combMat._43 -= rootMotionPos.z;

		_mat realPosMat = combMat * pOwner->GetTransform()->GetWorldMatrix();

		_mat wMat = pOwner->GetTransform()->GetWorldMatrix();
		_float3 right = { wMat._11, wMat._12, wMat._13 };
		D3DXVec3Normalize(&right, &right);
		_float3 pos = { realPosMat._41, realPosMat._42, realPosMat._43 };
		m_spHookEffect->GetTransform()->SetPosition(pos - (right * 1.3f));
	}
}

SP(CRobotBasePattern) CRobotBasePattern::Create()
{
	SP(CRobotBasePattern) spInstance(new CRobotBasePattern, Engine::SmartDeleter<CRobotBasePattern>);

	return spInstance;
}