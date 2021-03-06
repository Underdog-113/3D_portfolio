#include "stdafx.h"
#include "..\Header\Bronya_Ult_Ring.h"
#include "Bronya_Ult_Cannon.h"
#include "Bronya_Ult_Wind.h"

_uint CBronya_Ult_Ring::m_s_uniqueID = 0;

CBronya_Ult_Ring::CBronya_Ult_Ring()
{
}


CBronya_Ult_Ring::~CBronya_Ult_Ring()
{
}

SP(CBronya_Ult_Ring) CBronya_Ult_Ring::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Ult_Ring) spInstance(new CBronya_Ult_Ring, Engine::SmartDeleter<CBronya_Ult_Ring>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Ult_Ring::MakeClone()
{
	SP(CBronya_Ult_Ring) spClone(new CBronya_Ult_Ring, Engine::SmartDeleter<CBronya_Ult_Ring>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Ult_Ring::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Plane2");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Impact_Red");
	m_spTexture->AddTexture(L"Locking_2");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
	m_spTransform->SetSize(0.01f, 0.01f, 0.01f);
	m_spTransform->SetRotationX(D3DXToRadian(195));

}

void CBronya_Ult_Ring::Start()
{
	__super::Start();

	m_fRingSize = 0.07f;

	m_fAlpha = 1.f;
	m_fTime = 0.f;
	m_fAngle = 0.f;
	m_bSpawnWind = false;
}

void CBronya_Ult_Ring::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Ult_Ring::Update()
{
	__super::Update();

	if (nullptr != m_pOwner)
	{
		if (true == m_pOwner->GetComponent<CPatternMachineC>()->GetOnDie())
		{
			m_deleteThis = true;
			m_pOwner = nullptr;
			return;
		}
	}

	if(!m_bSpawnWind)
		m_fTime += GET_DT;

	if (m_fTime >= 2.5f && m_spTransform->GetSize().x < m_fRingSize)
	{
		_float _size = 1.5f * GET_DT;

		m_spTransform->AddSize(_float3(_size, _size, _size));
	}
	else if (m_spTransform->GetSize().x >= m_fRingSize && !m_bSpawnWind)
	{
		// Add Wind and Cannon
		m_spWind = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Ult_Wind", true);
		m_spWind->GetTransform()->SetPosition(m_spTransform->GetPosition());
		m_spWind->GetTransform()->SetRotation(m_spTransform->GetRotation());
		m_spWind->GetTransform()->SetSize(_float3(m_fRingSize, m_fRingSize, m_fRingSize));

		m_spCannon = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Ult_Cannon", true);
		m_spCannon->GetTransform()->SetPositionX(m_spTransform->GetPosition().x);
		m_spCannon->GetTransform()->SetPositionY(m_spTransform->GetPosition().y);
		m_spCannon->GetTransform()->SetPositionZ(m_spTransform->GetPosition().z);
		m_spCannon->GetTransform()->SetRotation(m_spTransform->GetRotation());

		m_bSpawnWind = true;
	}
	_mat matRot;

	m_fAngle += D3DXToRadian(30) * GET_DT;

	D3DXMatrixRotationAxis(&matRot, &m_spTransform->GetForward(), m_fAngle);
	m_spTransform->SetParentRotMatrix(matRot);

	/* Delete this */
	if (true == m_disappear)
	{
		if (nullptr != m_spCannon)
		{
			_float alpha = std::dynamic_pointer_cast<CBronya_Ult_Cannon>(m_spCannon)->GetAlpha() - 1.f * GET_DT;

			if (0.f >= alpha)
			{
				std::dynamic_pointer_cast<CBronya_Ult_Cannon>(m_spCannon)->SetAlpha(0.f);
				m_spCannon->SetDeleteThis(true);
				m_spCannon = nullptr;
			}
			else
			{
				std::dynamic_pointer_cast<CBronya_Ult_Cannon>(m_spCannon)->SetAlpha(alpha);
			}
		}

		if (nullptr != m_spWind)
		{
			_float alpha = std::dynamic_pointer_cast<CBronya_Ult_Wind>(m_spWind)->GetAlpha() - 1.f * GET_DT;

			if (0.f >= alpha)
			{
				std::dynamic_pointer_cast<CBronya_Ult_Wind>(m_spWind)->SetAlpha(0.f);
				m_spWind->SetDeleteThis(true);
				m_spWind = nullptr;
			}
			else
			{
				std::dynamic_pointer_cast<CBronya_Ult_Wind>(m_spWind)->SetAlpha(alpha);
			}
		}
		
		m_fAlpha -= 0.7f * GET_DT;

		if (0.f >= m_fAlpha)
		{
			m_fAlpha = 0.f;
			m_deleteThis = true;
			m_disappear = false;
		}
	}
}

void CBronya_Ult_Ring::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Ult_Ring::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);

	pEffect->CommitChanges();
}

void CBronya_Ult_Ring::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Ult_Ring::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Ult_Ring::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Ult_Ring::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Ult_Ring::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Ult_Ring::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
