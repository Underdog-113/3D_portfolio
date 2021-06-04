#pragma once
class CImageObject final : public Engine::CObject
{
private:

public:
	CImageObject();
	~CImageObject();

	// CObject을(를) 통해 상속됨
	static	SP(CImageObject) Create(_bool isStatic, Engine::CScene* pScene);
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

private:

};

