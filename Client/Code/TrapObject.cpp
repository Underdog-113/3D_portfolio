#include "stdafx.h"
#include "TrapObject.h"

#include "DecoObject.h"
#include "MapObject.h"
#include "AttackBall.h"

_uint CTrapObject::m_s_uniqueID = 0;
CTrapObject::CTrapObject()
{
}


CTrapObject::~CTrapObject()
{
	OnDestroy();
}

SP(CTrapObject) CTrapObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTrapObject) spInstance(new CTrapObject, Engine::SmartDeleter<CTrapObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTrapObject::MakeClone(void)
{
	SP(CTrapObject) spClone(new CTrapObject, Engine::SmartDeleter<CTrapObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CTrapObject::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Map;
	m_dataID	= UNDEFINED;

	m_addExtra = true;
}

void CTrapObject::Start(void)
{
	__super::Start();

	if (!m_pStat)
	{
		BaseStat stat;
		stat.SetBaseHp(100.f);
		stat.SetBaseAtk(35.f);
		stat.SetBaseDef(1.f);

		stat.SetGrowHp(1.f);
		stat.SetGrowAtk(1.f);
		stat.SetGrowDef(1.f);

		m_pStat = new M_Stat;
		m_pStat->SetupStatus(&stat);
	}
	
	m_spPlate = std::dynamic_pointer_cast<CDecoObject>(m_pScene->GetObjectFactory()->AddClone(L"DecoObject", true));
	m_spPlate->SetDataID((_int)EDataID::Scene);
	m_spPlate->GetComponent<Engine::CMeshC>()->SetMeshData(L"trap_plate");
	m_spPlate->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_spPlate->GetComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	m_spPlate->GetComponent<Engine::CTextureC>()->AddTexture(L"Spike");
	m_spPlate->GetTransform()->SetPosition(m_spTransform->GetPosition());

	m_spNiddle = std::dynamic_pointer_cast<CMapObject>(m_pScene->GetObjectFactory()->AddClone(L"MapObject", true));
	m_spNiddle->SetDataID((_int)EDataID::Scene);
	m_spNiddle->GetComponent<Engine::CMeshC>()->SetMeshData(L"trap_niddle");
	m_spNiddle->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_spNiddle->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	m_spNiddle->GetComponent<Engine::CTextureC>()->AddTexture(L"Spike");
	m_spNiddle->GetTransform()->SetPosition(m_spTransform->GetPosition());

	m_spTop = std::dynamic_pointer_cast<CDecoObject>(m_pScene->GetObjectFactory()->AddClone(L"DecoObject", true));
	m_spTop->SetDataID((_int)EDataID::Scene);
	m_spTop->GetComponent<Engine::CMeshC>()->SetMeshData(L"trap_top");
	m_spTop->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_spTop->GetComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	m_spTop->GetComponent<Engine::CTextureC>()->AddTexture(L"Spike");
	m_spTop->GetTransform()->SetPosition(m_spTransform->GetPosition());

	m_spBottom = std::dynamic_pointer_cast<CDecoObject>(m_pScene->GetObjectFactory()->AddClone(L"DecoObject", true));
	m_spBottom->SetDataID((_int)EDataID::Scene);
	m_spBottom->GetComponent<Engine::CMeshC>()->SetMeshData(L"trap_bottom");
	m_spBottom->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_spBottom->GetComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	m_spBottom->GetComponent<Engine::CTextureC>()->AddTexture(L"Spike");
	m_spBottom->GetTransform()->SetPosition(m_spTransform->GetPosition());

	m_initPos = m_spNiddle->GetTransform()->GetPosition();

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOwner(this);
	m_pAttackBall->Start();
}

void CTrapObject::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CTrapObject::Update(void)
{
	__super::Update();
	
	TrapAnimation();
}

void CTrapObject::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CTrapObject::PreRender(LPD3DXEFFECT pEffect)
{
}

void CTrapObject::Render(LPD3DXEFFECT pEffect)
{
}

void CTrapObject::PostRender(LPD3DXEFFECT pEffect)
{
}

void CTrapObject::OnDestroy(void)
{
	__super::OnDestroy();
	
	delete m_pStat;
}

void CTrapObject::OnEnable(void)
{
	__super::OnEnable();
	
}

void CTrapObject::OnDisable(void)
{
	__super::OnDisable();
	
}

void CTrapObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CTrapObject::TrapAnimation(void)
{
	/* niddle */
	if (true == m_onUp)
	{
		m_atkMat = m_spNiddle->GetTransform()->GetWorldMatrix();

		m_accTime += GET_DT;

		if (m_accTime >= m_maxTime)
		{
			UnActiveAttackBall();
			m_accTime = 0.f;
			m_onUp = false;
			m_onDown = true;

			m_onTop = false;
			m_onBottom = false;
		}
	}
	else if (true == m_onDown)
	{
		m_accTime += GET_DT;

		if (m_accTime >= m_maxTime)
		{
			ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.21f);
			m_accTime = 0.f;
			m_onUp = true;
			m_onDown = false;

			m_onTop = true;
			m_onBottom = true;
		}
	}

	if (true == m_onUp)
	{
		m_spNiddle->GetTransform()->SetLerpOn(true);
		m_spNiddle->GetTransform()->SetGoalPosition(_float3(m_initPos.x, m_initPos.y + 0.35f, m_initPos.z));
	}
	else if (true == m_onDown)
	{
		m_spNiddle->GetTransform()->SetLerpOn(true);
		m_spNiddle->GetTransform()->SetGoalPosition(_float3(m_initPos.x, m_initPos.y, m_initPos.z));
	}

	/* Top */
	if (true == m_onTop)
	{
		m_spTop->GetTransform()->SetLerpOn(true);
		m_spTop->GetTransform()->SetGoalPosition(_float3(m_initPos.x - 0.04f, m_initPos.y - 0.001f, m_initPos.z + 0.04f));
	}
	else if (false == m_onTop)
	{
		m_spTop->GetTransform()->SetLerpOn(true);
		m_spTop->GetTransform()->SetGoalPosition(_float3(m_initPos.x, m_initPos.y - 0.001f, m_initPos.z));
	}

	/* Bottom */
	if (true == m_onBottom)
	{
		m_spBottom->GetTransform()->SetLerpOn(true);
		m_spBottom->GetTransform()->SetGoalPosition(_float3(m_initPos.x + 0.04f, m_initPos.y - 0.001f, m_initPos.z - 0.04f));
	}
	else if (false == m_onBottom)
	{
		m_spBottom->GetTransform()->SetLerpOn(true);
		m_spBottom->GetTransform()->SetGoalPosition(_float3(m_initPos.x, m_initPos.y - 0.001f, m_initPos.z));
	}
}

void CTrapObject::ActiveAttackBall(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat * pBoneMat, _float radius)
{
	HitInfo info;
	info.SetDamageRate(damageRate);
	info.SetStrengthType(strength);
	info.SetCrowdControlType(cc);

	m_pAttackBall->SetupBall(this, pBoneMat, radius, info);
	m_pAttackBall->SetIsEnabled(true);
}

void CTrapObject::UnActiveAttackBall(void)
{
	m_pAttackBall->SetIsEnabled(false);
}
