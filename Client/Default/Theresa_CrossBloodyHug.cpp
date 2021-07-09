#include "stdafx.h"
#include "Theresa_CrossBloodyHug.h"

#pragma region Engine
#include "MeshC.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#pragma endregion


CTheresa_CrossBloodyHug::CTheresa_CrossBloodyHug()
{
}


CTheresa_CrossBloodyHug::~CTheresa_CrossBloodyHug()
{
	OnDestroy();
}

SP(CTheresa_CrossBloodyHug) CTheresa_CrossBloodyHug::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa_CrossBloodyHug) spInstance(new CTheresa_CrossBloodyHug, Engine::SmartDeleter<CTheresa_CrossBloodyHug>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa_CrossBloodyHug::MakeClone(void)
{
	SP(CTheresa_CrossBloodyHug) spClone(new CTheresa_CrossBloodyHug, Engine::SmartDeleter<CTheresa_CrossBloodyHug>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CTheresa_CrossBloodyHug::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::Player;
	m_dataID = (_int)EDataID::Player;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
}

void CTheresa_CrossBloodyHug::Start(void)
{
	__super::Start();

	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetReplay(false);
	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(0.f);
	m_layerID = (_int)ELayerID::Attack;

	m_spCrossBlade = GetScene()->ADD_CLONE(L"Theresa_CrossBlade", true, (_uint)ELayerID::Player, L"CrossBlade");
	m_spCrossBlade->SetIsEnabled(false);
}

void CTheresa_CrossBloodyHug::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CTheresa_CrossBloodyHug::Update(void)
{
	__super::Update();

	// sp 12, 10초, 2초동안 0.25초마다 한번씩 벤다 200퍼
	switch (m_skillState)
	{
	case CTheresa_CrossBloodyHug::Ready:
		break;
	case CTheresa_CrossBloodyHug::Fall:
		FallDown();
		break;
	case CTheresa_CrossBloodyHug::Stretch:
		StretchBlade();
		break;
	case CTheresa_CrossBloodyHug::Roll:
		RollBlade();
		break;
	case CTheresa_CrossBloodyHug::End:
		EndSkill();
		break;
	default:
		break;
	}
	// 십자가 공중에 소환


	// 바닥에 꼿고
	// 펼치기 애니메이션
	// 바로 칼날 소환해서 빙글빙글
	if (m_beginAnimEnd)
	{
		m_activeTimer += GET_DT;

		if (m_activeTimer > m_activeDuration)
		{
			// remove effect
			SetIsEnabled(false);

		}
	}

	// 끝나면 ㅂㅂ


}

void CTheresa_CrossBloodyHug::LateUpdate(void)
{
	__super::LateUpdate();
}

void CTheresa_CrossBloodyHug::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CTheresa_CrossBloodyHug::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa_CrossBloodyHug::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CTheresa_CrossBloodyHug::OnDestroy(void)
{
	__super::OnDestroy();
}

void CTheresa_CrossBloodyHug::OnEnable(void)
{
	__super::OnEnable();
	m_fallTimer = 0.f;
	m_activeTimer = 0.f;
	m_fallStartY = m_spTransform->GetPosition().y;
}

void CTheresa_CrossBloodyHug::OnDisable(void)
{
	__super::OnDisable();
}

void CTheresa_CrossBloodyHug::SetBasicName(void)
{
}

void CTheresa_CrossBloodyHug::FallDown()
{
	m_fallTimer += GET_PLAYER_DT;

	if (m_fallTimer > m_fallDuration)
	{
		m_spTransform->SetPositionY(m_fallStartY - 1.f);
		m_skillState = Stretch;
		m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(1.f);
		return;
	}

	float lerpY = GetLerpFloat(m_fallStartY, m_fallStartY - 1.f, m_fallTimer / m_fallDuration);
	m_spTransform->SetPositionY(lerpY);
}

void CTheresa_CrossBloodyHug::StretchBlade()
{
	auto pDM = m_spMesh->GetFirstMeshData_Dynamic();
}

void CTheresa_CrossBloodyHug::RollBlade()
{
}

void CTheresa_CrossBloodyHug::EndSkill()
{
}
