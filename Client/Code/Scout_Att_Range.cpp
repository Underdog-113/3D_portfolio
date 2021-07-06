#include "stdafx.h"
#include "..\Header\Scout_Att_Range.h"

_uint CScout_Att_Range::m_s_uniqueID = 0;

CScout_Att_Range::CScout_Att_Range()
{
}


CScout_Att_Range::~CScout_Att_Range()
{
}

SP(CScout_Att_Range) CScout_Att_Range::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CScout_Att_Range) spInstance(new CScout_Att_Range, Engine::SmartDeleter<CScout_Att_Range>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CScout_Att_Range::MakeClone()
{
	SP(CScout_Att_Range) spClone(new CScout_Att_Range, Engine::SmartDeleter<CScout_Att_Range>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSizeX(0.3f);
	spClone->m_spTransform->SetSizeZ(0.3f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CScout_Att_Range::Awake()
{
	__super::Awake();
}

void CScout_Att_Range::Start()
{
	__super::Start();

	m_spAtt_Range_Hold = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Scout_Att_Range_Hold", true, (_int)Engine::ELayerID::Effect, L"MeshEffect");
	m_spAtt_Range_Hold->GetComponent<Engine::CMeshC>()->SetMeshData(L"Scout_Att_Range_Hold");
	m_spAtt_Range_Hold->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spAtt_Range_Hold->GetComponent<Engine::CTextureC>()->AddTexture(L"Sign");
	m_spAtt_Range_Hold->GetComponent<Engine::CTextureC>()->AddTexture(L"AttackHint_Fan");
	m_spAtt_Range_Hold->GetComponent<Engine::CTextureC>()->AddTexture(L"AttackHint_Fan");
	m_spAtt_Range_Hold->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	m_spAtt_Range_Hold->GetComponent<Engine::CTransformC>()->SetPosition(this->GetTransform()->GetPosition());
	m_spAtt_Range_Hold->GetComponent<Engine::CTransformC>()->SetRotation(this->GetTransform()->GetRotation());
	m_spAtt_Range_Hold->GetComponent<Engine::CTransformC>()->SetSize(this->GetTransform()->GetSize());	
	
	m_fAlpha = 0.f;
}

void CScout_Att_Range::FixedUpdate()
{
	__super::FixedUpdate();

}

void CScout_Att_Range::Update()
{
	__super::Update();

	if (m_fAlpha >= 1.f)
	{
		SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Scout_Laser", true, (_int)Engine::ELayerID::Effect, L"MeshEffect");
		spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(L"Scout_Laser");
		spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"BallColor");
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"BallColor");
		spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
		spMeshEffect->GetTransform()->SetPosition(this->GetTransform()->GetPosition());

		m_spAtt_Range_Hold->SetDeleteThis(true);
		this->SetDeleteThis(true);
	}

	m_fAlpha += 0.5f * GET_DT;
}

void CScout_Att_Range::LateUpdate()
{
	__super::LateUpdate();

}

void CScout_Att_Range::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gTmpAlpha", 0.5f);
	pEffect->SetBool("g_bAlphaCtrl", true);

}

void CScout_Att_Range::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CScout_Att_Range::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CScout_Att_Range::OnDestroy()
{
	__super::OnDestroy();
}

void CScout_Att_Range::OnEnable()
{
	__super::OnEnable();
}

void CScout_Att_Range::OnDisable()
{
	__super::OnDisable();
}

void CScout_Att_Range::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
