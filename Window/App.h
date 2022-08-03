#pragma once
#include "WS_Windows.h"
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
	WS_Windows wnd;
	Timer time;
	Tool tool;
};