#include "stdafx.h"
#include "..\Header\Sakura_WSkill_Twist.h"

_uint CSakura_WSkill_Twist::m_s_uniqueID = 0;

CSakura_WSkill_Twist::CSakura_WSkill_Twist()
{
}


CSakura_WSkill_Twist::~CSakura_WSkill_Twist()
{
}

SP(CSakura_WSkill_Twist) CSakura_WSkill_Twist::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_WSkill_Twist) spInstance(new CSakura_WSkill_Twist, Engine::SmartDeleter<CSakura_WSkill_Twist>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_WSkill_Twist::MakeClone()
{
	SP(CSakura_WSkill_Twist) spClone(new CSakura_WSkill_Twist, Engine::SmartDeleter<CSakura_WSkill_Twist>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CSakura_WSkill_Twist::Awake()
{
	__super::Awake();
	m_spTransform->SetSize(0.03f, 0.03f, 0.03f);
}

void CSakura_WSkill_Twist::Start()
{
	__super::Start();

	m_spTwistWind = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Sakura_WSkill_Twist_Wind", true);
	m_spTwistWind->GetTransform()->SetOwner(this);

	m_fLifeTime = 0.f;
	m_fAlpha = 1.f;
	m_fUVSpeed = 0.f;
}

void CSakura_WSkill_Twist::FixedUpdate()
{
	__super::FixedUpdate();

}

void CSakura_WSkill_Twist::Update()
{
	__super::Update();

	if (m_fLifeTime >= 1.f)
	{
		m_fAlpha -= 1.5f * GET_PLAYER_DT;

		if (m_fAlpha <= 0)
		{
			m_spTwistWind->SetDeleteThis(true);
			this->SetDeleteThis(true);
		}
	}

	if (m_fTime >= 0.5f)
	{
		SP(Engine::CObject) spImpact;
		spImpact = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Sakura_WSkill_Impact", true);
		spImpact->GetTransform()->SetPosition(m_spTransform->GetPosition());
		m_fTime = 0.f;
	}

	m_fTime += GET_PLAYER_DT;
	m_fLifeTime += GET_PLAYER_DT;

	m_fUVSpeed += 5.f * GET_PLAYER_DT;

	_float _size = 0.1f * GET_PLAYER_DT;
	if(m_spTransform->GetSize().x <= 0.2f)
		m_spTransform->AddSize(_float3(_size, _size, _size));

	if(m_fLifeTime < 1)
		m_spTransform->AddPosition(m_MoveDir * GET_PLAYER_DT * 5.f);

	m_spTransform->AddRotationY(-15.f * GET_PLAYER_DT);

}

void CSakura_WSkill_Twist::LateUpdate()
{
	__super::LateUpdate();

}

void CSakura_WSkill_Twist::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", -m_fUVSpeed);
	pEffect->SetBool("gPlayingAnim", true);
	pEffect->CommitChanges();
}

void CSakura_WSkill_Twist::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CSakura_WSkill_Twist::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CSakura_WSkill_Twist::OnDestroy()
{
	__super::OnDestroy();

}

void CSakura_WSkill_Twist::OnEnable()
{
	__super::OnEnable();

}

void CSakura_WSkill_Twist::OnDisable()
{
	__super::OnDisable();

}

void CSakura_WSkill_Twist::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
