#pragma once
#include "Windows.h"


class App
{
public:
	App();
	int Start();
private:
	void Tick();
private:
	Windows wnd;
};