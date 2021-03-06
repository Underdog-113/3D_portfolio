#include "stdafx.h"
#include "..\Header\Monster.h"

#include "AttackBall.h"
#include "AttackBox.h"
#include "ClientScene.h"
#include "Sakura_DamageMark.h"
#include "ItemObject.h"
#include "Stun_Eff.h"

_uint CMonster::m_s_channelID = 0;

CMonster::CMonster()
{
}

SP(Engine::CObject) CMonster::MakeClone(void)
{
	return SP(CObject)();
}

void CMonster::Awake(void)
{
	__super::Awake();

	m_dataID = (_int)EDataID::Enemy;
	m_layerID = (_int)ELayerID::Enemy;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spShader		= AddComponent<Engine::CShaderC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();

	m_spRigidBody = AddComponent<Engine::CRigidBodyC>();
	m_spCollision = AddComponent<Engine::CCollisionC>();
	m_spDebug = AddComponent<Engine::CDebugC>();

	m_spPatternMachine = AddComponent<CPatternMachineC>();
}

void CMonster::Start(void)
{
	__super::Start();

	if (!m_pStat)
	{
		BaseStat stat;
		stat.SetBaseHp(321.f);
		stat.SetBaseAtk(60.f);
		stat.SetBaseDef(22.f);

		stat.SetGrowHp(10.f);
		stat.SetGrowAtk(1.2f);
		stat.SetGrowDef(1.f);

		stat.SetType(BaseStat::Mecha);

		m_pStat = new M_Stat;
		m_pStat->SetupStatus(&stat);
		m_pSuperArmor = new M_SuperArmor;
	}
	
	// select ChannelID for Sound
	SelectChannelID();
}

void CMonster::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMonster::Update(void)
{
	__super::Update();

	if (false == m_pStat->GetOnSuperArmor())
	{
		m_accTime += GET_DT;

		if (m_accTime >= m_weakTime)
		{
			m_pStat->SetOnSuperArmor(true);
			m_pStat->SetCurBreakGauge(m_pStat->GetMaxBreakGauge());
			m_accTime = 0.f;
		}
	}
}

void CMonster::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMonster::OnDestroy(void)
{
	__super::OnDestroy();
	
	ReturnChannelID();
	SAFE_DELETE(m_pStat);
	SAFE_DELETE(m_pSuperArmor);

	if(m_pAttackBall)
		m_pAttackBall->SetDeleteThis(true);
	if (m_pAttackBox)
		m_pAttackBox->SetDeleteThis(true);

	if (EChannelID::MONSTER_0 == m_channelID)
	{
		m_s_channelID ^= EMonChID::MON_0;
	}
	else if (EChannelID::MONSTER_1 == m_channelID)
	{
		m_s_channelID ^= EMonChID::MON_1;
	}
	else if (EChannelID::MONSTER_2 == m_channelID)
	{
		m_s_channelID ^= EMonChID::MON_2;
	}
	else if (EChannelID::MONSTER_3 == m_channelID)
	{
		m_s_channelID ^= EMonChID::MON_3;
	}
	else if (EChannelID::MONSTER_4 == m_channelID)
	{
		m_s_channelID ^= EMonChID::MON_4;
	}
}

void CMonster::OnEnable(void)
{
	__super::OnEnable();
}

void CMonster::OnDisable(void)
{
	__super::OnDisable();
}

void CMonster::SetBasicName(void)
{
}
void CMonster::ApplyHitInfo(HitInfo info)
{
	// ?????? ????
	if (info.GetCrowdControlType() == HitInfo::CrowdControl::CC_Sakura)
	{
		if (m_pStat->GetSakuraCounter() < 3)
		{
			m_pStat->SetSakuraCounter(m_pStat->GetSakuraCounter() + 1);

			if (m_pStat->GetSakuraCounter() == 3)
			{
				AttachSakuraMark();
			}
		}

	}

	// Break Point ?????? ??????????
	if (false == m_pStat->GetOnBPShield())
	{
		_float breakGauge = m_pStat->GetCurBreakGauge() - info.GetBreakDamage();

		if (breakGauge <= 0.f)
		{
			breakGauge = 0.f;
			m_pStat->SetOnSuperArmor(false);
		}
		m_pStat->SetCurBreakGauge(breakGauge);
	}
}

void CMonster::AttachSakuraMark()
{
	if (!m_pStat->GetSakuraMark())
	{
		SP(Engine::CObject) spObj;
		spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Sakura_DamageMark", true, (_uint)Engine::ELayerID::Effect);
		//spObj->GetTransform()->SetParent(m_spTransform);
		static_cast<CSakura_DamageMark*>(spObj.get())->SetTargetObject(this);

		//spObj->GetTransform()->SetSize(5.f, 5.f, 5.f);
		m_pStat->SetSakuraMark(spObj);

		m_spSakuraMark = spObj;
	}
}

void CMonster::AttachStunMark()
{
	if (!m_pStat->GetStunMark())
	{
		SP(Engine::CObject) spObj;
		spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Stun_Eff", true, (_uint)Engine::ELayerID::Effect);
		static_cast<CStun_Eff*>(spObj.get())->SetTargetObject(this);

		m_pStat->SetStunMark(spObj);
	}
}

void CMonster::DettachStunMark()
{
	if (m_pStat->GetStunMark())
	{
		m_pStat->GetStunMark()->SetDeleteThis(true);
		m_pStat->SetStunMark(nullptr);
	}
}

