#ifndef BUTTON_H
#define BUTTON_H

#include "Object.h"
#include "DeleGate.h"
class CButton final : public Engine::CObject
{
public:
	enum EButton_Type { UP, Down, Press };
public:
	explicit CButton();
	~CButton();

	// CObject��(��) ���� ��ӵ�
	static	SP(CButton) Create(_bool isStatic, Engine::CScene* pScene);
	SP(Engine::CObject) MakeClone(void) override;
	void Awake(void) override;
	void Start(void) override;
	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;
	void OnDestroy(void) override;
	void OnEnable(void) override;
	void OnDisable(void) override;
	void SetBasicName(void) override;

	void FunceActivation();
private:

private:
	static _uint m_s_uniqueID;
	GETTOR_SETTOR(EButton_Type, m_buttonType, EButton_Type::UP, ButtonType);

	Delegate<> m_functionGate;

};
#endif

/*
�������� Ư����Ȳ�� ��������Ʈ�� ������������
1. ��ư������Ʈ�� ���� ����Ǵ������̴ٸ�
2. ���콺 �ѹ�Ŭ���� �ϳ��� ������Ʈ�� ��ư�� �����
3.

��ư�Ŵ����� ��� ��ư������Ʈ�� �������ִ´�.
���콺�� �ൿ���ϸ� �׿� �°� �Լ��������Ѵ�.
�ൿ�����ϰ� ��ư������Ʈ�� �������� �����Ѵ�.
*/