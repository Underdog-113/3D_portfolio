#include "stdafx.h"
#include "YongScene.h"
#include "EmptyObject.h"
#include "DynamicMeshData.h"
#include "FRC.h"


CYongScene::CYongScene()
{
}


CYongScene::~CYongScene()
{
}

Engine::CScene * CYongScene::Create(void)
{
	CYongScene* pInstance = new CYongScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CYongScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CYongScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CYongScene::Start(void)
{
	__super::Start();
	{
		SP(Engine::CObject) spEmptyObject
			= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Parent");

		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Bronya");
		spEmptyObject->AddComponent<Engine::CTextureC>();
		spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		

		spEmptyObject = m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Weapon");

		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Weapon");
		spEmptyObject->AddComponent<Engine::CTextureC>();
		spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		
	}
}

void CYongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CYongScene::Update(void)
{
	__super::Update();
	
	EquipWeapon();
	
}

void CYongScene::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CYongScene::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CYongScene::OnEnable(void)
{
	__super::OnEnable();
	
}

void CYongScene::OnDisable(void)
{
	__super::OnDisable();
	
}

void CYongScene::InitPrototypes(void)
{
}

HRESULT CYongScene::Movement(_float DeltaTime)
{
	SP(Engine::CObject) momBox = FindObjectByName(L"Cube0");

	if (Engine::IMKEY_PRESS(KEY_UP))
	{
		momBox->GetTransform()->MoveForward(0.05f);
	}
	if (Engine::IMKEY_PRESS(KEY_LEFT))
	{
		momBox->GetTransform()->AddRotationY(-0.05f);
	}
	if (Engine::IMKEY_PRESS(KEY_RIGHT))
	{
		momBox->GetTransform()->AddRotationY(0.05f);
	}
	if (Engine::IMKEY_PRESS(KEY_DOWN))
	{
		momBox->GetTransform()->AddRotationX(0.05f);
	}
	if (Engine::IMKEY_PRESS(KEY_E))
	{
		momBox->GetTransform()->AddRotationZ(0.05f);
	}
	
	return S_OK;
}

void CYongScene::EquipWeapon()
{
	SP(Engine::CTransformC) pParentTransform;
	pParentTransform = static_cast<SP(Engine::CTransformC)>(FindObjectByName(L"Parent")->GetComponent<Engine::CTransformC>());

	SP(Engine::CTransformC) pWeaponTransform;
	pWeaponTransform = static_cast<SP(Engine::CTransformC)>(FindObjectByName(L"Weapon")->GetComponent<Engine::CTransformC>());

	if (m_pParentBoneMat == nullptr)
	{	

		Engine::CDynamicMeshData* pDM =
			static_cast<Engine::CDynamicMeshData*>(FindObjectByName(L"Parent")->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);

		if (nullptr == pDM)
		{
			MSG_BOX(__FILE__, L"ParentMat is Not Found SceneName : YongScene.cpp 73");
			ABORT;
		}

		const Engine::D3DXFRAME_DERIVED* pFrm = pDM->GetFrameByName("Bip002_L_Forearm");

		if (nullptr == pFrm)
		{
			MSG_BOX(__FILE__, L"pFrm is Not Found SceneName : YongScene.cpp 81");
			ABORT;
		}

		m_pParentBoneMat = &pFrm->CombinedTransformMatrix;

		
		m_pParentWorldMat = &pParentTransform->GetWorldMatrix();
	}

	
	//pWeaponTransform->SetRotationY(60.f);
	//pWeaponTransform->SetRotationY(40.f);
	if (Engine::IMKEY_PRESS(KEY_Q))
	{
		//pWeaponTransform->AddPositionX(1.f * GET_DT);
		pWeaponTransform->AddRotationX(1.f * GET_DT);

	}
	if (Engine::IMKEY_PRESS(KEY_E))
	{
		//pWeaponTransform->AddPositionY(1.f * GET_DT);
		pWeaponTransform->AddRotationY(1.f * GET_DT);

	}
	if (Engine::IMKEY_PRESS(KEY_Z))
	{
		//pWeaponTransform->AddPositionZ(1.f * GET_DT);
		pWeaponTransform->AddRotationZ(1.f * GET_DT);

	}
	if (Engine::IMKEY_PRESS(VK_UP))
	{
		pWeaponTransform->AddPositionX(-1.f * GET_DT);
	}
	if (Engine::IMKEY_PRESS(VK_DOWN))
	{
		pWeaponTransform->AddPositionY(-1.f * GET_DT);
	}
	if (Engine::IMKEY_PRESS(VK_LEFT))
	{
		pWeaponTransform->AddPositionZ(-1.f * GET_DT);
	}

	pWeaponTransform->SetRotation(_float3(30.2f, 23.8f, 1.6f));
	pWeaponTransform->SetPosition(_float3(1.1f, -0.22f, -0.6f));

	// 부모의 매트릭스 *= 본 매트릭스;
	pWeaponTransform->UpdateParentMatrix(m_pParentBoneMat);
		

}
