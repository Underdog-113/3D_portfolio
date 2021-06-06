#include "EngineStdafx.h"
#include "EmptyObject.h"

USING(Engine)
_uint CEmptyObject::m_s_uniqueID = 0;

CEmptyObject::CEmptyObject()
{
}


CEmptyObject::~CEmptyObject()
{
}

SP(CEmptyObject) CEmptyObject::Create(_bool isStatic, CScene* pScene)
{
	SP(CEmptyObject) spInstance(new CEmptyObject, SmartDeleter<CEmptyObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CEmptyObject::MakeClone(void)
{
	SP(CEmptyObject) spClone(new CEmptyObject, SmartDeleter<CEmptyObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<CTransformC>();

	return spClone;
}

void CEmptyObject::Awake(void)
{
	__super::Awake();
}

void CEmptyObject::Start(void)
{
	__super::Start();

	PickComponentToRender();
}

void CEmptyObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CEmptyObject::Update(void)
{
	__super::Update();
}

void CEmptyObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CEmptyObject::PreRender(void)
{
	m_spComponentToRender->PreRender(GetComponent<CGraphicsC>());
}

void CEmptyObject::PreRender(LPD3DXEFFECT pEffect)
{
	m_spComponentToRender->PreRender(GetComponent<CGraphicsC>(), pEffect);
}

void CEmptyObject::Render(void)
{
	m_spComponentToRender->Render(GetComponent<CGraphicsC>());
}

void CEmptyObject::Render(LPD3DXEFFECT pEffect)
{
	m_spComponentToRender->Render(GetComponent<CGraphicsC>(), pEffect);
}

void CEmptyObject::PostRender(void)
{
	m_spComponentToRender->PostRender(GetComponent<CGraphicsC>());
}

void CEmptyObject::PostRender(LPD3DXEFFECT pEffect)
{
	m_spComponentToRender->PostRender(GetComponent<CGraphicsC>(), pEffect);
}

void CEmptyObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CEmptyObject::OnEnable(void)
{
	__super::OnEnable();
}

void CEmptyObject::OnDisable(void)
{
	__super::OnDisable();
}

void CEmptyObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CEmptyObject::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	//if (ci.pOtherCollider->GetOwner()->GetCollisionID() == 0)
	//	ci.pOtherCollider->GetOwner()->GetTransform()->AddPosition(ci.normal * ci.penetLength);
}

void CEmptyObject::OnCollisionStay(Engine::_CollisionInfo ci)
{
	//if (ci.pOtherCollider->GetOwner()->GetCollisionID() == 0)
	//	ci.pOtherCollider->GetOwner()->GetTransform()->AddPosition(ci.normal * ci.penetLength);
}

void CEmptyObject::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CEmptyObject::PickComponentToRender(void)
{
	SP(CMeshC)		spMesh = GetComponent<CMeshC>();
	SP(CRectTexC)	spRectTex = GetComponent<CRectTexC>();
	SP(CTextC)		spText = GetComponent<CTextC>();

	
	if (spMesh != nullptr)
	{
		m_spComponentToRender = spMesh;
		return;
	}
	else if (spRectTex != nullptr)
	{
		m_spComponentToRender = spRectTex;
		return;
	}
	else if (spText != nullptr)
	{
		if (GetComponent<CGraphicsC>() == nullptr)
		{
			AddComponent<CGraphicsC>()->SetRenderID((_int)ERenderID::UI);
		}

		m_spComponentToRender = spText;
	}
}
