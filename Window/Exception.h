#pragma once
#include <exception>
#include <string>
#include <sstream>


class CatchException :public std::exception
{
public:
	CatchException(int line, const char* file) noexcept; //file Ϊһ������
	const char* what() const noexcept override; //����ֵ���ܱ��޸�const* / ...const ���޸����ݳ�Ա /override ���غ���
	virtual const char* GetType() const noexcept; // noexcept �����ֱ�ӱ���
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;


private:
	int line;
	std::string file;


protected:
	mutable std::string whatBuffer; //���޸õĳ�Ա
};