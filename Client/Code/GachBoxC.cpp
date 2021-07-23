#include "Stdafx.h"
#include "GachBoxC.h"
#include "AniCtrl.h"

CGachBoxC::CGachBoxC()
{
}

CGachBoxC::~CGachBoxC()
{
	OnDestroy();
}

SP(Engine::CComponent) CGachBoxC::MakeClone(Engine::CObject *pObject)
{
	SP(CGachBoxC) spClone(new CGachBoxC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CGachBoxC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CGachBoxC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

}

void CGachBoxC::FixedUpdate(SP(CComponent) spThis)
{
}

void CGachBoxC::Update(SP(CComponent) spThis)
{
	if (GetOwner()->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->IsAnimationEnd())
	{
		*m_production = false;
		m_isEnabled = false;
		GetOwner()->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(0);
		Engine::GET_CUR_SCENE->FindObjectByName(L"OutCanvas")->SetIsEnabled(true);
	}
}

void CGachBoxC::LateUpdate(SP(CComponent) spThis)
{

}

void CGachBoxC::OnDestroy()
{
}

void CGachBoxC::OnEnable()
{
	__super::OnEnable();
}

void CGachBoxC::OnDisable()
{
	__super::OnDisable();
}