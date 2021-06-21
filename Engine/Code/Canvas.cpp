#include "EngineStdafx.h"
#include "Canvas.h"
#include "Layer.h"

USING(Engine)
_uint CCanvas::m_s_uniqueID = 0;
CCanvas::CCanvas()
{
}

CCanvas::~CCanvas()
{
	OnDestroy();
}

SP(CCanvas) CCanvas::Create(_bool isStatic, CScene * pScene)
{
	SP(CCanvas) spInstance(new CCanvas, SmartDeleter<CCanvas>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CCanvas::MakeClone(void)
{
	SP(CCanvas) spClone(new CCanvas, SmartDeleter<CCanvas>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<CTransformC>();

	return spClone;
}

void CCanvas::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::Decoration;
	m_addExtra = true;
}

void CCanvas::Start(void)
{
	__super::Start();
	AddObjectFind();
}

void CCanvas::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CCanvas::Update(void)
{
	__super::Update();

}

void CCanvas::LateUpdate(void)
{
	__super::LateUpdate();
}

void CCanvas::PreRender(LPD3DXEFFECT pEffect)
{
}

void CCanvas::Render(LPD3DXEFFECT pEffect)
{

}

void CCanvas::PostRender(LPD3DXEFFECT pEffect)
{
}

void CCanvas::OnDestroy(void)
{
	__super::OnDestroy();

	m_spObjectList.clear();
}

void CCanvas::OnEnable(void)
{
	__super::OnEnable();

	for (auto& object : m_spObjectList)
	{
		object->SetIsEnabled(true);
	}
}

void CCanvas::OnDisable(void)
{
	__super::OnDisable();

	for (auto& object : m_spObjectList)
	{
		object->SetIsEnabled(false);
	}
}

void CCanvas::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CCanvas::AddObjectFind()
{
	// 오브젝트의 앞글자가 캔버스의 이름과 같은지
	// _을 만나기전까지의 이름이 canvs의 이름이다.
	
	size_t strSize = m_name.size();

	for (auto& layer : m_pScene->GetLayers())
	{
		for (SP(CObject) object : layer->GetGameObjects())
		{
			std::wstring name = object->GetName().substr(0, strSize);
			if (m_name == name && object.get() != this)
			{
				m_spObjectList.emplace_back(object.get());
			}
		}
	}
}
