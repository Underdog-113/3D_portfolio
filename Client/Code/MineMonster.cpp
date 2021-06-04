#include "stdafx.h"
#include "..\Header\MineMonster.h"


CMineMonster::CMineMonster() :
	m_eCurState(STATE_END),
	m_ePreState(STATE_END),
	m_fDelay(0.f)	
{

}

SP(Engine::CObject) CMineMonster::MakeClone(void)
{
	SP(CMineMonster) spClone(new CMineMonster, Engine::SmartDeleter<CMineMonster>);

	spClone->AddComponent<Engine::CMeshC>()->AddMeshData(L"Spider");
	spClone->AddComponent<Engine::CTextureC>();
	spClone->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spClone->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);

	__super::InitClone(spClone);

	return spClone;
}

void CMineMonster::Awake(void)
{
	__super::Awake();
}

void CMineMonster::Start(void)
{
	__super::Start();

}

void CMineMonster::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMineMonster::Update(void)
{
	__super::Update();
}

void CMineMonster::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMineMonster::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMineMonster::OnEnable(void)
{
	__super::OnEnable();
}

void CMineMonster::OnDisable(void)
{
	__super::OnDisable();
}

void CMineMonster::SetBasicName(void)
{
}

void CMineMonster::Chase_Target(_float DeltaTime)
{

}

void CMineMonster::Change_State()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CMineMonster::WALK_RIGHT:
			break;
		case CMineMonster::WALK_LEFT:
			break;
		case CMineMonster::WALK_FORWARD:
			break;
		case CMineMonster::THROW_BLOW:
			break;
		case CMineMonster::THROW_02:
			break;
		case CMineMonster::THROW_01:
			break;
		case CMineMonster::IDLE:
			break;
		case CMineMonster::KNOCK_DOWN:
			break;
		case CMineMonster::HIT_THROW_L:
			break;
		case CMineMonster::HIT_THROW:
			break;
		case CMineMonster::HIT_L_EARLY:
			break;
		case CMineMonster::HIT_H:
			break;
		case CMineMonster::BURY_LOOP:
			break;
		case CMineMonster::BURY_BS:
			break;
		case CMineMonster::BURY_AS:
			break;
		case CMineMonster::BORN:
			break;
		case CMineMonster::ATTACK_DIE:
			break;
		case CMineMonster::ATTACK_3_BS:
			break;
		case CMineMonster::ATTACK_3_AS:
			break;
		case CMineMonster::ATTACK_3:
			break;
		case CMineMonster::ATTACK_2_RUN:
			break;
		case CMineMonster::ATTACK_2_BS:
			break;
		case CMineMonster::ATTACK_2:
			break;
		case CMineMonster::ATTACK_1:
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}