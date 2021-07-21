#include "stdafx.h"
#include "..\Header\MonsterAttackSign.h"

_uint CMonsterAttackSign::m_s_uniqueID = 0;

CMonsterAttackSign::CMonsterAttackSign()
{
}


CMonsterAttackSign::~CMonsterAttackSign()
{
}

SP(CMonsterAttackSign) CMonsterAttackSign::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMonsterAttackSign) spInstance(new CMonsterAttackSign, Engine::SmartDeleter<CMonsterAttackSign>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMonsterAttackSign::MakeClone(void)
{
	SP(CMonsterAttackSign) spClone(new CMonsterAttackSign, Engine::SmartDeleter<CMonsterAttackSign>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSizeX(3);
	spClone->m_spTransform->SetSizeY(2);
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;

	return spClone;
}

void CMonsterAttackSign::Awake(void)
{
	__super::Awake();
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	
}

void CMonsterAttackSign::Start(void)
{
	__super::Start();
	m_fAlphaWidth = 1.f;
	m_fAlphaHeight = 1.f;
	m_TilingX = 0;
	m_TilingY = 0;
	m_maxXIndex = 1;
	m_maxYIndex = 0;
	m_fTIme = 0.f;	
}

void CMonsterAttackSign::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CMonsterAttackSign::Update(void)
{
	__super::Update();

	if (this->GetTransform()->GetSize().y <= 0)
	{
		this->SetDeleteThis(true);
	}

	this->GetTransform()->AddSizeY(-3.5f * GET_DT);

}

void CMonsterAttackSign::LateUpdate(void)
{
	__super::LateUpdate();

}

void CMonsterAttackSign::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);	

	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);

	pEffect->CommitChanges();
}

void CMonsterAttackSign::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);
}

void CMonsterAttackSign::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);
}

void CMonsterAttackSign::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMonsterAttackSign::OnEnable(void)
{
	__super::OnEnable();
}

void CMonsterAttackSign::OnDisable(void)
{
	__super::OnDisable();
}

void CMonsterAttackSign::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}