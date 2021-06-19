#include "stdafx.h"
#include "..\Header\MB_Bronya.h"
#include "DynamicMeshData.h"

CMB_Bronya::CMB_Bronya()
{
}

CMB_Bronya::~CMB_Bronya()
{
	OnDestroy();
}

SP(Engine::CObject) CMB_Bronya::MakeClone(void)
{
	SP(CMB_Bronya) spClone(new CMB_Bronya, Engine::SmartDeleter<CMB_Bronya>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CMB_Bronya::Awake(void)
{
	__super::Awake();
}

void CMB_Bronya::Start(void)
{
	__super::Start();
	
	SP(Engine::CObject) spEmptyObject
		= m_pScene->GetObjectFactory()->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Weapon");

	spEmptyObject = m_pScene->GetObjectFactory()->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Weapon");

	spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Weapon");
	spEmptyObject->AddComponent<Engine::CTextureC>();
	spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);

}

void CMB_Bronya::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMB_Bronya::Update(void)
{
	__super::Update();

	EquipWeapon();
}

void CMB_Bronya::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMB_Bronya::PreRender(LPD3DXEFFECT pEffect)
{
}

void CMB_Bronya::Render(LPD3DXEFFECT pEffect)
{
}

void CMB_Bronya::PostRender(LPD3DXEFFECT pEffect)
{

}

void CMB_Bronya::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMB_Bronya::OnEnable(void)
{
	__super::OnEnable();
}

void CMB_Bronya::OnDisable(void)
{
	__super::OnDisable();
}

void CMB_Bronya::SetBasicName(void)
{
}

void CMB_Bronya::EquipWeapon()
{
	SP(Engine::CTransformC) pParentTransform;
	pParentTransform = static_cast<SP(Engine::CTransformC)>(m_pScene->FindObjectByName(L"Bronya")->GetComponent<Engine::CTransformC>());

	SP(Engine::CTransformC) pWeaponTransform;
	pWeaponTransform = static_cast<SP(Engine::CTransformC)>(m_pScene->FindObjectByName(L"Weapon")->GetComponent<Engine::CTransformC>());

	if (m_pParentBoneMat == nullptr)
	{
		Engine::CDynamicMeshData* pDM =
			static_cast<Engine::CDynamicMeshData*>(m_pScene->FindObjectByName(L"Bronya")->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);

		if (nullptr == pDM)
		{
			MSG_BOX(__FILE__, L"ParentMat is Not Found SceneName : MB_Bronya.cpp 107");
			ABORT;
		}

		const Engine::D3DXFRAME_DERIVED* pFrm = pDM->GetFrameByName("Bip002_L_Forearm");

		if (nullptr == pFrm)
		{
			MSG_BOX(__FILE__, L"pFrm is Not Found SceneName :  MB_Bronya.cpp 115");
			ABORT;
		}

		m_pParentBoneMat = &pFrm->CombinedTransformMatrix;


		m_pParentWorldMat = &pParentTransform->GetWorldMatrix();
	}

	pWeaponTransform->SetRotation(_float3(30.2f, 23.8f, 1.6f));
	pWeaponTransform->SetPosition(_float3(1.1f, -0.22f, -0.6f));

	// 부모의 매트릭스 *= 본 매트릭스;
	pWeaponTransform->UpdateParentMatrix(m_pParentBoneMat);
}

SP(CMB_Bronya) CMB_Bronya::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMB_Bronya) spInstance(new CMB_Bronya, Engine::SmartDeleter<CMB_Bronya>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

