#ifndef TIMERUICOMPONENT_H
#define TIMERUICOMPONENT_H

#include "Component.h"
class CTimerUi  final : public Engine::CComponent
{
public:
	explicit CTimerUi();
	~CTimerUi();

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

public:
	static const	EComponentID	m_s_componentID = EComponentID::Text;
private:
};
#endif

// �ؽ�Ʈ �߰�
// ���� ���ϴ� �ؽ�Ʈ�� ������������
// ���ڿ���