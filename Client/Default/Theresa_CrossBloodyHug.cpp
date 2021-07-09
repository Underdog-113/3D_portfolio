#include "stdafx.h"
#include "Theresa_CrossBloodyHug.h"

#pragma region Engine
#include "MeshC.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#pragma endregion

#include "AttackBall.h"
#include "StageCameraMan.h"


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
	m_spCrossBlade->GetTransform()->SetSizeY(2.f);

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->GetTransform()->SetSize(5.f, 5.f, 5.f);
	m_pAttackBall->SetIsEnabled(false);
	m_pAttackBall->SetOwner((Engine::CObject*)m_pTheresa);
}

void CTheresa_CrossBloodyHug::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CTheresa_CrossBloodyHug::Update(void)
{
	__super::Update();

	// sp 12, 10��, 2�ʵ��� 0.25�ʸ��� �ѹ��� ���� 200��
	switch (m_skillState)
	{
	case CTheresa_CrossBloodyHug::Ready:
		FallReady();
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
	// ���ڰ� ���߿� ��ȯ


	// ������ ����


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
	m_stateTimer = 0.f;
	m_stateDuration = 0.5f;
	m_skillState = Ready;
	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(0.f);

	HitInfo info;
	info.SetDamageRate(0.25f);
	info.SetStrengthType(HitInfo::Str_Damage);
	info.SetCrowdControlType(HitInfo::CC_None);
	m_pAttackBall->SetupBall(1.2f, info);

	CStageControlTower::GetInstance()->SetCameraCustomTake(3.f, 1.5f, D3DXToRadian(5.f));
}

void CTheresa_CrossBloodyHug::OnDisable(void)
{
	__super::OnDisable();	
	m_spMesh->GetFirstMeshData_Dynamic()->ResetAnimation();
}

void CTheresa_CrossBloodyHug::SetBasicName(void)
{
}

void CTheresa_CrossBloodyHug::FallReady()
{
	m_stateTimer += GET_PLAYER_DT;

	if (m_stateTimer > m_stateDuration)
	{
		m_stateTimer = 0.f;
		m_stateDuration = 0.12f;
		m_skillState = Fall;

		CStageControlTower::GetInstance()->SetCameraCustomTake(4.f, 2.f, D3DXToRadian(10.f));
		return;
	}
}

void CTheresa_CrossBloodyHug::FallDown()
{
	m_stateTimer += GET_PLAYER_DT;

	if (m_stateTimer > m_stateDuration)
	{
		m_spTransform->SetPositionY(m_fallEndY);
		m_skillState = Stretch;
		m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(1.f);
		CStageControlTower::GetInstance()->GetCameraMan()->ShakeCamera_Theresa_CrossImpact(Engine::GET_MAIN_CAM->GetTransform()->GetPosition());
		return;
	}

	float lerpY = GetLerpFloat(m_fallStartY, m_fallEndY, m_stateTimer / m_stateDuration);
	m_spTransform->SetPositionY(lerpY);
}

void CTheresa_CrossBloodyHug::StretchBlade()
{
	if (m_spMesh->GetFirstMeshData_Dynamic()->GetAniTimeline() > 0.99f)
	{
		m_stateTimer = 0.f;
		m_stateDuration = 2.f;
		m_spCrossBlade->GetTransform()->SetPosition(m_spTransform->GetPosition());
		//m_spCrossBlade->GetTransform()->AddPositionX(0.5f);
		m_spCrossBlade->GetTransform()->AddPositionY(0.3f);
		m_spCrossBlade->SetIsEnabled(true);
		m_pAttackBall->GetTransform()->SetPosition(m_spTransform->GetPosition());
		//0m_pAttackBall->GetTransform()->AddPositionX(0.3f);
		m_pAttackBall->GetTransform()->AddPositionY(0.3f);
		m_skillState = Roll;
		return;
	}
}

void CTheresa_CrossBloodyHug::RollBlade()
{
	// �ٷ� Į�� ��ȯ�ؼ� ���ۺ���

	m_stateTimer += GET_PLAYER_DT;
	m_attackTimer += GET_PLAYER_DT;

	m_spCrossBlade->GetTransform()->AddRotationY(D3DXToRadian(480.f) * GET_PLAYER_DT);

	if (m_pAttackBall->GetIsEnabled())
	{
		m_pAttackBall->SetIsEnabled(false);
	}

	if (m_attackTimer > 0.25f)
	{
		m_attackTimer = 0.f;
		m_pAttackBall->SetIsEnabled(true);
	}

	if (m_stateTimer > m_stateDuration)
	{
		m_skillState = End;
		return;
	}


}

void CTheresa_CrossBloodyHug::EndSkill()
{
	// remove effectd
	m_spCrossBlade->SetIsEnabled(false);
	m_pAttackBall->SetIsEnabled(false);
	SetIsEnabled(false);
}
