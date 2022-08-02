#pragma once
#include <Windows.h>
#include <string>
#include <codecvt>
#include <string>
#include <locale>


class Tool
{
public:

	 std::wstring StringToWstring(const std::string& string) noexcept;
	 std::string WstringToString(const std::wstring& wstring) noexcept;
	 std::wstring StringToWstringZN(const std::string& string) noexcept;

};

