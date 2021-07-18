#include "stdafx.h"
#include "BronyaBullet.h"

#include "AttackBall.h"

CBronyaBullet::CBronyaBullet()
{
}


CBronyaBullet::~CBronyaBullet()
{
	OnDestroy();
}

SP(CBronyaBullet) CBronyaBullet::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronyaBullet) spInstance(new CBronyaBullet, Engine::SmartDeleter<CBronyaBullet>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronyaBullet::MakeClone(void)
{
	SP(CBronyaBullet) spClone(new CBronyaBullet, Engine::SmartDeleter<CBronyaBullet>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronyaBullet::Awake(void)
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

void CBronyaBullet::Start(void)
{
	__super::Start();

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOwner(this);
}

void CBronyaBullet::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBronyaBullet::Update(void)
{
	__super::Update();

	// �Ѿ��� Ȱ��ȭ�Ǹ� Ÿ�̸� ����
	if (true == m_isEnabled)
	{
		m_bulletMat = m_spTransform->GetWorldMatrix();

		ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_bulletMat, 0.17f);

		if (0.f >= m_accTime)
		{
			m_spTransform->AddPositionY(0.2f);
			m_x = (_float)(rand() % 25) / 10;
			m_y = (_float)(rand() % 16) / 10;

			_int sign = GetRandRange(1, 4);

			switch (sign)
			{
			case 1:
				break;
			case 2:
				m_x *= -1;
				break;
			case 3:
				m_y *= -1;
				break;
			case 4:
				m_x *= -1;
				m_y *= -1;
				break;
			}
		}

		m_accTime += GET_DT;

		if (m_accTime < m_maxTime)
		{
			m_spTransform->AddPositionX(m_x * GET_DT * 1.2f);
			m_spTransform->AddPositionY(m_y * GET_DT * 1.2f);
			m_spTransform->AddPosition(m_dir * GET_DT * m_speed);
		}
		else
		{
			UnActiveAttackBall();
			m_accTime = 0.f;
			m_isEnabled = false;
		}
	}
}

void CBronyaBullet::LateUpdate(void)
{
	__super::LateUpdate();

	//m_spTransform->SetLastWorldMatrix(*m_pParentMatrix);
}

void CBronyaBullet::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CBronyaBullet::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CBronyaBullet::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CBronyaBullet::OnDestroy(void)
{
	__super::OnDestroy();

	if (m_pAttackBall)
		m_pAttackBall->SetDeleteThis(true);
}
void CBronyaBullet::OnEnable(void)
{
	__super::OnEnable();
}

void CBronyaBullet::OnDisable(void)
{
	__super::OnDisable();
}

void CBronyaBullet::SetBasicName(void)
{
}

void CBronyaBullet::ActiveAttackBall(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat * pBoneMat, _float radius)
{
	HitInfo info;
	info.SetDamageRate(damageRate);
	info.SetStrengthType(strength);
	info.SetCrowdControlType(cc);

	m_pAttackBall->SetupBall(this, pBoneMat, radius, info);
	m_pAttackBall->SetIsEnabled(true);
}

void CBronyaBullet::UnActiveAttackBall()
{
	m_pAttackBall->SetIsEnabled(false);
}
