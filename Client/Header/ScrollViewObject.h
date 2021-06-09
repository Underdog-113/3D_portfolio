#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include "Object.h"
#include "ImageObject.h"
class CScrollViewObject final : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	CScrollViewObject();
	~CScrollViewObject();

public:
	// CObject을(를) 통해 상속됨
	static	SP(CScrollViewObject) Create(_bool isStatic, Engine::CScene* pScene);
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

	void AddScrollViewData(_int column, _float2 distanceXY, _float2 offSet, std::wstring texture);
	CScrollViewObject* AddImageObjectData(std::wstring texture, _float3 size);

private:
	void SetBasicName(void) override;
	void ImageObjectSort();
private:
	static _uint m_s_uniqueID;

	GETTOR_SETTOR(_int, m_column, 1, Column); // 열
	GETTOR_SETTOR(_float2, m_offSet, _float2(0, 0), OffSet); // 이미지 사이의 거리
	GETTOR_SETTOR(_float2, m_distanceXY, _float2(1,1), DistanceXY); // 이미지 사이의 거리
	GETTOR_SETTOR(std::vector<SP(Engine::CImageObject)>, m_vImageObject, {}, ImageObject); // 그려야될 오브젝트의 그룹

	// 부가적인 이미지 요소
	// 이미지가 아니라 버튼이 들어갈수도있음

	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, nullptr, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, nullptr, Texture)
	GETTOR(SP(Engine::CRectTexC), m_spRectTex, nullptr, RectTex)
};
#endif
