#include "stdafx.h"
#include "..\Header\Bronya_Grenade_Dome.h"

_uint CBronya_Grenade_Dome::m_s_uniqueID = 0;

CBronya_Grenade_Dome::CBronya_Grenade_Dome()
{
}


CBronya_Grenade_Dome::~CBronya_Grenade_Dome()
{
}

SP(CBronya_Grenade_Dome) CBronya_Grenade_Dome::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Grenade_Dome) spInstance(new CBronya_Grenade_Dome, Engine::SmartDeleter<CBronya_Grenade_Dome>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Grenade_Dome::MakeClone()
{
	SP(CBronya_Grenade_Dome) spClone(new CBronya_Grenade_Dome, Engine::SmartDeleter<CBronya_Grenade_Dome>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetRotationZ(D3DXToRadian(180.f));
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Grenade_Dome::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Dome");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
}

void CBronya_Grenade_Dome::Start()
{
	__super::Start();
	m_fAlpha = 0.25f;
}

void CBronya_Grenade_Dome::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Grenade_Dome::Update()
{
	__super::Update();

	if (this->GetTransform()->GetSize().x >= 1.5f)
	{
		this->SetDeleteThis(true);
	}

	_float _size = 2.3f * GET_DT;

	this->GetTransform()->AddSize(_float3(_size, _size, _size));
}

void CBronya_Grenade_Dome::LateUpdate()
{
	__super::LateUpdate();
}

void CBronya_Grenade_Dome::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CBronya_Grenade_Dome::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Grenade_Dome::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Grenade_Dome::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Grenade_Dome::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Grenade_Dome::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Grenade_Dome::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
