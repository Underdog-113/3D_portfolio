#include "stdafx.h"
#include "EffectToolScene.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "EmptyObject.h"
#include "MeshEffect.h"
#include "AttackTrail.h"
#include "SoftEffect.h"
#include "AttackRange_Editor.h"

CEffectToolScene::CEffectToolScene()
{
}

void CEffectToolScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	//DataStore Init
	m_pDataStore->InitDataMap((_uint)EDataID::NumOfDataID);
	m_pDataStore->AddDataSection(L"BasicObject", (_uint)EDataID::BasicObject);
	m_pDataStore->AddDataSection(L"Player", (_uint)EDataID::Player);
	m_pDataStore->AddDataSection(L"Scene", (_uint)EDataID::Scene);
	m_pDataStore->AddDataSection(L"Enemy", (_uint)EDataID::Enemy);
	m_pDataStore->AddDataSection(L"Effect", (_uint)EDataID::Effect);
	m_pDataStore->AddDataSection(L"UI", (_uint)EDataID::UI);
	m_pDataStore->AddDataSection(L"Stat", (_uint)EDataID::Stat);
	m_pDataStore->AddDataSection(L"Monster", (_uint)EDataID::Monster);
	m_pDataStore->AddDataSection(L"ClientObject", (_uint)EDataID::ClientObject);


	m_pDataStore->InitDataForScene(L"StaticScene", true);
	m_pMeshStore->InitMeshForScene(L"StaticScene", true);
	m_pTextureStore->InitTextureForScene(L"StaticScene", true);

	m_pDataStore->InitDataForScene(m_objectKey);
	m_pMeshStore->InitMeshForScene(m_objectKey);
	m_pTextureStore->InitTextureForScene(m_objectKey);

	InitPrototypes();
}

void CEffectToolScene::Start()
{
	m_isStarted = true;

	SP(Engine::CCamera) spCameraObject =
		std::dynamic_pointer_cast<Engine::CCamera>(m_pObjectFactory->AddClone(L"Camera", false));

	Engine::CCameraManager::GetInstance()->AddCamera(m_objectKey + L"BasicCamera", spCameraObject);
}

void CEffectToolScene::FixedUpdate()
{
	__super::FixedUpdate();
}

void CEffectToolScene::Update()
{
	__super::Update();
}

void CEffectToolScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CEffectToolScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CEffectToolScene::OnEnable(void)
{
	__super::OnEnable();
}

void CEffectToolScene::OnDisable(void)
{
	__super::OnDisable();
}

Engine::CScene * CEffectToolScene::Create()
{
	Engine::CScene* pEditorScene = new CEffectToolScene;
	pEditorScene->Awake((_int)ELayerID::NumOfLayerID);

	return pEditorScene;
}

void CEffectToolScene::Free()
{
	OnDestroy();
	delete this;
}

void CEffectToolScene::InitPrototypes(void)
{
	SP(Engine::CObject) spEmptyObjectPrototype(Engine::CEmptyObject::Create(false, this));
	ADD_PROTOTYPE(spEmptyObjectPrototype);

	SP(Engine::CCamera) spCameraPrototype(Engine::CCamera::Create(false, this));
	ADD_PROTOTYPE(spCameraPrototype);

	SP(CMeshEffect) spMeshEffect(CAttackTrail::Create(false, this));
	ADD_PROTOTYPE(spMeshEffect);

	SP(CSoftEffect) spSoftEffect(CSoftEffect::Create(false, this));
	ADD_PROTOTYPE(spSoftEffect);

	SP(CAttackRange_Editor) spAttackRange(CAttackRange_Editor::Create(false, this));
	ADD_PROTOTYPE(spAttackRange);
}
