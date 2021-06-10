#pragma once
class CMainEditor final 
{
	SMART_DELETER_REGISTER
protected:
	CMainEditor();
	~CMainEditor();

public:
	static SP(CMainEditor) Create();

	void Awake();
	void Start();

	void FixedUpdate(void);
	void Update(void);
	void LateUpdate(void);

	void PreRender(void);
	void Render(void);
	void PostRender(void);

	void OnDestroy(void);

	void OnEnable(void);
	void OnDisable(void);
};

