#ifndef CLIENTFUNCTION_H
#define CLIENTFUNCTION_H

inline std::vector<std::string> split(std::string input, char delimiter)
{
	std::vector<std::string> answer;
	std::stringstream ss(input);
	std::string temp;

	while (getline(ss, temp, delimiter))
		answer.push_back(temp);



	return answer;
}

inline _int WstrToInt(std::wstring wstr)
{
	return std::stoi(wstr);
}

inline std::wstring IntToWstr(_int num)
{
	return std::to_wstring(num);
}

inline _float WstrToFloat(std::wstring wstr)
{
	return std::stof(wstr);
}

inline _bool WstrToBool(std::wstring wstr)
{
	return WstrToInt(wstr) == 1 ? true : false;
}

inline _float StrToFloat(std::string str)
{
	return std::stof(str);
}

inline _int StrToInt(std::string str)
{
	return std::stoi(str);
}

inline std::wstring FloatToWStr(_float num)
{
	return std::to_wstring(num);
}

inline std::wstring DeleteCharInWstr(std::wstring src, _byte ch)
{
	std::string str = Engine::WStrToStr(src);
	str.erase(str.find_last_not_of(ch) + 1, str.length() - 1);
	str.erase(str.find_last_not_of('.') + 1, str.length() - 1);

	return Engine::StrToWStr(str);
}

inline _int GetRandRange(_int min, _int max)
{
	return rand() % ((max - min) + 1) + min;
}


inline _float3 GetLerpPosition(_float3 startPos, _float3 endPos, _float curTime, _float lerpDuration = 1.f)
{
	if (curTime >= lerpDuration)
		return endPos;

	_float3 dir = endPos - startPos;
	_float length = D3DXVec3Length(&dir);
	_float timeline = curTime / lerpDuration;

	_float moveAmount = length * timeline;

	D3DXVec3Normalize(&dir, &dir);
	return startPos + dir * moveAmount;
}

inline float GetLerpFloat(float _start, float _end, float _time)
{
	return _start * (1.f - _time) + _time * _end;
}

#endif