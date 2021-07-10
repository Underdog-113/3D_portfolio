#include "stdafx.h"
#include "FaceShader.h"
#include "Valkyrie.h"

CFaceShader::CFaceShader()
{
}


CFaceShader::~CFaceShader()
{
}

Engine::CShader * CFaceShader::Create(void)
{
	CFaceShader* pInstance = new CFaceShader;
	pInstance->Awake();

	return pInstance;
}


void CFaceShader::Free(void)
{
	__super::Free();
	
}

void CFaceShader::Awake(void)
{
	__super::Awake();
	
}

void CFaceShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	SetupWorldViewProj(spGC);
	
	_float4 playerDir = _float4(CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetForward(), 0);
	m_pEffect->SetVector("g_faceDir", &playerDir);

	m_pEffect->CommitChanges();
}
