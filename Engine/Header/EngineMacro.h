#ifndef MACRO_H
#define MACRO_H

//���̺귯���� Engine���� export�ϰ� Client���� Import�ϰ� �Ѵ�.
#ifdef EXPORTS_ENGINE
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif

//�����ϰ� �����͸� ���켼��
#define SAFE_DELETE(something)														\
if((something) != nullptr)															\
	delete (something);																\
(something) = nullptr;

//MessageBox ����ȭ
#ifdef _DEBUG_MSG
#define MSG_BOX(file, message) MessageBox(0, message, Engine::GetCurFileName(file).c_str(), MB_OK)
#define ABORT abort()
#else
#define MSG_BOX(caption, message) 0
#define ABORT 0
#endif

//namespace setting
#define BEGIN(Name) namespace Name {
#define END }
#define USING(Name) using namespace Name;

//SmartPointers
#define SP(typeName) std::shared_ptr<typeName>
#define UNIQUE(typeName) std::unique_ptr<typeName>
#define WEAK(typeName) std::weak_ptr<typeName>

#define SMART_DELETER_REGISTER														\
template<typename T> friend void Engine::SmartDeleter(T* something);


//Gettor, Settor
#define GETTOR_SETTOR(varType, varName, varInitValue, funcName)						\
protected:																			\
	varType varName = varInitValue; 												\
public: 																			\
	virtual inline varType const& Get##funcName(void) const { return varName; }		\
	virtual inline void Set##funcName(varType var){ varName = var; }

#define GETTOR(varType, varName, varInitValue, funcName)							\
protected: 																			\
	varType varName = varInitValue; 												\
public: 																			\
	virtual inline varType const& Get##funcName(void) const { return varName; }

#define GETTOR_REF(varType, varName, varInitValue, funcName)						\
protected: 																			\
	varType varName = varInitValue; 												\
public: 																			\
	virtual inline varType& Get##funcName(void) { return varName; }




//Singleton Macro
//ī�� �����ڸ� ���ƿ�
#define NO_COPY(ClassName)															\
private:																			\
	ClassName(const ClassName&)	= delete;

//Assign operator�� ���ƿ�
#define NO_ASSIGN_OPERATOR(ClassName)												\
private:																			\
	ClassName& operator=(const ClassName&) = delete;


//Default Destructor ��ũ��
#define DEFAULT_DESTRUCTOR(ClassName)												\
	virtual ~ClassName(void) DEFAULT;

//Default Constructor ��ũ��
#define DEFAULT_CONSTRUCTOR(ClassName)												\
	explicit ClassName(void) NONE;

#define DEFAULT_COPY_CONSTRUCTOR(ClassName)											\
	explicit ClassName(const ClassName& other) NONE;

//�̱��� ���� ��ũ��
#define DECLARE_SINGLETON(ClassName)												\
		NO_COPY(ClassName)															\
		NO_ASSIGN_OPERATOR(ClassName)												\
protected:																			\
	DEFAULT_CONSTRUCTOR(ClassName)													\
	DEFAULT_DESTRUCTOR(ClassName)													\
public:																				\
	static ClassName*	GetInstance		(void);										\
	static void			DestroyInstance	(void);										\
private:																			\
	static ClassName*	m_s_pInstance;


//�̱��� ���� ��ũ��
#define IMPLEMENT_SINGLETON(ClassName)												\
ClassName* ClassName::m_s_pInstance = nullptr;										\
ClassName* ClassName::GetInstance(void)												\
{																					\
	if (nullptr == m_s_pInstance)													\
		m_s_pInstance = new ClassName;												\
	return m_s_pInstance;															\
}																					\
																					\
void ClassName::DestroyInstance(void)												\
{																					\
	if(m_s_pInstance != nullptr)													\
	{																				\
		m_s_pInstance->OnDestroy();													\
		delete m_s_pInstance;														\
		m_s_pInstance = nullptr;													\
	}																				\
}


//InputManager Macro
#define IMKEY_DOWN(key) CInputManager::GetInstance()->KeyDown(key)
#define IMKEY_PRESS(key) CInputManager::GetInstance()->KeyPress(key)
#define IMKEY_UP(key) CInputManager::GetInstance()->KeyUp(key)
#define IMMOUSE_POS() CInputManager::GetInstance()->GetMousePos()
#define IMWHEEL_DIR() CInputManager::GetInstance()->GetMouseWheelDir()


