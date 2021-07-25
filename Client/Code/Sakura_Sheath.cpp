#include "stdafx.h"
#include "..\Header\Sakura_Sheath.h"


CSakura_Sheath::CSakura_Sheath()
{
}


CSakura_Sheath::~CSakura_Sheath()
{
}

SP(CSakura_Sheath) CSakura_Sheath::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_Sheath) spInstance(new CSakura_Sheath, Engine::SmartDeleter<CSakura_Sheath>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_Sheath::MakeClone()
{
	SP(CSakura_Sheath) spClone(new CSakura_Sheath, Engine::SmartDeleter<CSakura_Sheath>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CSakura_Sheath::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Sakura_Sheath");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"White_");
	m_spTexture->AddTexture(L"White_");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);	
	m_spTransform->SetSize(_float3(0.05f, 0.05f, 0.05f));
}

void CSakura_Sheath::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fAngle = 0.f;
	m_isSizeUpDown = false;
}

void CSakura_Sheath::FixedUpdate()
{
	__super::FixedUpdate();

}

void CSakura_Sheath::Update()
{
	__super::Update();

	_float3 _size;
	if (!m_isSizeUpDown)
	{
		_size = _float3(0.05f, 0.05f, 0.05f) * GET_DT * 2.f;

		if (m_spTransform->GetSize().x >= 0.05f)
		{
			m_isSizeUpDown = true;
		}
	}
	else
	{
		if (m_spTransform->GetSize().x > 0.f)
		{
			_size = -_float3(0.05f, 0.05f, 0.05f) * GET_DT * 2.f;

			
		}
	}

	m_spTransform->AddSize(_size);

	if (m_spTransform->GetSize().x < 0.f)
		this->SetDeleteThis(true);

	_mat matRot;

	m_fAngle -= D3DXToRadian(30) * GET_DT * 15.f;

	D3DXMatrixRotationAxis(&matRot, &m_spTransform->GetForward(), m_fAngle);
	m_spTransform->SetParentRotMatrix(matRot);


}

void CSakura_Sheath::LateUpdate()
{
	__super::LateUpdate();

	/*_mat matWorld, matView, matBill;

	matView = Engine::GET_MAIN_CAM->GetViewMatrix();

	D3DXMatrixIdentity(&matBill);

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	matWorld = m_spGraphics->GetTransform()->GetWorldMatrix();

	m_spGraphics->GetTransform()->SetWorldMatrix(matBill * matWorld);*/

}

void CSakura_Sheath::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("g_fGlow", 0.9f);
	pEffect->CommitChanges();
}

void CSakura_Sheath::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CSakura_Sheath::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CSakura_Sheath::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 0.f;
}

void CSakura_Sheath::OnEnable()
{
	__super::OnEnable();

}

void CSakura_Sheath::OnDisable()
{
	__super::OnDisable();

}

void CSakura_Sheath::SetBasicName()
{
}
