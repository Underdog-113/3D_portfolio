#ifndef CANVASECOMPONENT_H
#define CANVASECOMPONENT_H

class CCanvasComponent final : public Engine::CComponent
{
private:
	std::list<SP(Engine::CObject)> m_objectList;
public:
	explicit CCanvasComponent();
	~CCanvasComponent();

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

private:
	void FindUi();
};

#endif