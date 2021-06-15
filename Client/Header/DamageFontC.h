#ifndef DAMAGEFONTCOMPONENT_H
#define DAMAGEFONTCOMPONENT_H

#include "Component.h"
class CDamageFontC  final : public Engine::CComponent
{
public:
	explicit CDamageFontC();
	~CDamageFontC();

	// CComponent��(��) ���� ��ӵ�
	SP(Engine::CComponent) MakeClone(Engine::CObject *pObject) override;
	void Awake() override;
	void Start(SP(Engine::CComponent) spThis) override;
	void FixedUpdate(SP(Engine::CComponent) spThis) override;
	void Update(SP(Engine::CComponent) spThis) override;
	void LateUpdate(SP(Engine::CComponent) spThis) override;
	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void AddDamageFontInit(_float upSpped, _float lifeTime, _int damage, std::wstring color);
public:
	static const	EComponentID	m_s_componentID = EComponentID::Text;
private:
	_int m_damage;
	_float m_upSpeed;
	_float m_lifeTime;
	_float m_oldLifeTime;
};
#endif

// �ؽ�Ʈ �߰�
// ���� ���ϴ� �ؽ�Ʈ�� ������������
// ���ڿ���