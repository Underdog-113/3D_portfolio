#include "stdafx.h"
#include "..\Header\EffectMaker.h"

#include "Valkyrie.h"

CEffectMaker::CEffectMaker()
{
}


CEffectMaker::~CEffectMaker()
{
}

SP(Engine::CObject) CEffectMaker::CreateEffect_Trail(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2, std::wstring texName3)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(objectKey, true, (_int)Engine::ELayerID::Effect, L"TrailEffect");

	spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::Effect);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName1);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName2);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName3);
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::MeshTrailShader_Glow);

	//spMeshEffect->GetTransform()->SetPosition(m_pOwner->GetTransform()->GetPosition());
	//spMeshEffect->GetTransform()->AddPositionY(m_pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset());

	return spMeshEffect;
}

SP(Engine::CObject) CEffectMaker::CreateEffect_AlphaMask(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(objectKey, true, (_int)Engine::ELayerID::Effect, L"AlphaMaskEffect");

	spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName1);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName2);
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);

	return spMeshEffect;
}

SP(Engine::CObject) CEffectMaker::CreateEffect_Dissolve(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(objectKey, true, (_int)Engine::ELayerID::Effect, L"DissolveEffect");

	spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::Effect);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName1);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName2);
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::DissolveShader_Glow);

	return spMeshEffect;
}

SP(Engine::CObject) CEffectMaker::CreateEffect_Dissolve(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2, std::wstring texName3)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(objectKey, true, (_int)Engine::ELayerID::Effect, L"DissolveEffect");

	spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::Effect);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName1);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName2);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName3);
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::DissolveShader_Glow);

	return spMeshEffect;
}

SP(Engine::CObject) CEffectMaker::CreateEffect_Fire(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(objectKey, true, (_int)Engine::ELayerID::Effect, L"FireEffect");

	spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName1);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName2);
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::FireShader);

	return spMeshEffect;
}

SP(Engine::CObject) CEffectMaker::CreateEffect_Laser(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2, std::wstring texName3)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(objectKey, true, (_int)Engine::ELayerID::Effect, L"LaserEffect");

	return spMeshEffect;
}

SP(Engine::CObject) CEffectMaker::CreateEffect_Switching()
{
	auto spEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Robot_Impact_Smoke", true, (_uint)Engine::ELayerID::Effect);
	spEffect->GetTransform()->SetPosition(CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition());
	//spEffect->GetTransform()->AddRotationZ(D3DXToRadian(90.f));
	spEffect->GetTransform()->SetSize(1.f, 0.2f, 1.f);

	return SP(Engine::CObject)();
}