void CMonster::ActiveAttackBall(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat * pBoneMat, _float radius)
{
	HitInfo info;
	info.SetDamageRate(damageRate);
	info.SetStrengthType(strength);
	info.SetCrowdControlType(cc);
	
	m_pAttackBall->SetupBall(this, pBoneMat, radius, info);
	m_pAttackBall->SetIsEnabled(true);
}

void CMonster::UnActiveAttackBall()
{
	m_pAttackBall->SetIsEnabled(false);
}

void CMonster::ActiveAttackBall(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat * pBoneMat, _float radius, CAttackBall * pAB)
{
	HitInfo info;
	info.SetDamageRate(damageRate);
	info.SetStrengthType(strength);
	info.SetCrowdControlType(cc);

	pAB->SetupBall(this, pBoneMat, radius, info);
	pAB->SetIsEnabled(true);
}

void CMonster::UnActiveAttackBall(CAttackBall * pAB)
{
	pAB->SetIsEnabled(false);
}

void CMonster::ActiveAttackBox(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat * pBoneMat, _float3 size, _float3 offset, _float3 rotOffset)
{
	HitInfo info;
	info.SetDamageRate(damageRate);
	info.SetStrengthType(strength);
	info.SetCrowdControlType(cc);

	m_pAttackBox->SetupBox(this, pBoneMat, size, offset, rotOffset, info);
	m_pAttackBox->SetIsEnabled(true);
}

void CMonster::UnActiveAttackBox()
{
	m_pAttackBox->SetIsEnabled(false);
}

void CMonster::MonsterDead()
{
	SP(Engine::CObject) item = GET_CUR_CLIENT_SCENE->GetObjectFactory()->AddClone(L"ItemObject", true, (_uint)ELayerID::Enemy, L"Object");
	_float3 pos = GetTransform()->GetPosition();
	pos.y += 0.3f;
	item->GetTransform()->SetPosition(pos);
	item->GetTransform()->SetSize(_float3(0.7f, 0.7f, 0.7f));

	_int randValue = rand() % 4;

	switch (randValue)
	{
	case 0:
		item->AddComponent<CStuffItemC>()->AddDataInit(ItemSave(L"???? ???? ??", 1), 50);
		break;
	case 1:
		item->AddComponent<CStuffItemC>()->AddDataInit(ItemSave(L"???? ???? ??", 1), 50);
		break;
	case 2:
		item->AddComponent<CStuffItemC>()->AddDataInit(ItemSave(L"???? ???? ??", 1), 50);
		break;
	case 3:
		item->AddComponent<CStuffItemC>()->AddDataInit(ItemSave(L"???? ??????", 1), 50);
		break;
	}

	if(m_spSakuraMark)
		m_spSakuraMark->SetDeleteThis(true);
}

void CMonster::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0;
	D3DXVec3Normalize(&dir, &dir);

	_float3 curForward = m_spTransform->GetForward();
	_float dotTwoForward = D3DXVec3Dot(&dir, &curForward);
	dotTwoForward = GET_MATH->RoundOffRange(dotTwoForward, 1);
	_float includedAngle = acos(dotTwoForward);

	if (abs(includedAngle) > m_spTransform->GetSlerpSpeed() * 2 * GET_DT)
	{
		m_spTransform->SetGoalForward(dir);
		m_spTransform->SetSlerpOn(true);
	}

	
	//m_spTransform->SetForwardUp(dir, UP_VECTOR);
}

void CMonster::AddEffect(SP(Engine::CObject) effect)
{
	m_vEffects.emplace_back(effect);
}

void CMonster::DeleteEffect(_int index)
{
	auto& iter = m_vEffects.begin();

	for (int i = 0; i < m_vEffects.size(); ++i)
	{
		if (index == i)
		{
			iter = m_vEffects.erase(iter);
			break;
		}
		++iter;
	}
}

Engine::CCollider * CMonster::GetHitBox()
{
	auto cols = m_spCollision->GetColliders();
	for (auto col : cols)
	{
		if (col->GetCollisionID() == (_uint)ECollisionID::EnemyHitBox)
		{
			return col.get();
		}
	}
	return nullptr;
}

void CMonster::SelectChannelID()
{
	if (!(m_s_channelID & EMonChID::MON_0))
	{
		m_channelID = EChannelID::MONSTER_0;
		m_s_channelID |= EMonChID::MON_0;
	}
	else if (!(m_s_channelID & EMonChID::MON_1))
	{
		m_channelID = EChannelID::MONSTER_1;
		m_s_channelID |= EMonChID::MON_1;
	}
	else if(!(m_s_channelID & EMonChID::MON_2))
	{
		m_channelID = EChannelID::MONSTER_2;
		m_s_channelID |= EMonChID::MON_2;
	}
	else if (!(m_s_channelID & EMonChID::MON_3))
	{
		m_channelID = EChannelID::MONSTER_3;
		m_s_channelID |= EMonChID::MON_3;
	}
	else if (!(m_s_channelID & EMonChID::MON_4))
	{
		m_channelID = EChannelID::MONSTER_4;
		m_s_channelID |= EMonChID::MON_4;
	}
}

void CMonster::ReturnChannelID()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)m_channelID);
}

/*
0000 0001 1
0000 0010 2
0000 0100 4
0000 1000 8
0001 0000 16

0000 1001

*/