#include "stdafx.h"
#include "..\Header\Bronya_LandSmoke.h"

_uint CBronya_LandSmoke::m_s_uniqueID = 0;

CBronya_LandSmoke::CBronya_LandSmoke()
{
}


CBronya_LandSmoke::~CBronya_LandSmoke()
{
}

SP(CBronya_LandSmoke) CBronya_LandSmoke::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_LandSmoke) spInstance(new CBronya_LandSmoke, Engine::SmartDeleter<CBronya_LandSmoke>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_LandSmoke::MakeClone()
{
	SP(CBronya_LandSmoke) spClone(new CBronya_LandSmoke, Engine::SmartDeleter<CBronya_LandSmoke>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CBronya_LandSmoke::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Impact_TripleRing");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Gray");
	m_spTexture->AddTexture(L"Austerity");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
}

void CBronya_LandSmoke::Start()
{
	__super::Start();

	m_fAlpha = 1.3f;
	m_fTime = 0.f;
}

void CBronya_LandSmoke::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_LandSmoke::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	_float3 _size = _float3(0.5f, 0.5f, 0.5f);

	m_fAlpha -= 2.3f * GET_DT;
	m_fTime += 0.2f * GET_DT;
	m_spTransform->AddSize(_size * GET_DT);
}

void CBronya_LandSmoke::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_LandSmoke::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fTime);
	pEffect->SetBool("gPlayingAnim", true);

	pEffect->CommitChanges();
}

void CBronya_LandSmoke::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_LandSmoke::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_LandSmoke::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_LandSmoke::OnEnable()
{
	__super::OnEnable();

}

void CBronya_LandSmoke::OnDisable()
{
	__super::OnDisable();

}

void CBronya_LandSmoke::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
