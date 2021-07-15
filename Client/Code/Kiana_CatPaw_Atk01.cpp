#include "stdafx.h"
#include "Kiana_CatPaw_Atk01.h"

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

CKiana_CatPaw_Atk01::CKiana_CatPaw_Atk01()
{
}


CKiana_CatPaw_Atk01::~CKiana_CatPaw_Atk01()
{
	OnDestroy();
}

SP(CKiana_CatPaw_Atk01) CKiana_CatPaw_Atk01::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_CatPaw_Atk01) spInstance(new CKiana_CatPaw_Atk01, Engine::SmartDeleter<CKiana_CatPaw_Atk01>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_CatPaw_Atk01::MakeClone(void)
{
	SP(CKiana_CatPaw_Atk01) spClone(new CKiana_CatPaw_Atk01, Engine::SmartDeleter<CKiana_CatPaw_Atk01>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CKiana_CatPaw_Atk01::OnEnable(void)
{
	m_forwardOffset = m_pOwner->GetTransform()->GetForward() * 0.4f;
	__super::OnEnable();

	m_spTransform->UpdateWorldMatrix();
}
