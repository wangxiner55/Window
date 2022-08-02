#pragma once
#include "Windows.h"
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
	Windows wnd;
	Timer time;
	Tool tool;
};