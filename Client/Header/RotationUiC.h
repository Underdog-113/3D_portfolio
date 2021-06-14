#ifndef ROTATIONUICOMPONENT_H
#define ROTATIONUICOMPONENT_H

#include "Component.h"
class CRotationUiC  final : public Engine::CComponent
{
public:
	explicit CRotationUiC();
	~CRotationUiC();

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
	GETTOR_SETTOR(_float, m_speed, 0, Speed);
};
#endif

// �ؽ�Ʈ �߰�
// ���� ���ϴ� �ؽ�Ʈ�� ������������
// ���ڿ���