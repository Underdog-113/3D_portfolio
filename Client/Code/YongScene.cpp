#include "stdafx.h"
#include "YongScene.h"
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
		SP(Engine::CObject) spEmptyObject = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Map, L"Cube0");

		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"waterplane");
		//spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		spEmptyObject->AddComponent<Engine::CTextureC>()->AddTexture(L"water", 0);
		spEmptyObject->GetComponent<Engine::CTextureC>()->AddTexture(L"WaterNormalMap", 0);
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		spEmptyObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::WaterShader);

		spEmptyObject = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Enemy, L"Cube0");
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::Particle);
		spEmptyObject->AddComponent<Engine::CParticleSystemC>();

		spEmptyObject->GetTransform()->SetSize(2, 2, 2);
		spEmptyObject->GetTransform()->SetPosition(3, 0, 0);

		m_pObjectFactory->AddClone(L"MO_Spider", true, (_int)ELayerID::Enemy, L"MO_Spider");

		//	// Save & Load Ex
		//	_int numOfMeshEffect;
		//	GET_VALUE(false, (_int)EDataID::EFFECT, m_objectKey + L"_EffectData", L"numOfMeshEffect", numOfMeshEffect);

		//	for (_int i = 0; I < numO!fMeshEffect; ++i)
		//	{
		//		SP(CMeshEffect) spMeshEffect = ADD_CLONE(L"MeshEffect", true, (_int)ELayerID::Effect);

		//		_int numOfTexture;
		//		GET_VALUE(false, (_int)EDataID::EFFECT, m_objectKey + L"_EffectData", L"numOfTexture" + std::to_wstring(i), numOfTexture);
		//		for (_int j = 0; j < numOfTexture; ++j)
		//		{
		//			std::wstring curTexKey;
		//			GET_VALUE(false, (_int)EDataID::EFFECT, m_objectKey + L"_EffectData", L"set" + std::to_wstring(i)
		//				+ L"_texkey" + std::to_wstring(j), curTexKey);
		//			spMeshEffect->GetTexture()->AddTexture(curTexKey);
		//		}

		//	}
		}		
}

void CYongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CYongScene::Update(void)
{
	__super::Update();
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