//SceneMangager Macro
#define GET_CUR_SCENE CSceneManager::GetInstance()->GetCurScene()

//WndApp Macro
#define GET_HANDLE CWndApp::GetInstance()->GetHWnd()
#define GET_WND_WIDTH CWndApp::GetInstance()->GetWndWidth()
#define GET_WND_HEIGHT CWndApp::GetInstance()->GetWndHeight()

//GraphicsManager Macro
#define ADD_TO_RENDER_LIST(renderID, spGraphicsC)									\
CGraphicsManager::GetInstance()->AddToRenderList(renderID, spGraphicsC)


//RenderTargetManager Macro
#define BEGIN_MRT(mrtName)															\
CRenderTargetManager::GetInstance()->BeginMRT(mrtName)
#define END_MRT(mrtName)															\
CRenderTargetManager::GetInstance()->EndMRT(mrtName)


//DeviceManager Macro
#define GET_DEVICE CDeviceManager::GetInstance()->GetDevice()

//FRC Macro
#ifdef EXPORTS_ENGINE
#define GET_DT CFRC::GetInstance()->GetDeltaTime()
#define GET_PURE_DT CFRC::GetInstance()->GetPureDeltaTime()
#else
#define GET_DT Engine::CFRC::GetInstance()->GetDeltaTime()
#define GET_PURE_DT Engine::CFRC::GetInstance()->GetPureDeltaTime()
#endif
#define TIME_MEASURE_START CFRC::GetInstance()->TimerStart()
#define GET_ELAPSED_TIME CFRC::GetInstance()->GetElapsedTime()

//DataStore Macro
#define GET_VALUE(isStatic, dataID, objectKey, varKey, result)						\
GetDataStore()->GetValue(isStatic, dataID, objectKey, varKey, result)


//ObjectFactory Macro
#define ADD_CLONE1(objectKey)														\
GetObjectFactory()->AddClone(objectKey)

#define ADD_CLONE2(objectKey, isStatic)												\
GetObjectFactory()->AddClone(objectKey, isStatic)

#define ADD_CLONE3(objectKey, isStatic, layerTag)									\
GetObjectFactory()->AddClone(objectKey, isStatic, layerTag)

#define ADD_CLONE4(objectKey, isStatic, layerTag, name)								\
GetObjectFactory()->AddClone(objectKey, isStatic, layerTag, name)

#define GET_5TH_ARG(arg1, arg2, arg3, arg4, arg5, ...) arg5

#define ADD_CLONE_MACRO_CHOOSER(...)												\
GET_5TH_ARG(__VA_ARGS__, ADD_CLONE4, ADD_CLONE3, ADD_CLONE2, ADD_CLONE1, )

#define ADD_CLONE(...) ADD_CLONE_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define ADD_PROTOTYPE(spPrototype)													\
GetObjectFactory()->AddPrototype(spPrototype)

//FontManager Macro
#define ADD_TEXT(key, text, position, boxsize, fontsize, alignment, color)										\
CTextManager::GetInstance()->AddText(key, text, position, boxsize, fontsize, alignment, color)

#define REWRITE_TEXT(key, text) CTextManager::GetInstance()->RewriteText(key, text)
#define DELETE_TEXT(key) CTextManager::GetInstance()->DeleteText(key)

//CameraManager Macro
#define GET_MAIN_CAM CCameraManager::GetInstance()->GetMainCamera()

//MathHelper Macro
#define GET_MATH CMath::CMathHelper::GetInstance()

//ShaderManager Macro
#define GET_SHADER(shaderID) CShaderManager::GetInstance()->GetShader(shaderID)

//SoundManager Macro
#define SOUND CSoundManager::GetInstance()

//PhysicsManager Macro
#define GET_PxSDK CPhysicsManager::GetInstance()
#define GET_PHYSICS CPhysicsManager::GetInstance()->GetPxPhysics()
#define GET_PxMATERIAL CPhysicsManager::GetInstance()->GetPxMaterial()


#endif // ! MACRO_H
