#include "stdafx.h"
#include "..\Header\EffectMaker.h"


CEffectMaker::CEffectMaker()
{
}


CEffectMaker::~CEffectMaker()
{
}

SP(Engine::CObject) CEffectMaker::CreateEffect(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2, std::wstring objName)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(objectKey, true, (_int)ELayerID::Effect, objName);

	spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName1);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(texName2);
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::MeshTrailShader);

	spMeshEffect->GetTransform()->SetPosition(m_pOwner->GetTransform()->GetPosition());
	spMeshEffect->GetTransform()->AddPositionY(m_pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset());

	return spMeshEffect;
}
