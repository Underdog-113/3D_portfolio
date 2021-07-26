#include "stdafx.h"
#include "..\Header\ScoutMeteor.h"

_uint CScoutMeteor::m_s_uniqueID = 0;


CScoutMeteor::CScoutMeteor()
{
}


CScoutMeteor::~CScoutMeteor()
{
}

SP(CScoutMeteor) CScoutMeteor::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CScoutMeteor) spInstance(new CScoutMeteor, Engine::SmartDeleter<CScoutMeteor>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CScoutMeteor::MakeClone(void)
{
	SP(CScoutMeteor) spClone(new CScoutMeteor, Engine::SmartDeleter<CScoutMeteor>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_bBillboard = true;

	return spClone;
}

void CScoutMeteor::Awake(void)
{
	__super::Awake();
	m_spTexture->AddTexture(L"BallColor");
	m_spTexture->AddTexture(L"Scout_Meteor");
	m_spShader->AddShader((_int)EShaderID::SoftEffectShader_Glow);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spCollision = AddComponent<Engine::CCollisionC>();
	m_spCollision->
		AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::FloorRay, _float3(0, 0, 0), _float3(0, -1, 0), 0.2f));

}

void CScoutMeteor::Start(void)
{
	__super::Start();
	//AddComponent<Engine::CDebugC>();

	m_fAlphaWidth = 1.f;
	m_fAlphaHeight = 1.f;
	m_TilingX = 0;
	m_TilingY = 0;

	m_maxXIndex = 0;
	m_maxYIndex = 0;
	m_fTIme = 0.f;
}

void CScoutMeteor::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CScoutMeteor::Update(void)
{
	__super::Update();

	m_spTransform->AddPositionY(-8.f * GET_DT);
}

void CScoutMeteor::LateUpdate(void)
{
	__super::LateUpdate();
}

void CScoutMeteor::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
	pEffect->CommitChanges();
}

void CScoutMeteor::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);
}

void CScoutMeteor::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);
}

void CScoutMeteor::OnDestroy(void)
{
	__super::OnDestroy();
}

void CScoutMeteor::OnEnable(void)
{
	__super::OnEnable();
}

void CScoutMeteor::OnDisable(void)
{
	__super::OnDisable();
}

void CScoutMeteor::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CScoutMeteor::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	SP(Engine::CObject) spSoftEffect;

	for (_int i = 0; i < 4; ++i)
	{
		if (i == 0)
		{
			spSoftEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"SparkEffect", true);
			spSoftEffect->GetTransform()->SetPosition(ci.hitPoint.x + 1.2f, ci.hitPoint.y, ci.hitPoint.z);
			spSoftEffect->GetTransform()->SetRotation(0, D3DXToRadian(-90), D3DXToRadian(-15));
		}		
		else if (i == 1)
		{
			spSoftEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"SparkEffect", true);
			spSoftEffect->GetTransform()->SetPosition(ci.hitPoint.x + 0.7f, ci.hitPoint.y, ci.hitPoint.z + 1.5f);
			spSoftEffect->GetTransform()->SetRotation(0, D3DXToRadian(-75), D3DXToRadian(-15));
		}
		else if (i == 2)
		{
			spSoftEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"SparkEffect", true);
			spSoftEffect->GetTransform()->SetPosition(ci.hitPoint.x + -1.2f, ci.hitPoint.y, ci.hitPoint.z);
			spSoftEffect->GetTransform()->SetRotation(0, D3DXToRadian(90), D3DXToRadian(15));
		}
		else if (i == 3)
		{
			spSoftEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"SparkEffect", true);
			spSoftEffect->GetTransform()->SetPosition(ci.hitPoint.x + -1.2f, ci.hitPoint.y, ci.hitPoint.z + -1.5f);
			spSoftEffect->GetTransform()->SetRotation(0, D3DXToRadian(75), D3DXToRadian(15));
		}
	}

 	this->SetDeleteThis(true);
}

void CScoutMeteor::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CScoutMeteor::OnCollisionExit(Engine::_CollisionInfo ci)
{
}
