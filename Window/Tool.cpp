#pragma warning(disable : 4996)
#include "Tool.h"

using namespace std;
 std::wstring Tool::StringToWstring(const std::string& string) noexcept
{
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, string.c_str(), string.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, string.c_str(), string.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾 
	result.append(buffer);
	delete[] buffer;
	return result;
}

 std::string Tool::WstringToString(const std::wstring& wstring) noexcept
{
    string result;
    //获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
    int len = WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), wstring.size(), NULL, 0, NULL, NULL);
    char* buffer = new char[len + 1];
    //宽字节编码转换成多字节编码  
    WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), wstring.size(), buffer, len, NULL, NULL);
    buffer[len] = '\0';
    //删除缓冲区并返回值  
    result.append(buffer);
    delete[] buffer;
    return result;

}

 std::wstring Tool::StringToWstringZN(const std::string& string) noexcept
 {
	 setlocale(LC_ALL, "zh_CN");
	 const char* point_to_source = string.c_str();
	 size_t new_size = string.size() + 1;
	 wchar_t* point_to_destination = new wchar_t[new_size];
	 wmemset(point_to_destination, 0, new_size);
	 mbstowcs(point_to_destination, point_to_source, new_size);
	 wstring result = point_to_destination;
	 delete[]point_to_destination;
	 return result;
 }
