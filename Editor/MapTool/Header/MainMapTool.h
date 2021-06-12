#pragma once
class CMainMapTool final
{
	SMART_DELETER_REGISTER;
protected:
	explicit CMainMapTool(void);
	~CMainMapTool(void);

public:
	static SP(CMainMapTool) Create(void);

	void Awake(void);
	void Start(void);
		 
	void FixedUpdate(void);
	void Update(void);
	void LateUpdate(void);
		 
	void PreRender(void);
	void Render(void);
	void PostRender(void);
		 
	void OnDestroy(void);
		 
	void OnEnable(void);
	void OnDisable(void);
		 
private: 
	void InitStaticPrototype(void);
};
