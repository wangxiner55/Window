#pragma once
#include <exception>
#include <string>
#include <sstream>


class CatchException :public std::exception
{
public:
	CatchException(int line, const char* file) noexcept; //file 为一个常量
	const char* what() const noexcept override; //返回值不能被修改const* / ...const 不修改数据成员 /override 重载函数
	virtual const char* GetType() const noexcept; // noexcept 不检查直接编译
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;


private:
	int line;
	std::string file;


protected:
	mutable std::string whatBuffer; //可修该的成员
};