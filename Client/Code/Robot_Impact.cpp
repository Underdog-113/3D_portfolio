#include "stdafx.h"
#include "..\Header\Robot_Impact.h"

_uint CRobot_Impact::m_s_uniqueID = 0;

CRobot_Impact::CRobot_Impact()
{
}


CRobot_Impact::~CRobot_Impact()
{
}

SP(CRobot_Impact) CRobot_Impact::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CRobot_Impact) spInstance(new CRobot_Impact, Engine::SmartDeleter<CRobot_Impact>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CRobot_Impact::MakeClone()
{
	SP(CRobot_Impact) spClone(new CRobot_Impact, Engine::SmartDeleter<CRobot_Impact>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	//spClone->m_spTransform->SetPositionZ(2.f);
	//spClone->m_spTransform->SetSizeX(0.5f);
	//spClone->m_spTransform->SetSizeY(0.2f);
	/*spClone->m_spTransform->SetSizeX(3.5f);
	spClone->m_spTransform->SetSizeY(3.2f);*/
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;
	return spClone;
}

void CRobot_Impact::Awake()
{
	__super::Awake();
}

void CRobot_Impact::Start()
{
	__super::Start();
	m_fAlphaWidth = 2.f;
	m_fAlphaHeight = 2.f;
	m_TilingX = 0;
	m_TilingY = 0;

	m_maxXIndex = 2;
	m_maxYIndex = 1;
	m_fTIme = 0.f;

	SP(Engine::CObject) spImpactSmoke = Engine::GET_CUR_SCENE->ADD_CLONE(L"Robot_Impact_Smoke", true);
	spImpactSmoke->GetTransform()->SetPosition(this->GetTransform()->GetPosition());
	spImpactSmoke->GetTransform()->SetPositionY(this->GetTransform()->GetPosition().y - 0.1f);
}

void CRobot_Impact::FixedUpdate()
{
	__super::FixedUpdate();

}

void CRobot_Impact::Update()
{
	__super::Update();
	
	UpdateFrame(0.1f);

}

void CRobot_Impact::LateUpdate()
{
	__super::LateUpdate();

	_mat matWorld, matView, matBill;

	matView = Engine::GET_MAIN_CAM->GetViewMatrix();

	D3DXMatrixIdentity(&matBill);

	//matBill._11 = matView._11;
	//matBill._13 = matView._13;
	//matBill._31 = matView._31;
	//matBill._33 = matView._33;

	memcpy(&matBill.m[0][0], &matView.m[0][0], sizeof(_float3));
	memcpy(&matBill.m[1][0], &matView.m[1][0], sizeof(_float3));
	memcpy(&matBill.m[2][0], &matView.m[2][0], sizeof(_float3));

	D3DXMatrixInverse(&matBill, 0, &matBill);

	matWorld = m_spGraphics->GetTransform()->GetWorldMatrix();

	m_spGraphics->GetTransform()->SetWorldMatrix(matBill * matWorld);
}

void CRobot_Impact::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);

	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);

	pEffect->CommitChanges();
}

void CRobot_Impact::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);
}

void CRobot_Impact::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);


}

void CRobot_Impact::OnDestroy()
{
	__super::OnDestroy();

}

void CRobot_Impact::OnEnable()
{
	__super::OnEnable();

}

void CRobot_Impact::OnDisable()
{
	__super::OnDisable();

}

void CRobot_Impact::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CRobot_Impact::UpdateFrame(_float _frmSpeed)
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
