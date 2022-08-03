#include "App.h"

App::App():wnd(800,800,L"Default Window")
{
}

int App::Start()
{
	while (true)
	{
		if (const auto ecode = WS_Windows::ProcessMessages())
		{
			return *ecode;
		}

		Tick();
	}

}

void App::Tick()
{

	const float c = sin(time.Peek()) / 2.0f + 0.5f;
	//wnd.Gfx().ClearBuffer(c, c, 0.0);
	wnd.Gfx().Draw();
	wnd.Gfx().EndFrame();


}



