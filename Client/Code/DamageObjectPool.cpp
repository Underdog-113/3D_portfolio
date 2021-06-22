#include "stdafx.h"
#include "DamageObjectPool.h"
#include "ImageObject.h"
#include "DamageFontC.h"

IMPLEMENT_SINGLETON(CDamageObjectPool)
void CDamageObjectPool::Start(Engine::CScene* pScene)
{
	// 풀 추기화
	_int poolCount = 50;

	for (int i = 0; i <= poolCount; i++)
	{
		SP(Engine::CImageObject) image =
			std::dynamic_pointer_cast<Engine::CImageObject>(pScene->GetObjectFactory()->AddClone(L"ImageObject", true, (_int)Engine::ELayerID::UI, L"DamageFontUIObject"));
		image->GetComponent<Engine::CShaderC>()->
			AddShader((_int)EShaderID::DamageFontShader);
		image->AddComponent<CDamageFontC>();

		image->SetIsEnabled(false);
		image->GetTexture()->AddTexture(L"Defalut", 0);
		m_disabledObjectList.emplace_back(image.get());
	}

}

void CDamageObjectPool::Update(void)
{
	// 활성화중에 비활성화된놈들 넘겨주기
	ReMoveDamage();
}

void CDamageObjectPool::OnDestroy(void)
{
	// 모든 오브젝트 삭제
	m_disabledObjectList.clear();
	m_activationObjectList.clear();
}

void CDamageObjectPool::AddDamage(_float3 pos, _float3 size,  _float interval, _float upSpped, _float enableTime, _int damage, std::wstring color)
{
	// damage의 자릿수만큼 for문돌아야한다.
	
	int Tdamage = damage;
	while (Tdamage != 0)
	{
		int value = Tdamage % 10;
		Tdamage /= 10;

		// 데미지 전부다 한자릿수로 쪼개고 간격에따라서 생성하기
		if (m_disabledObjectList.empty())
		{
			SP(Engine::CImageObject) image =
				std::dynamic_pointer_cast<Engine::CImageObject>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"ImageObject", true, (_int)Engine::ELayerID::UI, L"DamageFontUIObject"));
			image->AddComponent<CDamageFontC>();
			image->GetComponent<Engine::CShaderC>()->
				AddShader((_int)EShaderID::DamageFontShader);
			image->GetTexture()->AddTexture(L"Defalut", 0);
			m_disabledObjectList.emplace_back(image.get());
		}
		
		Engine::CObject* object = m_disabledObjectList.front();
		object->GetComponent<CDamageFontC>()->AddDamageFontInit(upSpped, enableTime, value, color);

		auto cam = Engine::CCameraManager::GetInstance()->GetCamera(Engine::GET_CUR_SCENE->GetObjectKey() + L"BasicCamera");
		_float3 pos2D = cam->WorldToScreenPoint(pos);
		pos2D.z = 0.f;

		object->GetTransform()->SetPosition(pos2D);
		pos.x += interval;
		object->GetTransform()->SetSize(size);

		m_disabledObjectList.pop_front();
		m_activationObjectList.emplace_back(object);
	}
}

void CDamageObjectPool::ReMoveDamage()
{
	// 활성화된 오브젝트중에 비활성된 오브젝트로 넘겨주기
	/*for (auto& iter = m_activationObjectList.begin(); iter != m_activationObjectList.end(); iter++)
	{
		if (!(*iter)->GetIsEnabled())
		{
			m_disabledObjectList.emplace_back((*iter));
			iter = m_activationObjectList.erase(iter);
		}
	}*/
}
