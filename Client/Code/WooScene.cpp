#include "stdafx.h"
#include "WooScene.h"
#include "EmptyObject.h"
#include "ObjectFactory.h"

#include "DynamicMeshData.h"
#include "AniCtrl.h"

#include "FSM_SpiderC.h"
//#include "FSMDefine_Spider.h"
#include "MO_Spider.h"

#include "FSM_AxeC.h"
//#include "FSMDefine_Axe.h"
#include "MO_Axe.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "Kiana_CatPaw_Atk01.h"
#include "Kiana_CatPaw_Atk02.h"
#include "Kiana_CatPaw_Atk03.h"
#include "Kiana_CatPaw_Atk04.h"
#include "Kiana_CatPaw_Atk05.h"
#include "Kiana_CatPaw_Ring_Atk01.h"

#include "FSM_KianaC.h"
#include "Kiana.h"
#include "StageController.h"

#include "DataLoad.h"
CWooScene::CWooScene()
{
}


CWooScene::~CWooScene()
{
	m_pController->DestroyInstance();
}

CClientScene* CWooScene::Create(void)
{
	CWooScene* pInstance = new CWooScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CWooScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CWooScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	m_pController = CStageController::GetInstance();
	m_pController->Awake();
}

void CWooScene::Start(void)
{
	__super::Start();
	{
		//{
		//	SP(Engine::CObject) spEmptyObject1
		//		= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Pivot");

		//	spEmptyObject1->AddComponent<Engine::CMeshC>()->AddMeshData(L"Pistol_USP45");
		//	spEmptyObject1->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		//	spEmptyObject1->AddComponent<Engine::CTextureC>();
		//	spEmptyObject1->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		//	spEmptyObject1->GetTransform()->SetSize(1, 1, 1);

		//	m_pivot = spEmptyObject1.get();

		//	Engine::CCameraManager::GetInstance()->GetCamera(L"WooSceneBasicCamera")->SetTarget(spEmptyObject1);
		//}

		//// Kiana Body
		//{
		//	SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", false, (_uint)ELayerID::Player, L"Kiana");

		//	m_spKiana = spKianaClone;
		//	m_pController->AddSquadMember(m_spKiana);
		//	m_pController->Start();
		//}

		//// Monster
		//{
		//	SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
		//	spSpiderClone->GetTransform()->SetPosition(0, 0, 5);
		//	spSpiderClone->GetTransform()->SetRotationY(D3DXToRadian(90));
		//	m_spSpider = spSpiderClone;

		//	SP(Engine::CObject) spAxeClone = ADD_CLONE(L"MO_Axe", true, (_uint)ELayerID::Enemy, L"MO_Axe");
		//	spAxeClone->GetTransform()->SetPosition(0, 0, 3);
		//	spAxeClone->GetTransform()->SetRotationY(D3DXToRadian(90));
		//	m_spAxe = spAxeClone;

		//	SP(Engine::CObject) spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
		//	//spSickleClone->GetTransform()->SetSize(5, 5, 5);
		//	spSickleClone->GetTransform()->SetPosition(0, 0, 10);
		//	spSickleClone->GetTransform()->SetRotationY(D3DXToRadian(90));
		//	m_spSickle = spSickleClone;

		//	m_fsm = m_spSickle->GetComponent<CFSM_SickleC>();
		//	//m_fsm = m_spSpider->GetComponent<CFSM_SpiderC>();
		//	//m_fsm = m_spAxe->GetComponent<CFSM_SickleC>();
		//}

	}

	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ToolLoad(this);
	delete(Load);

}

void CWooScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CWooScene::Update(void)
{
	__super::Update();

	//m_pController->Update();
	//m_pivot->GetTransform()->SetPosition(m_spKiana->GetTransform()->GetPosition());
	//m_pivot->GetTransform()->SetPositionY(0.f);
	
	if (Engine::IMKEY_DOWN(KEY_Q))
		m_pattern1 = true;

	//SicklePattern0();
	//SpiderPattern0();

	//AxePattern0();
	//AxePattern1();

}

void CWooScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CWooScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CWooScene::OnEnable(void)
{
	__super::OnEnable();
}

void CWooScene::OnDisable(void)
{
	__super::OnDisable();
}

void CWooScene::SpiderPattern0()
{
	//if (Name_Walk_Forward != m_fsm->GetCurStateString())
	//	m_fsm->ChangeState(Name_Walk_Forward);

	//_float3 tPos = m_spKiana->GetTransform()->GetPosition();
	//_float3 mPos = m_spSickle->GetTransform()->GetPosition();
	//_float mSpeed = 1.f;

	//static_cast<CMO_Spider*>(m_spSickle.get())->ChaseTarget(tPos);

	//_float3 dir = tPos - mPos;

	//mPos += *D3DXVec3Normalize(&dir, &dir) * mSpeed * GET_DT;
	//m_spSickle->GetTransform()->SetPosition(mPos);
}

