#include "stdafx.h"
#include "WooScene.h"
#include "EmptyObject.h"
#include "ObjectFactory.h"

#include "DynamicMeshData.h"
#include "StageControlTower.h"
#include "AniCtrl.h"

/* for.Monster */
#include "FSM_SpiderC.h"
//#include "FSMDefine_Spider.h"
#include "MO_Spider.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "FSM_KianaC.h"
#include "Kiana.h"

#include <ctime>
/**/

#include "Kiana_CatPaw_Atk01.h"
#include "Kiana_CatPaw_Atk02.h"
#include "Kiana_CatPaw_Atk03.h"
#include "Kiana_CatPaw_Atk04.h"
#include "Kiana_CatPaw_Atk05.h"
#include "Kiana_CatPaw_Ring_Atk01.h"
#include "Kiana_Pistol_USP45.h"

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

	m_pController = CStageControlTower::GetInstance();
	m_pController->Awake();
}

void CWooScene::Start(void)
{
	__super::Start();
	{
		CDataLoad* Load = new CDataLoad();
		Load->Setting();
		Load->ButtonLoad(this);
		Load->ImageLoad(this);
		Load->SliderLoad(this);
		Load->ScrollViewLoad(this);
		Load->CanvasLoad(this);
		Load->TextLoad(this);
		delete(Load);

		srand((_uint)time(NULL));

		CBattleUiManager::GetInstance()->Start(this);

		{
			SP(Engine::CObject) spEmptyObject1 
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Pivot");

			spEmptyObject1->AddComponent<Engine::CMeshC>()->AddMeshData(L"Pistol_USP45");
			spEmptyObject1->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject1->AddComponent<Engine::CTextureC>();
			spEmptyObject1->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spEmptyObject1->GetTransform()->SetSize(1, 1, 1);

			m_pivot = spEmptyObject1.get();

			auto cam = Engine::CCameraManager::GetInstance()->GetCamera(L"WooSceneBasicCamera");
			cam->SetTarget(spEmptyObject1);
			cam->SetTargetDist(6.f);
			CStageControlTower::GetInstance()->SetCurrentMainCam(cam);
		}

		// Kiana Body
		{
			SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", false, (_uint)ELayerID::Player, L"Kiana");

			m_spKiana = spKianaClone;
			m_spKiana->GetTransform()->SetPosition(0, 0, 0);
			m_pController->AddSquadMember(m_spKiana);
			m_pController->Start();
		}

		// Monster
		{
			/* Spider */
			//SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
			//spSpiderClone->GetTransform()->SetPosition(0, 0, 5);
			//spSpiderClone->GetTransform()->SetRotationY(D3DXToRadian(90));
			//m_spSpider = spSpiderClone;

			/* Sickle */
			SP(Engine::CObject) spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
			spSickleClone->GetTransform()->SetSize(2, 2, 2);
			spSickleClone->GetTransform()->SetPosition(0, 0, 10);
			spSickleClone->GetTransform()->SetRotationY(D3DXToRadian(90));
			m_spSickle = spSickleClone;

			/* Ganesha */
			//SP(Engine::CObject) spGaneshaClone = ADD_CLONE(L"MB_Ganesha", true, (_uint)ELayerID::Enemy, L"MB_Ganesha");
			//spGaneshaClone->GetTransform()->SetSize(2, 2, 2);
			//spGaneshaClone->GetTransform()->SetPosition(0, 0, 10);
			//spGaneshaClone->GetTransform()->SetRotationY(D3DXToRadian(90));
			//m_spGanesha = spGaneshaClone;

			//m_fsm = m_spSpider->GetComponent<CFSM_SpiderC>();
			m_fsm = m_spSickle->GetComponent<CFSM_SickleC>();
			//m_fsm = m_spGanesha->GetComponent<CFSM_GaneshaC>();
		}
	}

	//CDataLoad* Load = new CDataLoad();
	//Load->Setting();
	//Load->ToolLoad(this);
	//delete(Load);
}

void CWooScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CWooScene::Update(void)
{
	__super::Update();

	m_pController->Update();
	m_pivot->GetTransform()->SetPosition(m_spKiana->GetTransform()->GetPosition());
	m_pivot->GetTransform()->SetPositionY(0.f);

	SicklePattern0();
	SicklePattern1();
	SicklePattern2();
	SicklePattern3();
	//SpiderPattern0();
	//GaneshaPattern0();
	//GaneshaPattern1();
	//GaneshaPattern2();
}

void CWooScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CWooScene::OnDestroy(void)
{
	__super::OnDestroy();

	m_pController->DestroyInstance();
	m_pController = nullptr;
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
	_float3 tPos = m_spKiana->GetTransform()->GetPosition(); // target pos
	_float3 mPos = m_spSickle->GetTransform()->GetPosition(); // monster pos
	//_float mSpeed = 1.f;

	_float len = D3DXVec3Length(&(tPos - mPos));

	CoolTime(m_sickleAtkTime, m_sickleAtkCool, m_sickleAtkReady);
	CoolTime(m_sickleWalkTime, m_sickleWalkCool, m_sickleWalkReady);

	static_cast<CMO_Sickle*>(m_spSickle.get())->ChaseTarget(tPos);

	if (false == m_sicklePattern0)
		return;

	//m_sickleAtkDis = 1.f;

	// 상대가 공격 범위 밖이고
	if (len > m_sickleAtkDis)
	{
		// 공격1 상태면
		if (Name_Sickle_Attack_1 == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
		{
			m_fsm->ChangeState(Name_Sickle_Walk_Back);
			m_sicklePattern1 = false;
			m_sicklePattern2 = true;
		}
		// 공격2 상태면
		if (Name_Sickle_Attack_2 == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
		{
			m_fsm->ChangeState(Name_Sickle_Walk_Back);
			m_sicklePattern3 = false;
			m_sicklePattern2 = true;
		}

		// 내가 대기 상태면 이동 애니로 변경
		if (Name_Sickle_StandBy == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
		{
			m_fsm->ChangeState(Name_Sickle_Walk_Forward);
		}
		// 내가 이동 중이라면
		else if (Name_Sickle_Walk_Forward == m_fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			m_spSickle->GetTransform()->SetPosition(mPos);
		}
		// 내가 뒤로 이동 중이라면
		else if (Name_Sickle_Walk_Back == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd() && false == m_sickleWalkReady)
		{
			_float3 dir = tPos - mPos;

			mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			m_spSickle->GetTransform()->SetPosition(mPos);
		}
		// 내가 뒤로 이동 중이라면
		else if (Name_Sickle_Walk_Back == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd() && true == m_sickleWalkReady)
		{
			m_fsm->ChangeState(Name_Sickle_Walk_Forward);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_sickleAtkDis)
	{
		// 뒤로 이동 상태고, 애니가 끝났고, walkReady가 true라면 대기로 변경
		if (Name_Sickle_Walk_Back == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd() && true == m_sickleWalkReady)
		{
			m_fsm->ChangeState(Name_Sickle_StandBy);
		}
		
		// 이동 상태라면 대기로 변경
		if (Name_Sickle_Walk_Forward == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
		{
			m_fsm->ChangeState(Name_Sickle_StandBy);
			m_sicklePattern0 = false;

			// 랜덤으로 공격 패턴 정함
			m_sicklePattern3 = true;
		}
		
		// 공격1 상태고, 애니가 끝났다면 
		if (Name_Sickle_Attack_1 == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
		{
			m_fsm->ChangeState(Name_Sickle_Walk_Back);
			m_sicklePattern1 = false;
			m_sicklePattern2 = true;
		}
		if (Name_Sickle_Attack_2 == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
		{
			m_fsm->ChangeState(Name_Sickle_Walk_Back);
			m_sicklePattern3 = false;
			m_sicklePattern2 = true;
		}
	}
}

void CWooScene::SicklePattern1()
{
	if (false == m_sicklePattern1)
		return;

	m_fsm->ChangeState(Name_Sickle_Attack_1);
	m_sickleAtkReady = false;
	m_sicklePattern0 = true;
	m_sicklePattern1 = false;
}

void CWooScene::SicklePattern2()
{
	if (false == m_sicklePattern2)
		return;

	m_fsm->ChangeState(Name_Sickle_Walk_Back);
	m_sickleWalkReady = false;
	m_sicklePattern0 = true;
	m_sicklePattern2 = false;
}

void CWooScene::SicklePattern3()
{
	if (false == m_sicklePattern3)
		return;

	m_fsm->ChangeState(Name_Sickle_Attack_2);
	m_sickleWalkReady = false;
	m_sicklePattern0 = true;
	m_sicklePattern3 = false;
}

void CWooScene::GaneshaPattern0()
{
	//_float3 tPos = m_spKiana->GetTransform()->GetPosition(); // target pos
	//_float3 mPos = m_spGanesha->GetTransform()->GetPosition(); // monster pos
	////_float mSpeed = 1.f;

	//_float len = D3DXVec3Length(&(tPos - mPos));

	//CoolTime(m_atkTime, m_sickleAtkCool, m_atkReady);
	//CoolTime(m_walkTime, m_sickleWalkCool, m_walkReady);

	//static_cast<CMB_Ganesha*>(m_spGanesha.get())->ChaseTarget(tPos);

	//if (false == m_pattern0)
	//	return;

	//// 상대가 공격 범위 밖이고
	//if (len > m_sickleAtkDis)
	//{
	//	// 공격 상태고, 애니가 끝났다면 
	//	if (Name_Attack01 == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
	//	{
	//		m_fsm->ChangeState(Name_Jump_Back);
	//		m_pattern1 = false;
	//		m_pattern2 = true;
	//	}

	//	// 내가 대기 상태면 이동 애니로 변경
	//	if (Name_StandBy == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
	//	{
	//		m_fsm->ChangeState(Name_Run);
	//	}
	//	// 내가 이동 중이라면
	//	else if (Name_Run == m_fsm->GetCurStateString())
	//	{
	//		_float3 dir = tPos - mPos;

	//		mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
	//		m_spGanesha->GetTransform()->SetPosition(mPos);
	//	}
	//	// 내가 뒤로 이동 중이라면
	//	else if (Name_Jump_Back == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd() && false == m_walkReady)
	//	{
	//		_float3 dir = tPos - mPos;

	//		mPos -= *D3DXVec3Normalize(&dir, &dir) * 1.5f;
	//		m_spGanesha->GetTransform()->SetPosition(mPos);
	//		m_fsm->GetDM()->GetAniCtrl()->SetSpeed(0.5f);
	//		m_walkReady = true;
	//	}
	//	// 내가 뒤로 이동 중이라면
	//	else if (Name_Jump_Back == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd() && true == m_walkReady)
	//	{
	//		m_fsm->ChangeState(Name_Run);
	//	}
	//}
	//// 상대가 공격 범위 안이고
	//else if (len <= m_sickleAtkDis)
	//{
	//	// 뒤로 이동 상태고, 애니가 끝났고, walkReady가 true라면 대기로 변경
	//	if (Name_Jump_Back == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd() && true == m_walkReady)
	//	{
	//		m_fsm->ChangeState(Name_StandBy);
	//	}
	//	
	//	// 이동 상태라면 대기로 변경
	//	if (Name_Run == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
	//	{
	//		m_fsm->ChangeState(Name_StandBy);
	//		m_pattern0 = false;
	//		m_pattern1 = true;
	//	}
	//	
	//	// 공격 상태고, 애니가 끝났다면 
	//	if (Name_Attack01 == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
	//	{
	//		m_fsm->ChangeState(Name_Run);
	//		m_pattern1 = false;
	//		m_pattern2 = true;
	//	}
	//}
}

void CWooScene::GaneshaPattern1()
{
	//if (false == m_pattern1)
	//	return;

	//m_fsm->ChangeState(Name_Attack01);
	//m_atkReady = false;
	//m_pattern0 = true;
	//m_pattern1 = false;
}

void CWooScene::GaneshaPattern2()
{
	//if (false == m_pattern2)
	//	return;

	//m_fsm->ChangeState(Name_Jump_Back);
	//m_walkReady = false;
	//m_pattern0 = true;
	//m_pattern2 = false;
}

void CWooScene::CoolTime(_float& curTime, _float maxTime, _bool& readyType)
{
	if (true == readyType)
		return;

	if (maxTime <= curTime)
	{
		readyType = true;
		curTime = 0.f;
		return;
	}
	
	curTime += GET_DT;
}

void CWooScene::InitPrototypes(void)
{
	SP(CKiana) spKianaPrototype(CKiana::Create(false, this));
	ADD_PROTOTYPE(spKianaPrototype);

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

	SP(CKiana_Pistol_USP45) spPistol(CKiana_Pistol_USP45::Create(false, this));
	ADD_PROTOTYPE(spPistol);
}
