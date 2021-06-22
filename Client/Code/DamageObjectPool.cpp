#include "stdafx.h"
#include "DamageObjectPool.h"
#include "ImageObject.h"
#include "DamageFontC.h"

IMPLEMENT_SINGLETON(CDamageObjectPool)
void CDamageObjectPool::Start(Engine::CScene* pScene)
{
	// Ǯ �߱�ȭ
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
	// Ȱ��ȭ�߿� ��Ȱ��ȭ�ȳ��� �Ѱ��ֱ�
	ReMoveDamage();
}

void CDamageObjectPool::OnDestroy(void)
{
	// ���� ������Ʈ ����
	m_disabledObjectList.clear();
	m_activationObjectList.clear();
}

void CDamageObjectPool::AddDamage(Engine::CObject* target, _float3 size,  _float interval, _float upSpped, _float lifeTime, _int damage, std::wstring color)
{
	// damage�� �ڸ�����ŭ for�����ƾ��Ѵ�.

	_int Tdamage = damage;
	_float intervalSum = interval;
	while (Tdamage != 0)
	{
		int value = Tdamage % 10;
		Tdamage /= 10;

		// ������ ���δ� ���ڸ����� �ɰ��� ���ݿ������� �����ϱ�
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
		object->GetComponent<CDamageFontC>()->AddDamageFontInit(target, intervalSum, upSpped, lifeTime, value, color);
		intervalSum += interval;
		object->GetTransform()->SetSize(size);
		m_disabledObjectList.pop_front();
		m_activationObjectList.emplace_back(object);
	}
}

void CDamageObjectPool::ReMoveDamage()
{
	// Ȱ��ȭ�� ������Ʈ�߿� ��Ȱ���� ������Ʈ�� �Ѱ��ֱ�
	/*for (auto& iter = m_activationObjectList.begin(); iter != m_activationObjectList.end(); iter++)
	{
		if (!(*iter)->GetIsEnabled())
		{
			m_disabledObjectList.emplace_back((*iter));
			iter = m_activationObjectList.erase(iter);
		}
	}*/
}
