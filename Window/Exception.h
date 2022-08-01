#pragma once
#include <exception>
#include <string>

class CatchException :public std::exception
{
public:
	CatchException(int line, const char* file) noexcept;
	const char* what() const noexcept override;


private:
	int line;
	std::string file;


protected:
	mutable std::string whatBuffer;




	//This is A thest for Github
	//so on on on on
};