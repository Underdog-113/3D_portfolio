#include "stdafx.h"
#include "..\Header\Bronya_Grenade.h"

_uint CBronya_Grenade::m_s_uniqueID = 0;

CBronya_Grenade::CBronya_Grenade()
{
}


CBronya_Grenade::~CBronya_Grenade()
{
}

SP(CBronya_Grenade) CBronya_Grenade::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Grenade) spInstance(new CBronya_Grenade, Engine::SmartDeleter<CBronya_Grenade>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Grenade::MakeClone()
{
	SP(CBronya_Grenade) spClone(new CBronya_Grenade, Engine::SmartDeleter<CBronya_Grenade>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Grenade::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Bullet");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
}

void CBronya_Grenade::Start()
{
	__super::Start();
	
	_float3 size = { 5.1f, 5.1f, 5.1f };

	SP(Engine::CObject) spDome = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Grenade_Dome", true);
	spDome->GetTransform()->SetSize(_float3(2.85f, 2.85f, 2.85f));
	spDome->GetTransform()->SetPosition(m_spTransform->GetPosition());
	spDome->GetTransform()->SetPositionY(m_spTransform->GetPosition().y - 0.2f);

	SP(Engine::CObject) spImpact = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Grenade_Impact", true);
	spImpact->GetTransform()->SetSize(size);
	spImpact->GetTransform()->SetPosition(m_spTransform->GetPosition());

	SP(Engine::CObject) spTriRing = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Grenade_TriRing", true);
	spTriRing->GetTransform()->SetSize(size);
	spTriRing->GetTransform()->SetPosition(m_spTransform->GetPosition());
	spTriRing->GetTransform()->SetPositionY(m_spTransform->GetPosition().y - 0.07f);

}

void CBronya_Grenade::FixedUpdate()
{
	__super::FixedUpdate();
}

void CBronya_Grenade::Update()
{
	__super::Update();

	this->SetDeleteThis(true);		

}

void CBronya_Grenade::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Grenade::PreRender(LPD3DXEFFECT pEffect)
{
}

void CBronya_Grenade::Render(LPD3DXEFFECT pEffect)
{

}

void CBronya_Grenade::PostRender(LPD3DXEFFECT pEffect)
{

}

void CBronya_Grenade::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Grenade::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Grenade::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Grenade::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