void CWooScene::SicklePattern0()
{
	_float3 tPos = m_spKiana->GetTransform()->GetPosition();
	_float3 mPos = m_spSickle->GetTransform()->GetPosition();
	_float mSpeed = 1.f;

	_float3 *len = &(tPos - mPos);

	if (D3DXVec3Length(len) < 1.5f)
	{
		m_fsm->ChangeState(Name_StandBy);
		return;
	}

	if (Name_Walk_Forward != m_fsm->GetCurStateString())
		m_fsm->ChangeState(Name_Walk_Forward);

	static_cast<CMO_Sickle*>(m_spSickle.get())->ChaseTarget(tPos);

	_float3 dir = tPos - mPos;

	mPos += *D3DXVec3Normalize(&dir, &dir) * mSpeed * GET_DT;
	m_spSickle->GetTransform()->SetPosition(mPos);
}

void CWooScene::AxePattern0()
{
	//if (Name_Run != m_fsm->GetCurStateString())
	//	m_fsm->ChangeState(Name_Run);

	//_float3 tPos = m_spKiana->GetTransform()->GetPosition();
	//_float3 mPos = m_spAxe->GetTransform()->GetPosition();
	//_float mSpeed = 0.1f;

	//static_cast<CMO_Axe*>(m_spAxe.get())->ChaseTarget(tPos);

	//_float3 dir = tPos - mPos;

	//mPos += *D3DXVec3Normalize(&dir, &dir) * mSpeed * GET_DT;
	//m_spAxe->GetTransform()->SetPosition(mPos);
}

void CWooScene::AxePattern1()
{
	/*
	1. attack1
	4. idle
	5. left walk
	6. idle
	*/

	//if (Engine::IMKEY_DOWN(KEY_Q))
	//{
	//	if (false == m_fsm->GetPattern1())
	//		m_fsm->SetPattern1(true);
	//	else
	//		m_fsm->SetPattern1(false);
	//}

	if (false == m_pattern1)
		return;

	m_accTime += GET_DT;

	//if (0 == m_curPatternIdx)
	//{
	//	m_fsm->ChangeState(Name_Attack_1);
	//	++m_curPatternIdx;
	//	return;
	//}
	
	//if (Name_Attack_1 == m_fsm->GetCurStateString() && 0.8f <= m_fsm->GetDM()->GetAniTimeline())
	//{
	//	m_fsm->ChangeState(Name_Attack_2);
	//	return;
	//}

	//if (Name_Attack_2 == m_fsm->GetCurStateString() && 0.8f <= m_fsm->GetDM()->GetAniTimeline())
	//{
	//	m_fsm->ChangeState(Name_IDLE);
	//	EndPattern();
	//	return;
	//}
}

void CWooScene::AxePattern2()
{
}

void CWooScene::PlayOnceAni(std::wstring playAni, std::wstring nextAni)
{
	if (playAni != m_fsm->GetCurStateString())
		m_fsm->ChangeState(playAni);

	else if (m_fsm->GetDM()->GetAniTimeline() >= 0.8f)
		m_fsm->ChangeState(nextAni);
}

void CWooScene::PlayAni(std::wstring ani)
{
	//if (ani != m_fsm->GetCurStateString())
	//	m_fsm->ChangeState(ani);
}

void CWooScene::EndPattern()
{
	m_pattern1 = false;
	m_curPatternIdx = 0;
	m_accTime = 0.f;
}

void CWooScene::InitPrototypes(void)
{
	SP(CKiana_CatPaw_Atk01) spPaw01(CKiana_CatPaw_Atk01::Create(false, this));
	ADD_PROTOTYPE(spPaw01);

	SP(CKiana_CatPaw_Atk02) spPaw02(CKiana_CatPaw_Atk02::Create(false, this));
	ADD_PROTOTYPE(spPaw02);

	SP(CKiana_CatPaw_Atk03) spPaw03(CKiana_CatPaw_Atk03::Create(false, this));
	ADD_PROTOTYPE(spPaw03);

	SP(CKiana_CatPaw_Atk04) spPaw04(CKiana_CatPaw_Atk04::Create(false, this));
	ADD_PROTOTYPE(spPaw04);

	SP(CKiana_CatPaw_Atk05) spPaw05(CKiana_CatPaw_Atk05::Create(false, this));
	ADD_PROTOTYPE(spPaw05);

	SP(CKiana_CatPaw_Ring_Atk01) spPawRing01(CKiana_CatPaw_Ring_Atk01::Create(false, this));
	ADD_PROTOTYPE(spPawRing01);

	SP(CKiana) spKianaPrototype(CKiana::Create(false, this));
	ADD_PROTOTYPE(spKianaPrototype);
}
