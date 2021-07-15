#include "stdafx.h"
#include "..\Header\ParticleShader.h"


CParticleShader::CParticleShader()
{
}


CParticleShader::~CParticleShader()
{
}

Engine::CShader * CParticleShader::Create(void)
{
	CParticleShader* pInstance = new CParticleShader;
	pInstance->Awake();

	return pInstance;
}

void CParticleShader::Free(void)
{
	__super::Free();
}

void CParticleShader::Awake(void)
{
	__super::Awake();
}

void CParticleShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetWorldMatrix();
	viewMat = Engine::GET_MAIN_CAM->GetViewMatrix();
	projMat = Engine::GET_MAIN_CAM->GetProjMatrix();

	m_pEffect->SetMatrix("worldMatrix", &worldMat);
	m_pEffect->SetMatrix("viewMatrix", &viewMat);
	m_pEffect->SetMatrix("projectionMatrix", &projMat);	
}
