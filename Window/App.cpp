#include "App.h"

App::App():wnd(800,800,L"Default Window")
{
}

int App::Start()
{
	MSG msg;
	BOOL gResult;
	while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (wnd.Key.KeyIsPressed(VK_MENU))
		{
			MessageBox(nullptr, L"Pressed", L"Pressed", MB_OKCANCEL);
		}
		
		Tick();
	} 

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}

}

void App::Tick()
{
	
	const float t = time.Peek();
	std::ostringstream oss;
	oss << "time" << t << std::endl;
	wnd.SetWindowName(oss.str());
}



