#ifndef UIANIMCTRCOMPONENT_H
#define UIANIMCTRCOMPONENT_H

#include "Component.h"
class CUiAnimCtrC  final : public Engine::CComponent
{
public:
	explicit CUiAnimCtrC();
	~CUiAnimCtrC();

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

	void Play();
public:
	static const	EComponentID	m_s_componentID = EComponentID::Text;
private:
	GETTOR_SETTOR(_int, m_animCount, 0, AnimCount);
	GETTOR_SETTOR(_bool, m_repeat, true, Repeat);
	_bool m_play;
	_int m_curAnimValue;
	GETTOR_SETTOR(std::list<_float3>, m_position, {}, Position)
	GETTOR_SETTOR(_float, m_animSpeed, 0, AnimSpeed);
	_float m_time;
};
#endif

// �ؽ�Ʈ �߰�
// ���� ���ϴ� �ؽ�Ʈ�� ������������
// ���ڿ���