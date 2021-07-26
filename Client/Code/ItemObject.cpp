#include "stdafx.h"
#include "..\Header\ItemObject.h"

_uint CItemObject::m_s_uniqueID = 0;

CItemObject::CItemObject()
{
}


CItemObject::~CItemObject()
{
	OnDestroy();
}

SP(CItemObject) CItemObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CItemObject) spInstance(new CItemObject, Engine::SmartDeleter<CItemObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CItemObject::MakeClone()
{
	SP(CItemObject) spClone(new CItemObject, Engine::SmartDeleter<CItemObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CItemObject::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"HPMedic");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Healing");
	m_spTexture->AddTexture(L"Healing");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
	_float _size = 0.5f;
	m_spTransform->SetSize(_float3(_size, _size, _size));
}

void CItemObject::Start()
{
	__super::Start();
	m_iItemNum = rand() % 3;

	switch (m_iItemNum)
	{
	case 0:
		m_eItemStyle = ItemStyle::COIN;
		m_spMesh->SetMeshData(L"coin");
		m_spTexture->ChangeTexture(L"Coin",0,0);
		m_spTexture->ChangeTexture(L"Coin",0,1);
		AddComponent<CMoneyItemC>()->AddDataInit(100, 50);
		break;
	case 1:
		m_eItemStyle = ItemStyle::SP;
		m_spMesh->SetMeshData(L"sp");
		m_spTexture->ChangeTexture(L"Light_Box2", 0, 0);
		m_spTexture->ChangeTexture(L"Power", 0, 1);
		AddComponent<CSpItemC>()->AddDataInit(100, 50);
		break;
	case 2:
		m_eItemStyle = ItemStyle::HP;
		AddComponent<CHpItemC>()->AddDataInit(100, 50);
		break;
	default:
		m_eItemStyle = ItemStyle::HP;
		AddComponent<CHpItemC>()->AddDataInit(100, 50);
		break;
	}

	m_fAlpha = 1.f;
	m_fTime = 0.f;
}

void CItemObject::FixedUpdate()
{
	__super::FixedUpdate();

}

void CItemObject::Update()
{
	__super::Update();

	//m_spTransform->AddRotationY(D3DXToRadian(15.f) * GET_DT * 3.f);
}

void CItemObject::LateUpdate()
{
	__super::LateUpdate();

}

void CItemObject::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", false);
	pEffect->SetFloat("gEmissionPow", 0.15f);
	pEffect->CommitChanges();
}

void CItemObject::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CItemObject::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CItemObject::OnDestroy()
{
	__super::OnDestroy();

	switch (m_eItemStyle)
	{
	case CItemObject::ItemStyle::COIN:
		Engine::CSoundManager::GetInstance()->StopSound((_int)EChannelID::ITEM);
		Engine::CSoundManager::GetInstance()->StartSound(L"Gold.wav", (_int)EChannelID::ITEM);
		break;
	case CItemObject::ItemStyle::SP:
		Engine::CSoundManager::GetInstance()->StopSound((_int)EChannelID::ITEM);
		Engine::CSoundManager::GetInstance()->StartSound(L"SPItem.wav", (_int)EChannelID::ITEM);
		break;
	case CItemObject::ItemStyle::HP:
		Engine::CSoundManager::GetInstance()->StopSound((_int)EChannelID::ITEM);
		Engine::CSoundManager::GetInstance()->StartSound(L"HPPotion.wav", (_int)EChannelID::ITEM);
		break;
	default:
		break;
	}

}

void CItemObject::OnEnable()
{
	__super::OnEnable();

}

void CItemObject::OnDisable()
{
	__super::OnDisable();

}

void CItemObject::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
