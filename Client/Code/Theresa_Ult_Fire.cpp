#include "stdafx.h"
#include "..\Header\Theresa_Ult_Fire.h"

_uint CTheresa_Ult_Fire::m_s_uniqueID = 0;

CTheresa_Ult_Fire::CTheresa_Ult_Fire()
{
}


CTheresa_Ult_Fire::~CTheresa_Ult_Fire()
{
}

SP(CTheresa_Ult_Fire) CTheresa_Ult_Fire::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa_Ult_Fire) spInstance(new CTheresa_Ult_Fire, Engine::SmartDeleter<CTheresa_Ult_Fire>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa_Ult_Fire::MakeClone()
{
	SP(CTheresa_Ult_Fire) spClone(new CTheresa_Ult_Fire, Engine::SmartDeleter<CTheresa_Ult_Fire>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CTheresa_Ult_Fire::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Cloud");
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spTexture->AddTexture(L"Fire");
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spShader->AddShader((_int)EShaderID::DissolveShader);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
}

void CTheresa_Ult_Fire::Start()
{
	__super::Start();
	m_spTransform->SetSize(_float3(0.1f, 0.f, 0.1f));
	m_fAlpha = 1.f;
}

void CTheresa_Ult_Fire::FixedUpdate()
{
	__super::FixedUpdate();
}

void CTheresa_Ult_Fire::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 0.5f * GET_PLAYER_DT;

	_float _size = 0.1f * GET_DT;
	m_spTransform->AddSizeY(_size);
}

void CTheresa_Ult_Fire::LateUpdate()
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

void CTheresa_Ult_Fire::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->CommitChanges();
}

void CTheresa_Ult_Fire::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa_Ult_Fire::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CTheresa_Ult_Fire::OnDestroy()
{
	__super::OnDestroy();
}

void CTheresa_Ult_Fire::OnEnable()
{
	__super::OnEnable();
}

void CTheresa_Ult_Fire::OnDisable()
{
	__super::OnDisable();
}

void CTheresa_Ult_Fire::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
