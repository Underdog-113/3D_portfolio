#pragma once
class CButtonObject final : public Engine::CObject
{
private:

public:
	CButtonObject();
	~CButtonObject();

	// CObject을(를) 통해 상속됨
	static	SP(CButtonObject) Create(_bool isStatic, Engine::CScene* pScene);
	virtual SP(Engine::CObject) MakeClone(void) override;
	virtual void Awake(void) override;
	virtual void Start(void) override;
	virtual void FixedUpdate(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnEnable(void) override;
	virtual void OnDisable(void) override;
	virtual void SetBasicName(void) override;

private:

};

