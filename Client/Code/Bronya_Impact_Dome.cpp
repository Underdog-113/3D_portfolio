#include "stdafx.h"
#include "..\Header\Bronya_Impact_Dome.h"

_uint CBronya_Impact_Dome::m_s_uniqueID = 0;

CBronya_Impact_Dome::CBronya_Impact_Dome()
{
}


CBronya_Impact_Dome::~CBronya_Impact_Dome()
{
}

SP(CBronya_Impact_Dome) CBronya_Impact_Dome::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Impact_Dome) spInstance(new CBronya_Impact_Dome, Engine::SmartDeleter<CBronya_Impact_Dome>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Impact_Dome::MakeClone()
{
	SP(CBronya_Impact_Dome) spClone(new CBronya_Impact_Dome, Engine::SmartDeleter<CBronya_Impact_Dome>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetRotationZ(D3DXToRadian(180.f));
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Impact_Dome::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Dome");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"ExplosionWarning");
	m_spTexture->AddTexture(L"ExplosionWarning");
	m_spTexture->AddTexture(L"ExplosionWarning");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
}

void CBronya_Impact_Dome::Start()
{
	__super::Start();
	m_fAlpha = 0.25f;
}

void CBronya_Impact_Dome::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Impact_Dome::Update()
{
	__super::Update();

	if (this->GetTransform()->GetSize().x >= 8.f)
	{
		this->SetDeleteThis(true);
	}

	_float _size = 2.3f * GET_DT;

	this->GetTransform()->AddSize(_float3(_size, _size, _size));
}

void CBronya_Impact_Dome::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Impact_Dome::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CBronya_Impact_Dome::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Impact_Dome::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Impact_Dome::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Impact_Dome::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Impact_Dome::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Impact_Dome::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
