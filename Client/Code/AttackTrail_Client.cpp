#include "stdafx.h"
#include "..\Header\AttackTrail_Client.h"

_uint CAttackTrail_Client::m_s_uniqueID = 0;

CAttackTrail_Client::CAttackTrail_Client()
{
}


SP(Engine::CObject) CAttackTrail_Client::MakeClone()
{
	return SP(CObject)();
}

void CAttackTrail_Client::Awake()
{
	__super::Awake();


}

void CAttackTrail_Client::Start()
{
	__super::Start();
}

void CAttackTrail_Client::FixedUpdate()
{
	__super::FixedUpdate();
}

void CAttackTrail_Client::Update()
{
	__super::Update();

}

void CAttackTrail_Client::LateUpdate()
{
	__super::LateUpdate();
}

void CAttackTrail_Client::OnDestroy()
{
	__super::OnDestroy();
}

void CAttackTrail_Client::OnEnable()
{
	__super::OnEnable();
}

void CAttackTrail_Client::OnDisable()
{
	__super::OnDisable();
}

void CAttackTrail_Client::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
