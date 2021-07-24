#include "stdafx.h"
#include "..\Header\Bronya_RandomSmoke.h"

_uint CBronya_RandomSmoke::m_s_uniqueID = 0;

CBronya_RandomSmoke::CBronya_RandomSmoke()
{
}


CBronya_RandomSmoke::~CBronya_RandomSmoke()
{
}

SP(CBronya_RandomSmoke) CBronya_RandomSmoke::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_RandomSmoke) spInstance(new CBronya_RandomSmoke, Engine::SmartDeleter<CBronya_RandomSmoke>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_RandomSmoke::MakeClone(void)
{
	SP(CBronya_RandomSmoke) spClone(new CBronya_RandomSmoke, Engine::SmartDeleter<CBronya_RandomSmoke>);

	__super::InitClone(spClone);
	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	return spClone;
}

void CBronya_RandomSmoke::Awake(void)
{
	__super::Awake();
	m_spTransform->SetSize(_float3(0.5f, 0.5f, 0.5f));
	m_spMesh->SetMeshData(L"Cloud");
	m_spMesh->SetIsEffectMesh(true);
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
}

void CBronya_RandomSmoke::Start(void)
{
	__super::Start();

	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_fAlpha = 1.f;
	m_fTime = 0.f;

}

void CBronya_RandomSmoke::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CBronya_RandomSmoke::Update(void)
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	// 일정시간 뒤에 알파값 감소.

	if (m_fTime >= 5.f)
	{
		m_fAlpha -= 0.7f * GET_DT;
	}

	m_fTime += GET_DT;
}

void CBronya_RandomSmoke::LateUpdate(void)
{
	__super::LateUpdate();

	_mat matWorld, matView, matBill;

	matView = Engine::GET_MAIN_CAM->GetViewMatrix();

	D3DXMatrixIdentity(&matBill);

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	matWorld = m_spGraphics->GetTransform()->GetWorldMatrix();

	m_spGraphics->GetTransform()->SetWorldMatrix(matBill * matWorld);

}

void CBronya_RandomSmoke::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);

	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", false);
	pEffect->SetBool("g_AlphaTestEnabled", true);
	pEffect->CommitChanges();
}

void CBronya_RandomSmoke::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_RandomSmoke::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_RandomSmoke::OnDestroy(void)
{
	__super::OnDestroy();

}

void CBronya_RandomSmoke::OnEnable(void)
{
	__super::OnEnable();

}

void CBronya_RandomSmoke::OnDisable(void)
{
	__super::OnDisable();

}

void CBronya_RandomSmoke::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}


