#include "stdafx.h"
#include "BronyaGrenade.h"

#include "MB_Bronya.h"
#include "AttackBall.h"

#include "Bronya_Grenade.h"

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
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug		= spClone->GetComponent<Engine::CDebugC>();

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
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	m_spRigidBody	= AddComponent<Engine::CRigidBodyC>();
	m_spDebug		= AddComponent<Engine::CDebugC>();
}

void CBronyaGrenade::Start(void)
{
	__super::Start();

	if (!m_pStat)
	{
		BaseStat stat;
		stat.SetBaseHp(100.f);
		stat.SetBaseAtk(128.f);
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

	if (true == m_isEnabled && true == m_onBoomReady)
	{
		switch (index)
		{
		case 0:
			m_spTransform->AddPositionX(GET_DT * -1.8f);
			m_spTransform->AddPosition(m_dir * GET_DT * 5.f);
			break;
		case 1:
			m_spTransform->AddPosition(m_dir * GET_DT * 3.f);
			break;
		case 2:
			m_spTransform->AddPositionX(GET_DT * 1.2f);
			m_spTransform->AddPosition(m_dir * GET_DT * 4.f);
			break;
		}
	}

	if (false == m_onBoomReady)
	{
		m_accTime += GET_DT;

		if (m_accTime >= 1.4f &&
			true == m_onAttackBall)
		{
			m_accTime = 0.f;

			UnActiveAttackBall();
			m_bounceCount = 2;
			m_onAttackBall = false;
			m_onBoomReady = true;
			m_isEnabled = false;

			std::cout << "End" << std::endl;
		}
		else if (m_accTime >= 1.3f &&
			false == m_onAttackBall)
		{
			
			m_onAttackBall = true;

			std::cout << "Boom!" << std::endl;

			m_grenadeMat = m_spTransform->GetWorldMatrix();
			ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_grenadeMat, 0.55f);

			// boom effect
			std::cout << "Effect!" << std::endl;
			SP(Engine::CObject) effect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Grenade", true);
			effect->GetTransform()->SetPosition(m_spTransform->GetPosition());
		}
		
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
	__super::OnCollisionEnter(ci);

	////튕기는 총알
	
	//중력 상수 세팅 코드
	m_spRigidBody->SetGravityConstant(2.f); 

	//바닥이랑 충돌
	if (ci.pMyCollider->GetColliderType() == (_int)Engine::EColliderType::Ray)
	{
		if (ci.normal.y < -0.5f)
		{
			if (m_bounceCount > 1)
			{
				m_spRigidBody->SetVelocityY(5.5f);
				--m_bounceCount;
				//std::cout << "AddForceY" << std::endl;
			}
			else if (m_bounceCount > 0)
			{
				m_spRigidBody->SetVelocityY(3.5f);
				--m_bounceCount;
				//std::cout << "AddForceY" << std::endl;
			}
			else
			{
				//enabled를 끄고 다시 초기세팅 해주고
				TurnOffRigidbodyCollisionSetting();
				m_onBoomReady = false;
			}
		}
		else
		{
			//enabled를 끄고 다시 초기세팅 해주고
			TurnOffRigidbodyCollisionSetting();
			m_onBoomReady = false;
		}
	}
}

void CBronyaGrenade::OnCollisionStay(Engine::_CollisionInfo ci)
{
	__super::OnCollisionStay(ci);

	if (ci.pMyCollider->GetColliderType() == (_int)Engine::EColliderType::Ray)
	{
		std::cout << "충돌 중" << std::endl;
	}
}

void CBronyaGrenade::OnCollisionExit(Engine::_CollisionInfo ci)
{
	__super::OnCollisionExit(ci);

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

void CBronyaGrenade::TurnOffRigidbodyCollisionSetting()
{
	m_spRigidBody->SetVelocity(ZERO_VECTOR);
	m_spRigidBody->SetForce(ZERO_VECTOR);
	m_spRigidBody->SetUseGravity(false);
	m_spRigidBody->SetIsEnabled(false);
	m_spCollision->SetIsEnabled(false);
}
