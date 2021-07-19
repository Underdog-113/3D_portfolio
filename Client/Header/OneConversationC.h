#ifndef ONECONVERSATIONCOMPONENT_H
#define ONECONVERSATIONCOMPONENT_H

#include "Component.h"
class COneConversationC  final : public Engine::CComponent
{
public:
	explicit COneConversationC();
	~COneConversationC();

	SP(Engine::CComponent) MakeClone(Engine::CObject *pObject) override;
	void Awake() override;
	void Start(SP(Engine::CComponent) spThis) override;
	void FixedUpdate(SP(Engine::CComponent) spThis) override;
	void Update(SP(Engine::CComponent) spThis) override;
	void LateUpdate(SP(Engine::CComponent) spThis) override;
	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

public:
	_bool IsEnd();

private:
	void Conversation();
	void TextUpdate();
	void End();
	void Skip();
public:
	static const	EComponentID	m_s_componentID = EComponentID::TargetPosition;

private:
	Engine::CObject* m_conversationPlayerImage;
	Engine::CObject* m_conversationName;
	std::vector<Engine::CObject*> m_conversationText;

	_int m_conversationCount;
	_bool m_conversationCheck = false;
	_bool m_init;

	std::wstring m_inText[2];
	std::wstring m_outText[2];

	_float m_timer;

	_float m_textTime;
};
#endif
