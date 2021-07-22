#include "stdafx.h"
#include "..\Header\Ganesha_Dome_Impact.h"

_uint CGanesha_Dome_Impact::m_s_uniqueID = 0;

CGanesha_Dome_Impact::CGanesha_Dome_Impact()
{
}


CGanesha_Dome_Impact::~CGanesha_Dome_Impact()
{
	if (m_spDomeObject != nullptr)
		m_spDomeObject->SetDeleteThis(true);
}

SP(CGanesha_Dome_Impact) CGanesha_Dome_Impact::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CGanesha_Dome_Impact) spInstance(new CGanesha_Dome_Impact, Engine::SmartDeleter<CGanesha_Dome_Impact>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGanesha_Dome_Impact::MakeClone()
{
	SP(CGanesha_Dome_Impact) spClone(new CGanesha_Dome_Impact, Engine::SmartDeleter<CGanesha_Dome_Impact>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	//spClone->m_spTransform->SetSize(_float3(0.5f, 1.f, 0.5f));
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CGanesha_Dome_Impact::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Ganesha_Charge");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"effect_Ring07");
	m_spTexture->AddTexture(L"effect_Ring07");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
}

void CGanesha_Dome_Impact::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_spDomeObject = Engine::GET_CUR_SCENE->ADD_CLONE(L"Ganesha_Dome", true);

	_float3 iPos = this->GetTransform()->GetPosition();
	m_spDomeObject->GetTransform()->SetPosition(_float3(iPos.x, iPos.y - 0.6f, iPos.z));

}

void CGanesha_Dome_Impact::FixedUpdate()
{
	__super::FixedUpdate();

}

void CGanesha_Dome_Impact::Update()
{
	__super::Update();

	m_fTime += GET_DT;
}

void CGanesha_Dome_Impact::LateUpdate()
{
	__super::LateUpdate();

}

void CGanesha_Dome_Impact::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", -3.5f * m_fTime);
	pEffect->SetBool("gPlayingAnim", true);
}

void CGanesha_Dome_Impact::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CGanesha_Dome_Impact::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CGanesha_Dome_Impact::OnDestroy()
{
	__super::OnDestroy();
	

}

void CGanesha_Dome_Impact::OnEnable()
{
	__super::OnEnable();

}

void CGanesha_Dome_Impact::OnDisable()
{
	__super::OnDisable();

}

void CGanesha_Dome_Impact::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
