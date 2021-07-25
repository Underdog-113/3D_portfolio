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
	m_eventCnt = 0;
	m_timer = 0.f;
	m_bSpawn = false;
}

void CGachBoxC::FixedUpdate(SP(CComponent) spThis)
{
}

void CGachBoxC::Update(SP(CComponent) spThis)
{
	if (m_eventCnt == 0 && GetOwner()->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->GetAniTimeline() >= 0.7f && GetOwner()->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->GetCurIndex() == 0)
	{
		Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
		Engine::CSoundManager::GetInstance()->StartSound(L"GachaBoxLand.wav", (_uint)Engine::EChannelID::UI_ButtonUI);
		GetOwner()->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(0);
		m_eventCnt++;
	}
	else if (m_eventCnt == 1)
	{
		if (!m_bSpawn)
		{
			SP(Engine::CObject) spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Robot_Impact_Smoke", true, (_uint)Engine::ELayerID::Effect);
			spObj->GetTransform()->SetPosition(_float3(0.2f, -0.5f, 0.f));
			spObj->GetTransform()->SetSize(_float3(4.5f, 4.5f, 4.5f));
			m_bSpawn = true;
		}
		m_timer += GET_DT;

		if (m_timer >= 1.f)
		{
			//GetOwner()->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->ChangeAniSet(1);
			m_eventCnt++;
			m_timer = 0.f;
		}
	}
	else if (m_eventCnt == 2)
	{
		m_spEndEff = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"GachaBox_Eff", true, (_uint)Engine::ELayerID::Effect);
		m_spEndEff->GetTransform()->SetPosition(_float3(0.2f, -0.1f, -1.f));
		m_spEndEff->GetTransform()->SetSize(_float3(0.f, 0.f, 0.f));

		m_eventCnt++;
	}
	else if (m_eventCnt == 3)
	{
		if (m_spEndEff != nullptr)
		{
			if (m_spEndEff->GetDeleteThis())
			{
				*m_production = false;
				m_isEnabled = false;
				GetOwner()->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(0);
				Engine::GET_CUR_SCENE->FindObjectByName(L"OutCanvas")->SetIsEnabled(true);
				m_spEndEff = nullptr;
			}
		}
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