#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

class CTextComponent final : public Engine::CComponent
{
public:
	explicit CTextComponent();
	~CTextComponent();

	// CComponent��(��) ���� ��ӵ�
	virtual SP(Engine::CComponent) MakeClone(Engine::CObject *pObject);
	virtual void Awake();
	virtual void Start(SP(Engine::CComponent) spThis);
	virtual void FixedUpdate(SP(Engine::CComponent) spThis);
	virtual void Update(SP(Engine::CComponent) spThis);
	virtual void LateUpdate(SP(Engine::CComponent) spThis);
	virtual void OnDestroy();
	virtual void OnEnable();
	virtual void OnDisable();
};

#endif