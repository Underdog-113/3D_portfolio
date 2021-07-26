#include "stdafx.h"
#include "..\Header\Stun_Eff.h"

#include "Stun_Star.h"

_uint CStun_Eff::m_s_uniqueID = 0;

CStun_Eff::CStun_Eff()
{
}


CStun_Eff::~CStun_Eff()
{
	OnDestroy();
}

SP(CStun_Eff) CStun_Eff::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CStun_Eff) spInstance(new CStun_Eff, Engine::SmartDeleter<CStun_Eff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CStun_Eff::MakeClone()
{
	SP(CStun_Eff) spClone(new CStun_Eff, Engine::SmartDeleter<CStun_Eff>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CStun_Eff::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Impact_TripleRing");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Gray");
	m_spTexture->AddTexture(L"Austerity");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
	_float _size = 0.5f;
	m_spTransform->SetSize(_float3(_size, _size, _size));
}

void CStun_Eff::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fTime = 0.f;
}

void CStun_Eff::FixedUpdate()
{
	__super::FixedUpdate();

}

void CStun_Eff::Update()
{
	__super::Update();

	if (!m_pTargetObject || m_pTargetObject->GetDeleteThis())
	{
		SetDeleteThis(true);
		return;
	}

	m_spTransform->SetPosition(m_pTargetObject->GetTransform()->GetPosition());
	m_spTransform->AddPositionY(m_pTargetObject->GetComponent<Engine::CMeshC>()->GetHalfYOffset() * 2.1f);

	m_fTime += GET_DT;

	if (m_fTime >= 0.3f)
	{
		SP(Engine::CObject) effect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Stun_Star", true, (_uint)Engine::ELayerID::Effect);
		effect->GetTransform()->SetPosition(m_spTransform->GetPosition());
		effect->GetTransform()->SetSize(_float3(0.007f, 0.007f, 0.007f));
		m_fTime = 0.f;
	}

	m_spTransform->AddRotationY(D3DXToRadian(15.f) * GET_DT * 3.f);
}

void CStun_Eff::LateUpdate()
{
	__super::LateUpdate();

}

void CStun_Eff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", false);

	pEffect->CommitChanges();
}

void CStun_Eff::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CStun_Eff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CStun_Eff::OnDestroy()
{
	__super::OnDestroy();
}

void CStun_Eff::OnEnable()
{
	__super::OnEnable();

}

void CStun_Eff::OnDisable()
{
	__super::OnDisable();

}

void CStun_Eff::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
