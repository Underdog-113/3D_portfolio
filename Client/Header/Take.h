#pragma once

class CShot;
class CTake
{
public:
	CTake();
	~CTake();

	void StartTake();
	void ActTake();

	void ActTake_EditMode();
	void ActTake_NormalMode();

	void EndTake();

public:
	void MoveNextFrame();
	void MovePreviousFrame();

public:
	void EndShot(CShot* pShot);

	void AddShot(std::wstring name, CShot* pShot);
	void ReadyShot(std::wstring name, _float startTimeline, _float endTimeline, void* pDesc, _float readyTimeline);

protected:
	std::unordered_map<std::wstring, CShot*> m_shotMap;


	GETTOR_SETTOR(_float, m_playTimer, 0.f, PlayTimer)
	GETTOR_SETTOR(_bool, m_editMode, false, EditMode)

};   

