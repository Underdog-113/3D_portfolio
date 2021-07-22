#include "stdafx.h"
#include "..\Header\Stun_Star.h"

_uint CStun_Star::m_s_uniqueID = 0;

CStun_Star::CStun_Star()
{
}


CStun_Star::~CStun_Star()
{
}

SP(CStun_Star) CStun_Star::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CStun_Star) spInstance(new CStun_Star, Engine::SmartDeleter<CStun_Star>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CStun_Star::MakeClone()
{
	SP(CStun_Star) spClone(new CStun_Star, Engine::SmartDeleter<CStun_Star>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CStun_Star::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Cloud");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Star");
	m_spTexture->AddTexture(L"Star");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
	_float _size = 0.002f;
	m_spTransform->SetSize(_float3(_size, _size, _size));

}

void CStun_Star::Start()
{
	__super::Start();
	m_spTransform->AddRotationZ(D3DXToRadian(rand() % 90 + 45));

	m_fAlpha = 1.f;
}

void CStun_Star::FixedUpdate()
{
	__super::FixedUpdate();

}

void CStun_Star::Update()
{
	__super::Update();

	m_fAlpha -= 2.3f * GET_DT;

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_spTransform->AddPosition(m_spTransform->GetRight() * GET_DT * 0.2f);
}

void CStun_Star::LateUpdate()
{
	__super::LateUpdate();

	// Billboard
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

void CStun_Star::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", false);

	pEffect->CommitChanges();
}

void CStun_Star::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CStun_Star::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CStun_Star::OnDestroy()
{
	__super::OnDestroy();

}

void CStun_Star::OnEnable()
{
	__super::OnEnable();

}

void CStun_Star::OnDisable()
{
	__super::OnDisable();

}

void CStun_Star::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
