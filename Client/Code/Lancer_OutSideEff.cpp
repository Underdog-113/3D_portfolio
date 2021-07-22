#include "stdafx.h"
#include "..\Header\Lancer_OutSideEff.h"

_uint CLancer_OutSideEff::m_s_uniqueID = 0;

CLancer_OutSideEff::CLancer_OutSideEff()
{
}


CLancer_OutSideEff::~CLancer_OutSideEff()
{
}

SP(CLancer_OutSideEff) CLancer_OutSideEff::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CLancer_OutSideEff) spInstance(new CLancer_OutSideEff, Engine::SmartDeleter<CLancer_OutSideEff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CLancer_OutSideEff::MakeClone()
{
	SP(CLancer_OutSideEff) spClone(new CLancer_OutSideEff, Engine::SmartDeleter<CLancer_OutSideEff>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CLancer_OutSideEff::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Lancer_OutSideEff");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Lancer_Eff_Color");
	m_spTexture->AddTexture(L"Soft");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
}

void CLancer_OutSideEff::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_iCnt = 0;
	m_fTimer = 0;
	m_spTransform->AddRotationX(D3DXToRadian(15));

}

void CLancer_OutSideEff::FixedUpdate()
{
	__super::FixedUpdate();

}

void CLancer_OutSideEff::Update()
{
	__super::Update();
	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	/*if (m_fTimer >= 1.f || m_iCnt < 1)
	{
		SP(Engine::CObject) spSoftEffect;

		for (_uint i = 0; i < 5; ++i)
		{			
			spSoftEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Lancer_Impact", true);
			spSoftEffect->GetTransform()->SetPosition(m_spTransform->GetPosition().x, m_spTransform->GetPosition().y, m_spTransform->GetPosition().z);
			spSoftEffect->GetTransform()->SetRotationY(D3DXToRadian(90));
			spSoftEffect->GetTransform()->SetRotationZ(D3DXToRadian((rand() % 45) + 45));
		}
		m_iCnt++;
		m_fTimer = 0.f;
	}*/

	
	m_fTime += GET_DT;
	//m_fTimer += GET_DT;

	m_fAlpha -= 1.f * GET_DT;

	_mat q;
	D3DXMatrixRotationAxis(&q, &m_spTransform->GetForward(), -30 * m_fTime);
	m_spTransform->SetParentRotMatrix(q);
}

void CLancer_OutSideEff::LateUpdate()
{
	__super::LateUpdate();

}

void CLancer_OutSideEff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);

}

void CLancer_OutSideEff::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CLancer_OutSideEff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CLancer_OutSideEff::OnDestroy()
{
	__super::OnDestroy();

}

void CLancer_OutSideEff::OnEnable()
{
	__super::OnEnable();

}

void CLancer_OutSideEff::OnDisable()
{
	__super::OnDisable();

}

void CLancer_OutSideEff::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
