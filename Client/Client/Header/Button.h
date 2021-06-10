#ifndef BUTTON_H
#define BUTTON_H

#include "Object.h"
#include "DeleGate.h"
class CButton final : public Engine::CObject
{
	SMART_DELETER_REGISTER
public:
	enum EButton_Type { UP, Down, Press };
private:
	explicit CButton();
	~CButton();

public:
	// CObject��(��) ���� ��ӵ�
	static	SP(CButton) Create(_bool isStatic, Engine::CScene* pScene);
	SP(Engine::CObject) MakeClone(void) override;
	void Awake(void) override;
	void Start(void) override;

	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;

	void PreRender(void) override;
	void Render(void) override;
	void PostRender(void) override;

	void OnDestroy(void) override;

	void OnEnable(void) override;
	void OnDisable(void) override;

	void SetBasicName(void) override;

	void FuncActivation();

	template<typename Function, typename Object>
	void AddFuncData(Function function, Object object)
	{
		m_functionGate += std::bind(function, object);
	}

	void AddFuncData(Delegate<> delegate)
	{
		m_functionGate += delegate;
	}

private:

private:
	static _uint m_s_uniqueID;

	GETTOR_SETTOR(EButton_Type, m_buttonType, EButton_Type::UP, ButtonType)

	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, {}, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, {}, Texture)
	GETTOR(SP(Engine::CRectTexC), m_spRectTex, {}, RectTex)

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