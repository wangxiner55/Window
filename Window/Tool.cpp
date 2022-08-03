#pragma warning(disable : 4996)
#include "Tool.h"

using namespace std;
 std::wstring Tool::StringToWstring(const std::string& string) noexcept
{
	wstring result;
	//��ȡ��������С��������ռ䣬��������С���ַ�����  
	int len = MultiByteToWideChar(CP_ACP, 0, string.c_str(), string.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//���ֽڱ���ת���ɿ��ֽڱ���  
	MultiByteToWideChar(CP_ACP, 0, string.c_str(), string.size(), buffer, len);
	buffer[len] = '\0';             //����ַ�����β 
	result.append(buffer);
	delete[] buffer;
	return result;
}

 std::string Tool::WstringToString(const std::wstring& wstring) noexcept
{
    string result;
    //��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
    int len = WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), wstring.size(), NULL, 0, NULL, NULL);
    char* buffer = new char[len + 1];
    //���ֽڱ���ת���ɶ��ֽڱ���  
    WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), wstring.size(), buffer, len, NULL, NULL);
    buffer[len] = '\0';
    //ɾ��������������ֵ  
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
