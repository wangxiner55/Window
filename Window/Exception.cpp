#include "Exception.h"



CatchException::CatchException(int line, const char* file) noexcept :line(line) , file(file)
{
}

const char* CatchException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	whatBuffer = oss.str(); 
	return whatBuffer.c_str();//c_str()返回一个客户程序可读不可改的指向字符数组的指针，不需要手动释放或删除这个指针。
}

const char* CatchException::GetType() const noexcept
{
	return "SelfError Excption";
}

int CatchException::GetLine() const noexcept
{
	return line;
}

const std::string& CatchException::GetFile() const noexcept
{
	return file;
}

std::string CatchException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File]" << file << std::endl << "[Line]" << line;
	return oss.str();
}
