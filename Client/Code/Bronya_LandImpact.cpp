#include "stdafx.h"
#include "..\Header\Bronya_LandImpact.h"

_uint CBronya_LandImpact::m_s_uniqueID = 0;

CBronya_LandImpact::CBronya_LandImpact()
{
}


CBronya_LandImpact::~CBronya_LandImpact()
{
}

SP(CBronya_LandImpact) CBronya_LandImpact::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_LandImpact) spInstance(new CBronya_LandImpact, Engine::SmartDeleter<CBronya_LandImpact>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_LandImpact::MakeClone()
{
	SP(CBronya_LandImpact) spClone(new CBronya_LandImpact, Engine::SmartDeleter<CBronya_LandImpact>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(0.2f, 0.2f, 0.2f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_LandImpact::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Impact");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Gray");
	m_spTexture->AddTexture(L"Wave01");
	m_spTexture->AddTexture(L"Gray");
	m_spShader->AddShader((_int)EShaderID::DissolveShader);
}

void CBronya_LandImpact::Start()
{
	__super::Start();

	SP(Engine::CObject) spLandSmoke = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_LandSmoke", true);
	spLandSmoke->GetTransform()->SetPosition(this->GetTransform()->GetPosition());
	spLandSmoke->GetTransform()->SetPositionY(this->GetTransform()->GetPosition().y - 0.07f);

	m_fAlpha = 1.f;

}

void CBronya_LandImpact::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_LandImpact::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 3.f * GET_DT;
}

void CBronya_LandImpact::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_LandImpact::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CBronya_LandImpact::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_LandImpact::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_LandImpact::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_LandImpact::OnEnable()
{
	__super::OnEnable();

}

void CBronya_LandImpact::OnDisable()
{
	__super::OnDisable();

}

void CBronya_LandImpact::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
