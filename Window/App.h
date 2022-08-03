#pragma once
#include "U_Windows.h"
#include "Timer.h"
#include "Tool.h"


class App
{
public:
	App();
	int Start();
private:
	void Tick();
private:
	U_Windows wnd;
	Timer time;
	Tool tool;
};