#include "stdafx.h"
#include "Kiana_CatPaw_Atk04.h"

#pragma region Engine
#include "MeshC.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "CollisionC.h"
#include "Collider.h"
#pragma endregion

#include "AttackBall.h"
#include "Valkyrie.h"
#include "Monster.h"

CKiana_CatPaw_Atk04::CKiana_CatPaw_Atk04()
{
}


CKiana_CatPaw_Atk04::~CKiana_CatPaw_Atk04()
{
	OnDestroy();
}

SP(CKiana_CatPaw_Atk04) CKiana_CatPaw_Atk04::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_CatPaw_Atk04) spInstance(new CKiana_CatPaw_Atk04, Engine::SmartDeleter<CKiana_CatPaw_Atk04>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_CatPaw_Atk04::MakeClone(void)
{
	SP(CKiana_CatPaw_Atk04) spClone(new CKiana_CatPaw_Atk04, Engine::SmartDeleter<CKiana_CatPaw_Atk04>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CKiana_CatPaw_Atk04::OnEnable(void)
{
	__super::OnEnable();

	m_spTransform->AddPositionY(m_pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	m_spTransform->UpdateWorldMatrix();
}

