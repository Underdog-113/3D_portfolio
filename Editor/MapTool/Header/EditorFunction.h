#ifndef EDITORFUNCTION_H
#define EDITORFUNCTION_H

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

inline _bool WstrToBool(std::wstring wstr)
{
	return WstrToInt(wstr) == 1 ? true : false;
}

inline _float StrToFloat(std::string str)
{
	return std::stof(str);
}

inline std::string CStrToStr(CString cstr)
{
	return std::string(CT2CA(cstr));
}

#endif