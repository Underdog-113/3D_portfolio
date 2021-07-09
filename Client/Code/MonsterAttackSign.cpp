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
	spClone->m_spTransform->SetSizeX(5);
	spClone->m_spTransform->SetSizeY(1);
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;
	spClone->m_fAlphaWidth = 1.f;
	spClone->m_fAlphaHeight = 6.f;
	spClone->m_TilingX = 0;
	spClone->m_TilingY = 0;
	spClone->m_maxXIndex = 1;
	spClone->m_maxYIndex = 5;
	spClone->m_fTIme = 0.f;
	return spClone;
}

void CMonsterAttackSign::Awake(void)
{
	__super::Awake();
	
}

void CMonsterAttackSign::Start(void)
{
	__super::Start();

	
}

void CMonsterAttackSign::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CMonsterAttackSign::Update(void)
{
	__super::Update();

	UpdateFrame(0.1f);
}

void CMonsterAttackSign::LateUpdate(void)
{
	__super::LateUpdate();

}

void CMonsterAttackSign::PreRender(LPD3DXEFFECT pEffect)
{
	/*_mat matWorld, matView, matProj;
	
	matWorld = this->GetGraphics()->GetTransform()->GetWorldMatrix();
	matView = Engine::GET_MAIN_CAM->GetViewMatrix();
	matProj = Engine::GET_MAIN_CAM->GetProjMatrix();
	
	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	
	SP(Engine::CTextureC) spTexture = this->GetGraphics()->GetTexture();
	
	pEffect->SetTexture("g_BaseTexture", spTexture->GetTexData()[0][0]->pTexture);
	pEffect->SetTexture("g_ServeTexture", spTexture->GetTexData()[0][1]->pTexture);*/
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

void CMonsterAttackSign::UpdateFrame(_float _frmSpeed)
{
	m_fTIme += GET_DT;

	if (m_fTIme >= _frmSpeed)
	{
		m_TilingX++;

		if (m_TilingX >= m_maxXIndex)
		{
			m_TilingX = 0;

			if (m_TilingY >= m_maxYIndex)
			{
				m_TilingY = 0;
				SetDeleteThis(true);
			}
			else
			{
				m_TilingY++;
			}
		}
		m_fTIme = 0;
	}
}
