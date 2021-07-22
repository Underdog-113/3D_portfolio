#include "stdafx.h"
#include "BronyaGrenade.h"

#include "MB_Bronya.h"
#include "AttackBall.h"

CBronyaGrenade::CBronyaGrenade()
{
}


CBronyaGrenade::~CBronyaGrenade()
{
	OnDestroy();
}

SP(CBronyaGrenade) CBronyaGrenade::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronyaGrenade) spInstance(new CBronyaGrenade, Engine::SmartDeleter<CBronyaGrenade>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronyaGrenade::MakeClone(void)
{
	SP(CBronyaGrenade) spClone(new CBronyaGrenade, Engine::SmartDeleter<CBronyaGrenade>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRigidBody	= spClone->GetComponent<Engine::CRigidBodyC>();

	return spClone;
}

void CBronyaGrenade::Awake(void)
{
	__super::Awake();
	m_dataID = (_int)EDataID::Enemy;
	m_layerID = (_int)ELayerID::Prop;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spShader		= AddComponent<Engine::CShaderC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
}

void CBronyaGrenade::Start(void)
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

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOwner(this);

	m_pBronya = static_cast<CMB_Bronya*>(Engine::GET_CUR_SCENE->FindObjectWithKey(L"MB_Bronya").get());
}

void CBronyaGrenade::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBronyaGrenade::Update(void)
{
	__super::Update();

	if (true == m_isEnabled)
	{
		m_grenadeMat = m_spTransform->GetWorldMatrix();

		//m_accTime += GET_DT;

		//if (m_accTime < m_maxTime)
		//{
		//	m_spTransform->AddPositionX(m_x * GET_DT * 1.2f);
		//	m_spTransform->AddPositionY(m_y * GET_DT * 1.2f);
		//	m_spTransform->AddPosition(m_dir * GET_DT * m_speed);
		//}
		//else
		//{
		//	UnActiveAttackBall();
		//	m_accTime = 0.f;
		//	m_isEnabled = false;
		//}

		//_float pos = m_spTransform->GetPosition().x * GET_DT * 1.f;
		//m_spTransform->AddPositionX(GET_DT * 1.f);
	}
}

void CBronyaGrenade::LateUpdate(void)
{
	__super::LateUpdate();

	//m_spTransform->SetLastWorldMatrix(*m_pParentMatrix);
}

void CBronyaGrenade::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CBronyaGrenade::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CBronyaGrenade::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CBronyaGrenade::OnDestroy(void)
{
	__super::OnDestroy();

	if (m_pAttackBall)
		m_pAttackBall->SetDeleteThis(true);

	delete m_pStat;
	m_pBronya = nullptr;
}
void CBronyaGrenade::OnEnable(void)
{
	__super::OnEnable();
}

void CBronyaGrenade::OnDisable(void)
{
	__super::OnDisable();
}

void CBronyaGrenade::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	//__super::OnCollisionEnter(ci);

	//////튕기는 총알
	//
	////중력 상수 세팅 코드
	//m_spRigidBody->SetGravityConstant(2.f);

	////최대 몇번 튕길건지를 변수로 저장
	//_int m_bounceCount = 2;

	////바닥이랑
	//if (ci.pMyCollider->GetColliderType() == (_int)Engine::EColliderType::Ray)
	//{
	//	if (ci.normal.y < -0.8f)
	//	{
	//		if (m_bounceCount > 0)
	//		{
	//			m_spRigidBody->AddForceY(0.2f);
	//			--m_bounceCount;
	//		}
	//		else
	//		{
	//			//터트림
	//			//enabled를 끄고 다시 초기세팅 해주고
	//			std::cout << "Boom" << std::endl;
	//		}
	//	}
	//	else
	//	{
	//		//터트림
	//		//enabled를 끄고 다시 초기세팅 해주고
	//		std::cout << "Boom" << std::endl;

	//		m_dir;
	//		m_speed;

	//	}
	//}
}

void CBronyaGrenade::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CBronyaGrenade::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CBronyaGrenade::SetBasicName(void)
{
}

void CBronyaGrenade::ActiveAttackBall(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat * pBoneMat, _float radius)
{
	HitInfo info;
	info.SetDamageRate(damageRate);
	info.SetStrengthType(strength);
	info.SetCrowdControlType(cc);

	m_pAttackBall->SetupBall(this, pBoneMat, radius, info);
	m_pAttackBall->SetIsEnabled(true);
}

void CBronyaGrenade::UnActiveAttackBall()
{
	m_pAttackBall->SetIsEnabled(false);
}
