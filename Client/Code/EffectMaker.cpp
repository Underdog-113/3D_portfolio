#include "stdafx.h"
#include "..\Header\EffectMaker.h"


CEffectMaker::CEffectMaker()
{
}


CEffectMaker::~CEffectMaker()
{
}

SP(Engine::CObject) CEffectMaker::CreateEffect_Trail(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2, std::wstring texName3, std::wstring objName)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(objectKey, true, (_int)Engine::ELayerID::Effect, objName);

	spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName1);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName2);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName3);
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::MeshTrailShader);

	//spMeshEffect->GetTransform()->SetPosition(m_pOwner->GetTransform()->GetPosition());
	//spMeshEffect->GetTransform()->AddPositionY(m_pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset());

	return spMeshEffect;
}

SP(Engine::CObject) CEffectMaker::CreateEffect_AlphaMask(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2, std::wstring objName)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(objectKey, true, (_int)Engine::ELayerID::Effect, objName);

	spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName1);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName2);
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);

	return spMeshEffect;
}

SP(Engine::CObject) CEffectMaker::CreateEffect_Dissolve(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2, std::wstring objName)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(objectKey, true, (_int)Engine::ELayerID::Effect, objName);

	spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName1);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName2);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName2);
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::DissolveShader);

	return spMeshEffect;
}

SP(Engine::CObject) CEffectMaker::CreateEffect_Fire(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2, std::wstring objName)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(objectKey, true, (_int)Engine::ELayerID::Effect, objName);

	spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName1);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName2);
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::FireShader);

	return spMeshEffect;
}
