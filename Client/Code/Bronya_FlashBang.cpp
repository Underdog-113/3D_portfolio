#include "stdafx.h"
#include "..\Header\Bronya_FlashBang.h"

_uint CBronya_FlashBang::m_s_uniqueID = 0;

CBronya_FlashBang::CBronya_FlashBang() : m_eState(SIZE_UP)
{
}


CBronya_FlashBang::~CBronya_FlashBang()
{
}

SP(CBronya_FlashBang) CBronya_FlashBang::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_FlashBang) spInstance(new CBronya_FlashBang, Engine::SmartDeleter<CBronya_FlashBang>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_FlashBang::MakeClone()
{
	SP(CBronya_FlashBang) spClone(new CBronya_FlashBang, Engine::SmartDeleter<CBronya_FlashBang>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(_float3(0.03f, 0.03f, 0.03f));
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_FlashBang::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_FlashBang");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"FlashBang");
	m_spTexture->AddTexture(L"FlashBang");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
}

void CBronya_FlashBang::Start()
{
	__super::Start();

	m_fTmpPosY = m_spTransform->GetPosition().y;
	m_fAlpha = 1.f;
	m_bCheck = false;
	m_fTime = 0.f;
}

void CBronya_FlashBang::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_FlashBang::Update()
{
	__super::Update();
	Movement();
}

void CBronya_FlashBang::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_FlashBang::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);

	pEffect->CommitChanges();
}

void CBronya_FlashBang::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_FlashBang::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_FlashBang::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_FlashBang::OnEnable()
{
	__super::OnEnable();

}

void CBronya_FlashBang::OnDisable()
{
	__super::OnDisable();

}

void CBronya_FlashBang::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CBronya_FlashBang::Movement()
{
	_float _size = 0.f;

	if (m_spTransform->GetPosition().y >= m_fTmpPosY + 0.7f)
	{
		m_bCheck = true;

		
	}

	if (m_eState == CBronya_FlashBang::SIZE_UP)
	{
		_size = 0.05f * GET_DT;

		if (m_spTransform->GetSize().x >= 0.035f && m_eState == CBronya_FlashBang::SIZE_UP)
		{
			m_eState = CBronya_FlashBang::SIZE_DOWN;
		}
	}
	else if (m_eState == CBronya_FlashBang::SIZE_DOWN)
	{
		_size = -0.05f * GET_DT;
		if (m_spTransform->GetSize().x <= 0.03f)
		{
			m_eState = CBronya_FlashBang::SIZE_UP;
		}
	}

	if (m_bCheck)
	{
		m_fTime += GET_DT;

		if (m_fTime >= 0.3f)
		{
			m_eState = CBronya_FlashBang::STATE_END;
			SP(Engine::CObject) spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"BronyaFlashBang_AS", true);
			spObj->GetTransform()->SetPosition(this->GetTransform()->GetPosition());
			this->SetDeleteThis(true);
			m_fTime = 0.f;
		}
	}

	if(!m_bCheck)
		m_spTransform->AddPositionY(1.f * GET_DT);

	m_spTransform->AddSize(_float3(_size, _size, _size));
}
